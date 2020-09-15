#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>
#include <chrono>

using namespace std;

class Sort {
	private:
		int arrType; // used to determine if our array will be sorted, reverseSorted, or random : 0, 1, 2, respectively
		vector<int> arr;
		vector<int> generateSorted(int newSize);
		vector<int> generateReverseSorted(int newSize);
		vector<int> generateRandom(int newSize);
		vector<int> setArr(int initArr, int newSize);
		void mergeSortHelper(vector<int>& vec, int front, int back, int &steps);
		void merge(vector<int>& vec, int front, int midpoint, int back, int &steps);
		long long totalDurationInMicroSecs;
		int totalSteps;
		int size;
	public:
		Sort();
		Sort(int initArr, int newSize);
		int getSize() const;
		long long getTotalTime();
		int getTotalSteps();
		void insertionSort();
		void mergeSort();
		void printArr() const;
		void resetArr();
		void resetFiftyInstancesTracker();
		void resetSize(int newSize);
		void resetArrType(int initArr);
		void resetSizeAndType(int initArr, int newSize);
		string getInitArrType() const;
};

#endif