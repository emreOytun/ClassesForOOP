#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
const T& getMax(const T arr[], int len) {
	if (len <= 0) {
		throw runtime_error("There is no element");
	}

	int max_i = 0;
	for (int i = 1; i < len; ++i) {
		if (arr[i] > arr[max_i]) max_i = i;
	}
	
	return arr[max_i];
}

template<class T>
const T& getMaxRec(const T arr[], int len) {
	if (len <= 0) {
		throw runtime_error("There is no element");
	}
	
	if (len == 1) return arr[0];
	
	const T& element = arr[len-1];
	const T& restMax = getMaxRec(arr, len-1);
	
	if (element > restMax) return element;
	return restMax;
}

int main () {
	
	int arr[10] {1, 3, 4};
	cout << getMax(arr, 3) << "\n";
	cout << getMaxRec(arr, 3) << "\n";
	
	return 0;
}
