#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
bool contains(const vector<T>& vec, const T& element) {
	if (vec.size() == 0) return false;
	if (vec.back() == element) return true;
	
	vector<T> copy = vec;
	copy.pop_back();
	return contains(copy, element);
}

template<class T>
vector<T> getRepeated(vector<T> vec) {
	vector<T> res;
	if (vec.size() == 0 || vec.size() == 1) return res;
	
	const T& last = vec.back();
	vec.pop_back();
	
	auto it = find(vec.begin(), vec.end(), last);
	if (it != vec.end()) {
		res.push_back(last);
		
		bool isDone = false;
		do {
			auto it = find(vec.begin(), vec.end(), last);
			if (it != vec.end()) vec.erase(it);
			else isDone = true;
		}while(!isDone);
	}

	const vector<T>&& restRes = getRepeated(vec);
	for (int i = 0; i < restRes.size(); ++i) res.push_back(restRes[i]);
	return res;	
}


int main () {
	
	vector<int> v1 {1, 3, 4, 5, 5, 2, 1, 0, -2, -2};
	vector<int>&& res = getRepeated(v1);
	for (auto& e : res) {
		cout << e << " ";
	}
	
	
	return 0;
}


