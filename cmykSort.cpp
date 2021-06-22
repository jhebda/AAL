// cmykSort.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <sstream>
#include <fstream>
#include "sequenceGenerator.h"
#include "sortAlgorithms.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void exportToFile(string path, std::vector<std::pair<int, std::vector<std::pair<double, double>>>> results, int numOfLoops);
void executeProperMode(char* argv[]);
void printTimeDuration(time_point<high_resolution_clock> stop, time_point<high_resolution_clock> start);
double calculateStandardDeviation(vector<double> moves);
void exportMoves(vector<double> moves);

int main(int argc, char* argv[]) {
	if (argc == 1)
		return 0;
	executeProperMode(argv);
}

void printTimeDuration(time_point<high_resolution_clock> stop, time_point<high_resolution_clock> start) {
	duration<double, milli> dur = stop - start;
	cout << "time: " << dur.count() << endl;
}

void executeProperMode(char* argv[]) {
	std::string shelf, sorted;;
	std::vector<string> data;
	std::pair<double, double> numOfMoves[3];
	SequenceGenerator generator;
	int size, percentage, numOfLoops, step, numOfSteps, firstStep, whichAlgorithm;
	time_point<high_resolution_clock> start;
	time_point<high_resolution_clock> stop;
	vector<double> moves;
	vector<double> times;
	double movesSum = 0;
	double timesSum = 0;

	switch (argv[1][2]) {
	case '1':
		while (!cin.eof()) {
			whichAlgorithm = std::stoi(argv[1]);
			std::cin >> shelf;
			std::cout << shelf << "\n";
			sorted = sortShelf(shelf);
			numOfMoves[whichAlgorithm].first = 0;
			numOfMoves[whichAlgorithm].second = 0;
			start = high_resolution_clock::now();
			switch (whichAlgorithm) {
			case 0:
				shelf = treeSort(shelf, numOfMoves);
				break;
			case 1:
				shelf = insertionSort(shelf, numOfMoves);
				break;
			case 2:
				shelf = insertionSortBetter(shelf, numOfMoves);
				break;
			case 3:
				shelf = insertionSortWithSubstrings(shelf, numOfMoves);
				break;
			}
			stop = high_resolution_clock::now();
			std::cout << shelf << " sorted?: " << bool(shelf == sorted) << " numOfMoves: " << numOfMoves[whichAlgorithm].second << "\t";
			printTimeDuration(stop, start);
			cout << "\n\n";
		}
		break;

	case '2':
		size = std::stoi(argv[2]);
		percentage = std::stoi(argv[3]);
		whichAlgorithm = std::stoi(argv[4]);
		shelf = generator.generateWithSameNextElementPossibility(size, percentage);
		std::cout << shelf << "\n";
		sorted = sortShelf(shelf);
		numOfMoves[whichAlgorithm].first = 0;
		numOfMoves[whichAlgorithm].second = 0;
		start = high_resolution_clock::now();
		switch (whichAlgorithm) {
		case 0:
			shelf = treeSort(shelf, numOfMoves);
			break;
		case 1:
			shelf = insertionSort(shelf, numOfMoves);
			break;
		case 2:
			shelf = insertionSortBetter(shelf, numOfMoves);
			break;
		case 3:
			shelf = insertionSortWithSubstrings(shelf, numOfMoves);
			break;
		}
		stop = high_resolution_clock::now();
		std::cout << shelf << " sorted?: " << bool(shelf == sorted) << " numOfMoves: " << numOfMoves[whichAlgorithm].second << "\t";
		printTimeDuration(stop, start);
		cout << "\n\n";
		break;

	case '3':
		firstStep = std::stoi(argv[2]);
		numOfSteps = std::stoi(argv[3]);
		step = std::stoi(argv[4]);
		numOfLoops = std::stoi(argv[5]);
		whichAlgorithm = std::stoi(argv[6]);
		for (int i = firstStep; i < firstStep + numOfSteps * step; i += step) {
			numOfMoves[whichAlgorithm].first = 0;
			numOfMoves[whichAlgorithm].second = 0;
			double sumOfTime = 0;
			for (int j = 0; j < numOfLoops; j++) {
				shelf = generator.generateRandomSequence(i, i);
				sorted = sortShelf(shelf);
				start = high_resolution_clock::now();
				switch (whichAlgorithm) {
				case 0:
					shelf = treeSort(shelf, numOfMoves);
					break;
				case 1:
					shelf = insertionSort(shelf, numOfMoves);
					break;
				case 2:
					shelf = insertionSortBetter(shelf, numOfMoves);
					break;
				case 3:
					shelf = insertionSortWithSubstrings(shelf, numOfMoves);
					break;
				}
				stop = high_resolution_clock::now();
				duration<double, milli> dur = stop - start;
				sumOfTime += dur.count();
			}
			std::cout << "step: " << i << "\t avr numOfMoves: " << numOfMoves[whichAlgorithm].second / numOfLoops << "\t avg time: " << sumOfTime / numOfLoops << endl;
		}
		break;

	case '4':
		size = std::stoi(argv[2]);
		percentage = std::stoi(argv[3]);
		numOfLoops = std::stoi(argv[4]);
		whichAlgorithm = std::stoi(argv[5]);
		if (whichAlgorithm < 0 || whichAlgorithm > 3) {
			std::cout << "bad algorithm number\n";
			return;
		}

		for (int i = 0; i < numOfLoops; i++) {
			numOfMoves[whichAlgorithm].first = 0;
			numOfMoves[whichAlgorithm].second = 0;
			shelf = generator.generateWithSameNextElementPossibility(size, percentage);
			start = high_resolution_clock::now();
			switch (whichAlgorithm) {
			case 0:
				shelf = treeSort(shelf, numOfMoves);
				break;
			case 1:
				shelf = insertionSort(shelf, numOfMoves);
				break;
			case 2:
				shelf = insertionSortBetter(shelf, numOfMoves);
				break;
			case 3:
				shelf = insertionSortWithSubstrings(shelf, numOfMoves);
				break;
			}
			stop = high_resolution_clock::now();
			duration<double, milli> durCombined = stop - start;
			moves.push_back(numOfMoves[whichAlgorithm].second);
			movesSum += numOfMoves[whichAlgorithm].second;
			times.push_back(durCombined.count());
			timesSum += durCombined.count();
			numOfMoves[whichAlgorithm].second = 0;
		}

		std::cout << "Moves: Standard Deviation: " << calculateStandardDeviation(moves) << "\t\tAvg: " << movesSum / numOfLoops << "\t\tCoefficient of variation: " << round(100 * calculateStandardDeviation(moves) / (movesSum / numOfLoops)) << " %\n";
		std::cout << "Times: Standard Deviation: " << calculateStandardDeviation(times) << "\t\tAvg: " << timesSum / numOfLoops << "\t\tCoefficient of variation: " << round(100 * calculateStandardDeviation(times) / (timesSum / numOfLoops)) << " %\n";
		//exportMoves(moves);

		break;

	default:
		std::cout << "bad argument\n";
		return;
	}
}

void exportToFile(string path, std::vector<std::pair<int, std::vector<std::pair<double, double>>>> results, int numOfLoops) {
	std::ofstream outputFile;
	outputFile.open(path);

	if (outputFile.is_open()) {
		for (auto& result : results) {
			outputFile << std::get<0>(result);
			for (auto& i : std::get<1>(result))
				outputFile << "\t" << std::get<0>(i) / numOfLoops << "\t" << std::get<1>(i) / numOfLoops;
			outputFile << "\n";
		}
		outputFile.close();
	}
	else
		std::cout << "OutputFile wasn't opened correctly";

}

double calculateStandardDeviation(vector<double> moves) {
	double average = 0.0, sum = 0;
	int numberOfElements = moves.size();

	for (int i = 0; i < numberOfElements; i++)
		average += moves[i];
	average = average / numberOfElements;

	for (int i = 0; i < numberOfElements; i++)
		sum += pow(moves[i] - average, 2);

	return sqrt(sum / numberOfElements);
}

void exportMoves(vector<int> moves) {
	std::ofstream outputFile;
	outputFile.open("moves.txt");

	if (outputFile.is_open()) {
		for (auto& result : moves)
			outputFile << result << "\n";
		outputFile.close();
	}
	else
		std::cout << "OutputFile wasn't opened correctly";
}