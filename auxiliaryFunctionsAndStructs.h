#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>

using namespace std;

struct Node {
	Node* parent;
	Node* bestChild;
	string value;
	int lvl;
	int lvlOfSuccess;
	bool isSuccess;
	int movedFourParentPosition;

	Node(string value, Node* parent) {
		this->value = value;
		this->lvl = parent != NULL ? parent->lvl + 1 : 0;
		this->lvlOfSuccess = INT_MAX;
		this->parent = parent;
		this->bestChild = NULL;
		this->isSuccess = false;
		this->movedFourParentPosition = -1;
	}
};

struct Substring {
	int position;
	int lenght;

	Substring() {
		this->position = -1;
		this->lenght = -1;
	}

	Substring(int position, int lenght) {
		this->position = position;
		this->lenght = lenght;
	}

	bool operator<(Substring other) {
		if (other.position % 4 == 0) {
			if (position % 4 != 0 || (position % 4 == 0 && other.lenght > lenght)) {
				return true;
			}
		}
		else if (position % 4 != 0 && other.lenght > lenght) {
			return true;
		}
		return false;
	}

	bool operator>(Substring other) {
		return !this->operator<(other);
	}

};

string moveFour(string current, size_t index, bool debugMode = false);
string sortShelf(string current);
string shelfToDigits(string shelf);
string digitsToShelf(string digits);
void printBestPath(Node* bestCombination, std::pair<double, double>* numOfMoves, bool debugMode = false);