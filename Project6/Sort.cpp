#include "Sort.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

Sort::Sort() {
	arr = generateSorted(100);
	size = 100;
	totalSteps = 0;
	arrType = 0;
	totalDurationInMicroSecs = 0;
}

Sort::Sort(int initArr, int newSize) {
	size = newSize;
	arrType = initArr;
	totalSteps = 0;
	totalDurationInMicroSecs = 0;
	arr = setArr(initArr, newSize);
}

vector<int> Sort::generateSorted(int newSize) {
	vector<int> arr;
	for (int i = 1; i <= newSize; i++) {
		arr.push_back(i);
	}
	return arr;
}

vector<int> Sort::generateReverseSorted(int newSize){
	vector<int> arr;
	for (int i = newSize; i >= 1; i--) {
		arr.push_back(i);
	}
	return arr;
}

vector<int> Sort::generateRandom(int newSize) {
	srand((unsigned)time(0));
	vector<int> arr;
	for (int i = 1; i <= newSize; i++) {
		int randomNumber = (rand() % newSize) + 1;
		arr.push_back(randomNumber);
	}
	return arr;
}

void Sort::printArr() const {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
}

// used to determine whether our array is going be sorted, reverseSorted, or random before we run a sorting algorithm
vector<int> Sort::setArr(int initArr, int newSize) {
	switch (initArr) {
	case 0:
		return generateSorted(newSize);
	case 1:
		return generateReverseSorted(newSize);
	case 2:
		return generateRandom(newSize);
	default:
		return generateSorted(newSize);
	}
}

// used to get the name of the arr type we're sorting
string Sort::getInitArrType() const {
	switch (arrType) {
	case 0:
		return "sorted";
	case 1:
		return "reverse sorted";
	case 2:
		return "random";
	default:
		return "";
	}
}

// used to reset how our initial array should look like before sort (sorted, reverseSorted, or random) and rebuilds it
void Sort::resetArrType(int initArr) {
	// set arrType
	switch (initArr) {
	case 0:
		arrType = 0;
		break;
	case 1:
		arrType = 1;
		break;
	case 2:
		arrType = 2;
		break;
	default:
		arrType = 0;
		break;
	}
	resetArr();
}

// used for resetting both the initial array type (sorted, reverse sorted, random) and size of array
void Sort::resetSizeAndType(int initArr, int newSize) {
	size = newSize;
	resetArrType(initArr);
}

// changes the size property of the Sort object and creates a new vector of newSize
void Sort::resetSize(int newSize){
	size = newSize;
	resetArr();
}
// used to remove the old data from memory and reset the array after every instance run
void Sort::resetArr() {
	arr.clear();
	vector<int>().swap(arr);
	arr = setArr(arrType, size);
}

// returns total duration of n runs in microseconds
long long Sort::getTotalTime() {
	return totalDurationInMicroSecs;
}

// returns the total steps of n runs
int Sort::getTotalSteps() {
	return totalSteps;
}

// gets the size of the array we're working with
int Sort::getSize() const {
	return size;
}

// resets the total time of the Sort instance if we're not keeping track of total time for multiple runs
void Sort::resetFiftyInstancesTracker() {
	totalDurationInMicroSecs = 0;
	totalSteps = 0;
}

void Sort::insertionSort() {
	// starting this instance timer & init the steps to 0
	high_resolution_clock::time_point instanceStartTime = high_resolution_clock::now();
	int steps = 0;
	for (int i = 1; i < arr.size(); i++) { 
		// skip the first element since that's the start of our sorted array & one element is by itself is sorted
		steps++;
		int j = i;
		while (j > 0 && arr[j - 1] > arr[j]) {
			steps++;
			int temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
			j--;
		}
	}
	// ending this instance timer
	high_resolution_clock::time_point instanceEndTime = high_resolution_clock::now();
	auto thisDuration = duration_cast<microseconds>(instanceEndTime - instanceStartTime);
	cout << "Insertion sort took " << steps << " number of steps and " << thisDuration.count() << " microseconds for a " << getInitArrType() << " array" << endl;
	totalDurationInMicroSecs += thisDuration.count();
	totalSteps += steps;
}

// its job is to call and use the mergeSort algorithm since it needs to keep track of time
void Sort::mergeSort() {
	// startTimer and initing steps to 0
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	// only sort if the arr size is greater than 1 else it's already sorted
	int steps = 0;
	mergeSortHelper(arr, 0, arr.size() - 1, steps);
	// endTimer
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	auto thisDuration = duration_cast<microseconds>(endTime - startTime);
	cout << "Merge sort took " << steps << " number of steps and " << thisDuration.count() 
		<< " microseconds for a " << getInitArrType() << " array" << endl;
	totalSteps += steps;
	totalDurationInMicroSecs += thisDuration.count();
}

// the actual merge sorting algorithm that's recursively calling itself
void Sort::mergeSortHelper(vector<int> &vec, int front, int back, int &steps) {
	if (front < back) {
		steps++;
		int midpoint = (front + back) / 2;
		mergeSortHelper(vec, front, midpoint, steps);
		mergeSortHelper(vec, midpoint + 1, back, steps);
		merge(vec, front, midpoint, back, steps);
	}
}

void Sort::merge(vector<int> &vec, int front, int midpoint, int back, int &steps) {
	vector<int> newArr(back - front + 1);
	int subArr1Ptr = front, subArr2Ptr = midpoint + 1, ptr = 0;

	while (subArr1Ptr <= midpoint && subArr2Ptr <= back) {
		steps++;
		if (vec.at(subArr1Ptr) <= vec.at(subArr2Ptr)) {
			newArr[ptr] = vec.at(subArr1Ptr);
			ptr++;
			subArr1Ptr++;
		} else {
			newArr[ptr] = vec.at(subArr2Ptr);
			ptr++;
			subArr2Ptr++;
		}
	}

	// used to store any leftover values in the first half of the array into our new array
	while (subArr1Ptr <= midpoint) {
		steps++;
		newArr[ptr] = vec.at(subArr1Ptr);
		ptr++;
		subArr1Ptr++;
	}

	// used to store any leftover values in the latter half of the array into our new array
	while (subArr2Ptr <= back) {
		steps++;
		newArr[ptr] = vec.at(subArr2Ptr);
		ptr++;
		subArr2Ptr++;
	}

	// storing our need sorted subarray back into our original vector
	for (int i = front, k = 0; i <= back; i++) {
		steps++;
		vec.at(i) = newArr[k++];
	}
}