#pragma once
#include "auxiliaryFunctionsForSortAlgorithms.h"

using namespace std;

enum class sortAlgorithmsType
{
	Tree = 0,
	Insertion = 1,
	InsertionBetter = 2,
	InsertionWithSubstrings = 3
};

string treeSort(string shelf, std::pair<double, double>* numOfMoves, bool debugMode = false);
string insertionSort(string shelf, std::pair<double, double>* numOfMoves, bool debugMode = false);
string insertionSortBetter(string shelf, std::pair<double, double>* numOfMoves, bool debugMode = false);
string insertionSortWithSubstrings(string shelf, std::pair<double, double>* numOfMoves, bool debugMode = false);