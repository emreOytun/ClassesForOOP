#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<class T>
vector<T> getIntersection(const T arr1[], int len1, const T arr2[], int len2) {
	vector<T> res;
	if (len1 == 0) return res;
	
	bool contains = false;
	for (int i = 0; i < len2 && !contains; ++i) {
		if (arr2[i] == arr1[len1-1]) {
			contains = true;
		}
	}
	
	if (contains) res.push_back(arr1[len1-1]);
	const vector<T>& restRes = getIntersection(arr1, len1-1, arr2, len2);
	for (int i = 0; i < restRes.size(); ++i) {
		res.push_back(restRes[i]);
	}
	
	return res;
}

int main () {
	const int arr1[] {1, 3, 4, 5, 6};
	const int arr2[] {2, 3, 1, 5, 5, 7, 6};	
	
	const vector<int>& res = getIntersection(arr1, 5, arr2, 7);
	for (auto& e : res) {
		cout << e << " ";
	}
	
	return 0;
}
