#include "sortAlgorithms.h"

string treeSort(string shelf, std::pair<double, double>* numOfMoves, bool debugMode) {
	string result = shelf;
	string sortedShelf = sortShelf(shelf);

	queue<Node*> toDelete;

	int bestLvlOfSuccess = INT_MAX;
	if (shelf != sortedShelf) {
		Node* bestCombination = newConstructTree(shelf, sortedShelf, toDelete);
		if (bestCombination != NULL) {
			result = bestCombination->value;
			printBestPath(bestCombination, numOfMoves, debugMode);
		}
		while (!toDelete.empty()) {
			toDelete.pop();
		}
	}
	return result;
}

string insertionSort(string shelf, std::pair<double, double>* numOfMoves, bool debugMode) {
	string digits = shelfToDigits(shelf);
	int SIZE = shelf.size(), corr = 0, pos, padd, zs;
	int numberOfMoves = 0;
	while (corr != SIZE) {
		pos = findMin(digits, corr);
		if (pos % 4 != 0) {
			zs = (SIZE - corr - 1) - (SIZE - corr - 1) / 4 * 4;
			padd = pos - 3 + zs;
			if (padd < 0) {
				digits = moveFour(digits, corr, debugMode);
				numberOfMoves++;
			}
			else {
				padd = corr + padd;
				if (padd >= SIZE - 4) {
					padd = corr;
					if (padd >= SIZE - 4)
						return "";
					digits = moveFour(digits, padd, debugMode);
					numberOfMoves++;
				}
				else {

					digits = moveFour(digits, padd, debugMode);
					numberOfMoves++;

					for (int i = (SIZE - corr - 1) / 4; i > 0; i--) {
						digits = moveFour(digits, corr, debugMode);
						numberOfMoves++;
					}
					corr++;
				}
			}
		}
		else {
			for (int i = pos / 4; i > 0; i--) {
				digits = moveFour(digits, corr, debugMode);
				numberOfMoves++;
			}
			corr++;
		}
		if (debugMode)
			printf("SIZE: %d corr: %d left: %d\n", SIZE, corr, SIZE - corr);
	}
	numOfMoves[int(sortAlgorithmsType::Insertion)].second += numberOfMoves;
	return digitsToShelf(digits);
}

string insertionSortBetter(string shelf, std::pair<double, double>* numOfMoves, bool debugMode) {
	string digits = shelfToDigits(shelf);
	int SIZE = shelf.size(), corr = 0, pos, padd, zs, goodPos = 0, inQue = 0;
	int numberOfMoves = 0;
	while (corr != SIZE) {
		pos = findMin(digits, corr);
		if (pos % 4 != 0 && pos != goodPos) {
			zs = (SIZE - corr - 1) - (SIZE - corr - 1) / 4 * 4;
			padd = pos - 3 + zs - inQue % 4;
			if (padd < 0) /*too close to start to position correctly*/ {
				digits = moveFour(digits, corr, debugMode);
				numberOfMoves++;
				goodPos = goodPos == 0 ? 0 : goodPos - 4;
			}
			else {
				padd = corr + padd;
				if (padd >= SIZE - 4) /*too close to end of sequence to positions to position correctly*/ {
					padd = corr;
					if (padd >= SIZE - 4)
					{
						printf("ERROR!!! SIZE: %d corr: %d left: %d gP: %d", SIZE, corr, SIZE - corr, goodPos);
						std::cout << digitsToShelf(digits) << "\n";
						return "";
					}
					digits = moveFour(digits, padd, debugMode);
					numberOfMoves++;
					goodPos = goodPos == 0 ? 0 : goodPos - 4;
				}
				else {
					if (padd + 3 >= corr + goodPos && goodPos != 0)
						digits = moveFour(digits, corr + goodPos - 4, debugMode);
					else
					{
						digits = moveFour(digits, padd, debugMode);
						inQue++;
					}
					numberOfMoves++;


					if (goodPos == 0)
						goodPos = (SIZE - corr - 1) / 4 * 4;
					else
						goodPos -= 4;

				}
			}
		}
		else {
			for (int i = pos / 4; i > 0; i--) {
				digits = moveFour(digits, corr, debugMode);
				numberOfMoves++;
			}
			goodPos = 0;
			inQue = 0;
			corr++;
		}
	}
	numOfMoves[int(sortAlgorithmsType::InsertionBetter)].second += numberOfMoves;
	return digitsToShelf(digits);
}

string insertionSortWithSubstrings(string shelf, std::pair<double, double>* numOfMoves, bool debugMode) {
	string digits = shelfToDigits(shelf);
	int SIZE = shelf.size(), numberOfSorted = 0;
	Substring bestSubstring;
	int numberOfMoves = 0;
	char digitToSort = '1';
	for (int i = 0; i < SIZE && digits[i] == digitToSort; i++) {
		numberOfSorted++;
	}
	while (numberOfSorted < SIZE) {
		bestSubstring = findSubstringToMove(digits, numberOfSorted, digitToSort);
		if (bestSubstring.position == -1) {
			break;
		}
		if (bestSubstring.position % 4 == 0) {
			for (int i = bestSubstring.position / 4; i > 0; i--) {
				digits = moveFour(digits, numberOfSorted, debugMode);
				numberOfMoves++;
			}
			numberOfSorted += bestSubstring.lenght;
		}
		else {
			if (bestSubstring.position >= SIZE - 4) {
				digits = moveFour(digits, numberOfSorted, debugMode);
				numberOfMoves++;
			}
			else {
				digits = moveSubstringToDivisibleByFour(digits, bestSubstring, digitToSort, numberOfSorted, numberOfMoves, debugMode);
			}
		}
	}
	numOfMoves[int(sortAlgorithmsType::InsertionWithSubstrings)].second += numberOfMoves;
	return digitsToShelf(digits);
}