#include <iostream>
using namespace std;

template<class T>
T getMedian(const T arr[], int len) {
	/* Error-check */
	if (len <= 0) {
		throw runtime_error("Lenght cannot be 0 or negative.");
	}
	
	/* Copy array */
	T copy[len];
	for (int i = 0; i < len; ++i) {
		copy[i] = arr[i];
	}
	
	/* Sort */
	for (int i = 0; i < len; ++i) {
		int min_i = i;	// Be careful here !!
		for (int j = i+1; j < len; ++j) {
			if (arr[j] < arr[min_i]) min_i = j;
		}
		
		T temp = arr[i];
		arr[i] = arr[min_i];
		arr[min_i] = temp;
	}
	
	/* Find median */
	T median;
	if (len % 2 == 0) {
		median = arr[len/2] + arr[len/2 - 1]		
	}
	
	else {
		median = arr[(len-1)/2];	
	}
	
	return median;
}

