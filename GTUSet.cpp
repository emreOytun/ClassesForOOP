#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

template<class T>
class GTUSet {

public :
	
	virtual ~GTUSet() = default;
	
	virtual void add(const T& element) = 0; // no duplicates
	virtual void remove(const T& element) = 0;
	virtual bool contains(const T& element) const noexcept = 0;
	virtual const T& get(int idx) const = 0;
	virtual void clear() = 0;
	virtual int size() const noexcept = 0;
	virtual void print() const noexcept = 0;
	
	
	static void intersectionSet(const GTUSet<T>& set1, const GTUSet<T>& set2, GTUSet<T>& result) {
		if (result.size() > 0) result.clear();
		
		for (int i = 0; i < set1.size(); ++i) {
			if (set2.contains(set1.get(i))) {
				result.add(set1.get(i));
			}
		}
	}
	
	static void unionSet(const GTUSet<T>& set1, const GTUSet<T>& set2, GTUSet<T>& result) {
		if (result.size() > 0) result.clear();
		
		for (int i = 0; i < set1.size(); ++i) {
			result.add(set1.get(i));
		}
		
		for (int i = 0; i < set2.size(); ++i) {
			if (!set1.contains(set2.get(i))) {
				result.add(set2.get(i));
			}
		}	
	} 

};

template<class T>
class GTUSetV : public GTUSet<T> {
	
public :
	
	virtual void add(const T& element) override {
		auto it = find(data.begin(), data.end(), element);
		if (it == data.end()) {
			data.push_back(element);
		}
	}
	
	virtual void remove(const T& element) override {
		auto it = find(data.begin(), data.end(), element);
		if (it != data.end()) {
			data.erase(it);
		}
	}
	
	virtual void clear() override {
		data.clear();
	}
	
	virtual bool contains(const T& element) const noexcept {
		auto it = find(data.begin(), data.end(), element);
		if (it == data.end()) return false;
		return true;
	}
	
	virtual const T& get(int idx) const {
		if (idx < 0 || idx >= data.size()) {
			throw runtime_error("Invalid index");
		}
		
		return data[idx];
	}
	
	virtual int size() const noexcept override {
		return data.size();
	}
	
	virtual void print() const noexcept override {
		for (auto e : data) {
			cout << e << " ";
		}
		cout << "\n";
	}
	
	
private :
	vector<T> data;
};


template<class T>
class GTUSetD : public GTUSet<T> {
	
public :
	GTUSetD() : data(new T[DEFAULT_CAPACITY]), len(0) {
	
	}
	
	GTUSetD(const GTUSetD<T>& oth) : data(new T[oth.capacity]), len(oth.len), capacity(oth.capacity) {
		for (int i = 0; i < oth.len; ++i) {
			data[i] = oth.data[i];
		}
	}
	
	const GTUSetD<T>& operator=(const GTUSetD<T>& oth) {
		if (data != nullptr) delete [] data;
		data = new T[oth.capacity];
		len = oth.len;
		capacity = oth.capacity;
		
		for (int i = 0; i < len; ++i) {
			data[i] = oth.data[i];
		}
	
		return *this;
	}
	
	/* Dont't forget 'noexcept' keyword here. */
	GTUSetD(GTUSetD<T>&& oth) noexcept : data(oth.data), len(oth.len), capacity(oth.capacity) {
		oth.data = nullptr;
		oth.len = 0;
		oth.capacity = 0;
	}
	
	const GTUSetD<T>& operator=(GTUSetD<T>&& oth) {
		if (this == &oth) return *this; // Don't forget to check references here.
		
		if (data != nullptr) delete [] data;
		data = oth.data;
		len = oth.len;
		capacity = oth.capacity;
		
		oth.data = nullptr;
		oth.len = 0;
		oth.capacity = 0;
		
		return *this;
	}
	
	virtual ~GTUSetD() {
		if (data != nullptr) delete [] data;
		data = nullptr;
	}
	
	virtual void add(const T& element) override {
		bool isFound = contains(element);
		
		if (!isFound) {	
			if (len == capacity) setCapacity(capacity * 2);
			data[len] = element;
			++len;
		}
	}
	
	virtual void remove(const T& element) override {
		bool isFound = false;
		int idx = -1;
		for (int i = 0; i < len && !isFound; ++i) {
			if (data[i] == element) {
				idx = i;
				isFound = true;
			}
		}
		
		if (isFound) {
			for (int i = idx+1; i < len; ++i) {
				data[i-1] = data[i];
			}
			--len;
			if (len == capacity && len != 0) setCapacity(capacity / 2);
		}
	}
	
	virtual bool contains(const T& element) const noexcept override {
		bool isFound = false;
		for (int i = 0; i < len && !isFound; ++i) {
			if (data[i] == element) {
				isFound = true;
			}
		}
		return isFound;
	}
	
	virtual const T& get(int idx) const override {
		if (idx < 0 || idx >= len) {
			throw runtime_error("Invalid index");
		}
	
		return data[idx];
	}
	
	virtual void clear() override {
		if (data != nullptr) delete [] data;
		len = 0;
		capacity = 0;
	}
	
	virtual int size() const noexcept override {
		return len;
	}
	
	virtual void print() const noexcept override {
		for (int i = 0; i < len; ++i) {
			cout << data[i] << " ";
		}
		cout << "\n";
	}
	
	
private :
	T* data;
	int len;
	int capacity;
	static const int DEFAULT_CAPACITY = 10;
	
	void setCapacity(int newCapacity) {
		if (newCapacity == 0) newCapacity = DEFAULT_CAPACITY; // Don't forget to check this.
		T* newData = new T[newCapacity];
		
		for (int i = 0; i < len; ++i) {
			newData[i] = data[i];		
		}
		
		if (data != nullptr) delete [] data;
		data = newData;
		capacity = newCapacity;
	}
};


int main () {
	GTUSetV<int> set1;
	set1.add(3);
	set1.add(5);
	set1.add(7);
	set1.print();
	
	GTUSetD<int> set2;
	set2.add(1);
	set2.add(3);
	set2.add(7);
	set2.add(9);
	set2.print();
	
	GTUSetV<int> res;
	
	GTUSet<int>::intersectionSet(set1, set2, res);
	res.print();
	
	GTUSet<int>::unionSet(set1, set2, res);
	res.print();
	
	return 0;
}
