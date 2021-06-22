#pragma once

#include <iostream>
#include <random>
#include "auxiliaryFunctionsAndStructs.h"

using namespace std;

class SequenceGenerator {
public:
	string generateRandomSequence(int sequenceLenght, int stepsToSolve);
	string generateWithSameNextElementPossibility(int maxSequenceLenght, int possibilityAsProcent);
	string shuffleSequence(string sequence, int numberOfShuffels);

private:
	string shuffleSequenceOneTime(string sequence);
	int generateRandomInt(int from, int to);
};