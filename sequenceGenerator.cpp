#include "sequenceGenerator.h"

string SequenceGenerator::generateRandomSequence(int sequenceLenght, int stepsToSolve)
{
	if (sequenceLenght < 4) {
		return "";
	}
	int remainingSequneceLenght = sequenceLenght - 4;
	char cansTypes[4] = { 'C', 'M', 'Y', 'K' };
	string sequence = "";
	for (int i = 0; i < remainingSequneceLenght; i++)
		sequence += string(1, cansTypes[generateRandomInt(0, 3)]);

	sequence += "KKKK";
	return shuffleSequence(sortShelf(sequence), stepsToSolve);
}

string SequenceGenerator::generateWithSameNextElementPossibility(int maxSequenceLenght, int possibilityAsProcent)
{
	if (possibilityAsProcent > 100 || maxSequenceLenght < 4) {
		return "";
	}
	int remainingSequneceLenght = maxSequenceLenght - 4;
	char cansTypes[4] = { 'C', 'M', 'Y', 'K' };
	string sequence = "KKKK";
	for (int i = 4; i < remainingSequneceLenght; i++) {
		int randomInt = generateRandomInt(1, 100);
		if (randomInt <= possibilityAsProcent) {
			sequence += sequence[i - 1];
		}
		else {
			char nextCan;
			do {
				nextCan = cansTypes[generateRandomInt(0, 3)];
			} while (nextCan == sequence[i - 1]);
			sequence += nextCan;
		}
	}
	return sequence;
}

string SequenceGenerator::shuffleSequence(string sequence, int numberOfShuffels)
{
	for (int i = 0; i < numberOfShuffels; i++) {
		sequence = shuffleSequenceOneTime(sequence);
	}
	return sequence;
}

string SequenceGenerator::shuffleSequenceOneTime(string sequence)
{
	if (sequence.length() >= 5) {
		int moveToPosition = generateRandomInt(0, sequence.length() - 5);
		return sequence.substr(0, moveToPosition) + sequence.substr(sequence.length() - 4, 4) + sequence.substr(moveToPosition, sequence.length() - moveToPosition - 4);
	}
	return sequence;
}

int SequenceGenerator::generateRandomInt(int from, int to)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> distribution(from, to);
	return distribution(rd);
}