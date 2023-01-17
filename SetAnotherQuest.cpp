#include <iostream>
#include <deque>
using namespace std;

template<class T>
class Set {

public :	
	virtual ~Set() = default;
	
	virtual void add(const T& element) = 0;
	virtual bool contains(const T& element) const noexcept = 0;
	virtual void intersection(const Set<T>& oth, Set<T>& res) const = 0;
	virtual int size() const noexcept = 0;
	virtual void clear() = 0;
	
};

template<class T, class Container = deque<T>>
class SetA : public Set<T> {
	
public :
	virtual void add(const T& element) override;
	virtual bool contains(const T& element) const noexcept override;
	virtual void intersection(const Set<T>& oth, Set<T>& res) const override;
	virtual int size() const noexcept override;
	virtual void clear() override;
	
private :
	Container data;
};


template<class T, class Container>
void SetA<T, Container>::add(const T& element) {
	if (!contains(element)) data.push_back(element);
}

template<class T, class Container>
bool SetA<T, Container>::contains(const T& element) const noexcept {
	bool isFound = false;
	for (auto it = data.begin(); it < data.end() && !isFound; ++it) {
		if (*it == element) isFound = true;
	}
	return isFound;
}

template<class T, class Container>
void SetA<T, Container>::intersection(const Set<T>& oth, Set<T>& res) const {
	if (res.size() != 0) res.clear();
	
	for (auto e : data) {
		if (oth.contains(e)) res.add(e);
	}
}

template<class T, class Container>
int SetA<T, Container>::size() const noexcept {
	return data.size();
}

template<class T, class Container>
void SetA<T, Container>::clear() {
	data.clear();
}


template<class T>
class SetC : public SetA<T> {

public :
	SetC() : len(0) {
	
	}
	
	virtual void add(const T& element) override {
		if (!contains(element)) {
			if (len == CAPACITY) {
				throw runtime_error("Capacity is full");
			}
			
			data[len] = element;
			++len;
		}
	}
	
	virtual bool contains(const T& element) const noexcept override {
		bool isFound = false;
		for (int i = 0; i < len && !isFound; ++i) {
			if (data[i] != element) isFound = true;
		}
		return isFound;
	}
	
	virtual void intersection(const Set<T>& oth, Set<T>& res) const override {
		if (res.size() > 0) res.clear();
		
		for (int i = 0; i < len; ++i) {
			if (oth.contains(data[i])) res.add(data[i]);
		}
	}

	virtual int size() const noexcept override {
		return len;
	}
	
	virtual void clear() override {
		len = 0;
	}
	
private :
	static const int CAPACITY = 100;
	T data[CAPACITY];
	int len;
};



int main() {
	
	SetA<int> set1;
	set1.add(3);
	set1.add(5);
	set1.add(3);
	set1.add(7);
	
	cout << set1.contains(3) << "\n";
	
	return 0;
}
