#include "auxiliaryFunctionsAndStructs.h"


string sortShelf(string shelf) {
	string digits = shelfToDigits(shelf);

	sort(digits.begin(), digits.end());

	return digitsToShelf(digits);
}

string shelfToDigits(string shelf) {
	string digits;
	for (size_t i = 0; i < shelf.length(); i++) {
		switch (shelf[i])
		{
		case 'C':
			digits += "1";
			break;
		case 'M':
			digits += "2";
			break;
		case 'Y':
			digits += "3";
			break;
		case 'K':
			digits += "4";
			break;
		default:
			break;
		}
	}
	return digits;
}

string digitsToShelf(string digits) {
	string shelf;
	for (size_t i = 0; i < digits.length(); i++) {
		switch (digits[i])
		{
		case '1':
			shelf += "C";
			break;
		case '2':
			shelf += "M";
			break;
		case '3':
			shelf += "Y";
			break;
		case '4':
			shelf += "K";
			break;
		default:
			break;
		}
	}
	return shelf;
}

string moveFour(string current, size_t index, bool debugMode) {
	size_t currSize = current.length();
	if (index >= 0 && index < currSize - 4) {
		string movedCurr = current.substr(0, index);
		movedCurr += current.substr(index + 4, currSize - index - 4);
		movedCurr += current.substr(index, 4);
		if (debugMode) {
			current = digitsToShelf(current);
			string value = current.substr(0, index) + " <" + current.substr(index, 4) + "> " + current.substr(index + 4, current.length() - index - 4);
			value += "  ->  " + digitsToShelf(movedCurr);
			std::cout << value << "\n";
		}
		return movedCurr;
	}
	return current;
}

void printBestPath(Node* bestCombination, std::pair<double, double>* numOfMoves, bool debugMode) {
	if (bestCombination == NULL) {
		return;
	}
	stack<Node*> toPrint;
	Node* curr = bestCombination;
	int lvlOfWin = curr->lvl;
	while (curr != NULL) {
		toPrint.push(curr);
		if (curr->parent != NULL) {
			curr->parent->bestChild = curr;
		}
		curr = curr->parent;
	}
	while (!toPrint.empty()) {
		curr = toPrint.top();
		string value = curr->value;
		if (debugMode && curr->bestChild != NULL) {
			int index = curr->bestChild->movedFourParentPosition;
			if (index > -1) {
				value = value.substr(0, index) + " <" + value.substr(index, 4) + "> " + value.substr(index + 4, value.length() - index - 4);
				value += "  ->  " + curr->bestChild->value;
			}
		}
		toPrint.pop();
	}
	numOfMoves[0].second += lvlOfWin;
}