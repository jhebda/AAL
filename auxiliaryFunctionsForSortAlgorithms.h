#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>
#include "auxiliaryFunctionsAndStructs.h"
#include "sequenceGenerator.h"

using namespace std;

Node* newConstructTree(string startingShelf, string sortedShelf, queue<Node*>& toDelete);
Node* getNextChildToCheck(Node* node, int i, map<string, int> combinationsWithLvls);
int findMin(string digits, int correct);
Substring findSubstringToMove(string digits, int lastSorted, char& digitToSort);
string moveSubstringToDivisibleByFour(string digits, Substring bestSubstring, char digitToSort, int& numberOfSorted, int& numberOfMoves, bool debugMode);