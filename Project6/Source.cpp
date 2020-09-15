#include "Sort.h"

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

void runForSizeN(Sort& run, int n, string sortType);
void runFiftyX(Sort& run, string sortType);

int main() {
	Sort run = Sort(0,0);
	/* insertion sorts */
	// size 100
	runForSizeN(run, 100, "insertion");

	// size 200
	runForSizeN(run, 200, "insertion");

	// size 300
	runForSizeN(run, 300, "insertion");

	// size 400
	runForSizeN(run, 400, "insertion");

	// size 500
	runForSizeN(run, 500, "insertion");
	
	// size 1000
	runForSizeN(run, 1000, "insertion");
	
	// size 4000
	runForSizeN(run, 4000, "insertion");

	// size 10000
	runForSizeN(run, 10000, "insertion");
	

	/* merge sorts */
	// size 100
	runForSizeN(run, 100, "merge");

	// size 200
	runForSizeN(run, 200, "merge");

	// size 300
	runForSizeN(run, 300, "merge");

	// size 400
	runForSizeN(run, 400, "merge");
	
	// size 500
	runForSizeN(run, 500, "merge");
	
	// size 1000
	runForSizeN(run, 1000, "merge");

	// size 4000
	runForSizeN(run, 4000, "merge");

	// size 10000
	runForSizeN(run, 10000, "merge");
	return 0;
}

// helper function that runs our sort 50x
void runFiftyX(Sort& run, string sortType) {
	if (sortType == "insertion") {
		int i = 1;
		for (i; i <= 50; i++) {
			run.insertionSort();
			run.resetArr();
		}
		cout << "50 runs of insertion sort on a ";
	} else if (sortType == "merge") {
		int i = 1;
		for (i; i <= 50; i++) {
			run.mergeSort();
			run.resetArr();
		}
		cout << "50 runs of merge sort on a ";
	}
	cout << run.getInitArrType() << " array with an initial size of " << run.getSize() << " took a total of " << run.getTotalSteps() << " steps and " 
	<< run.getTotalTime() << " microseconds." << endl;
}

// helper to run all sorting suit for size n
void runForSizeN(Sort& run, int n, string sortType) {
	cout << "Running for size n: " << n << endl;
	run.resetSizeAndType(0, n); // sorted array of size n
	sortType == "insertion" ? run.insertionSort() : run.mergeSort();
	run.resetArrType(1); // reverseSorted array of size n
	sortType == "insertion" ? run.insertionSort() : run.mergeSort();
	run.resetArrType(2); // randomArr of size n
	sortType == "insertion" ? run.insertionSort() : run.mergeSort();
	run.resetFiftyInstancesTracker(); // resetting the totalTime tracker in run object to prepare for the 50x timer run
	run.resetArr(); // resetting the array so we can a totally random initial array
	runFiftyX(run, sortType);
}