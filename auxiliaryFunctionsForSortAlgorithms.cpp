#include "auxiliaryFunctionsForSortAlgorithms.h"

Node* newConstructTree(string startingShelf, string sortedShelf, queue<Node*>& toDelete) {
	queue<Node*> toCheck;
	map<string, int> combinationsWithLvls;
	Node* combinationsTree = new Node(startingShelf, NULL);
	toCheck.push(combinationsTree);
	while (!toCheck.empty()) {
		Node* currentNode = toCheck.front();
		toDelete.push(currentNode);
		for (int i = 0; i < startingShelf.length() - 4; i++) {
			Node* child = getNextChildToCheck(currentNode, i, combinationsWithLvls);
			if (child == NULL) {
				continue;
			}
			child->movedFourParentPosition = i;
			combinationsWithLvls[child->value] = child->lvl;
			if (sortedShelf == child->value) {
				int currentLvlOfSuccess = child->lvl;
				child->lvlOfSuccess = currentLvlOfSuccess;
				while (!toCheck.empty()) {
					toCheck.pop();
				}
				toDelete.push(child);
				return child;
			}
			else {
				toCheck.push(child);
				toDelete.push(child);
			}
		}
		toCheck.pop();
	}
	return NULL;
}

Node* getNextChildToCheck(Node* node, int i, map<string, int> combinationsWithLvls) {
	Node* child = new Node(moveFour(node->value, i), node);
	child->movedFourParentPosition = i;
	if (combinationsWithLvls.size() > 0) {
		map<string, int>::iterator it = combinationsWithLvls.find(child->value);
		if (it != combinationsWithLvls.end() && it->second < child->lvl)
		{
			delete child;
			return NULL;
		}
	}
	return child;
}

int findMin(string digits, int correct) {
	int pos = correct;
	char min;
	min = digits[correct];

	for (int i = correct + 1; i < digits.size(); i++) {
		if (digits[i] < min) {
			min = digits[i];
			pos = i;
		}
	}

	return pos - correct;
}

Substring findSubstringToMove(string digits, int numberOfSorted, char& digitToSort) {
	Substring best;
	if (digitToSort > '4') {
		return best;
	}
	for (int i = numberOfSorted; i < digits.size(); i++) {
		if (digits[i] == digitToSort) {
			Substring candidate(i - numberOfSorted, 1);
			i++;
			while (i < digits.size() && digits[i] == digitToSort) {
				candidate.lenght++;
				i++;
			}
			if (best < candidate) {
				best = candidate;
				if (best.position % 4 == 0) {
					return best;
				}
			}
		}
	}
	if (best.position == -1) {
		digitToSort++;
		return findSubstringToMove(digits, numberOfSorted, digitToSort);
	}
	return best;
}

string moveSubstringToDivisibleByFour(string digits, Substring bestSubstring, char digitToSort, int& numberOfSorted, int& numberOfMoves, bool debugMode) {
	int numberOfDigitsToSort = digits.length() - numberOfSorted;
	int numberOfDigitsAfterProperPosition = numberOfDigitsToSort % 4;
	int moveFromPosition = numberOfSorted + bestSubstring.position - 4 + numberOfDigitsAfterProperPosition;
	if (moveFromPosition < numberOfSorted) {
		numberOfMoves++;
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> distribution(numberOfSorted, digits.length() - 4);
		return moveFour(digits, distribution(rd), debugMode);
	}
	int numberOfMovesToMake = (bestSubstring.lenght / 4);
	digits = moveFour(digits, moveFromPosition, debugMode);
	numberOfMoves++;
	bestSubstring.position = digits.length() - numberOfDigitsAfterProperPosition - numberOfSorted;
	for (; numberOfMovesToMake > 0; numberOfMovesToMake--) {
		digits = moveFour(digits, moveFromPosition, debugMode);

		numberOfMoves++;
		bestSubstring.position -= 4;
	}
	for (int i = bestSubstring.position / 4; i > 0; i--) {
		digits = moveFour(digits, numberOfSorted, debugMode);

		numberOfMoves++;
	}
	for (int i = numberOfSorted; i < digits.length() && digits[i] == digitToSort; i++) {
		numberOfSorted++;
	}
	return digits;
}