#include <iostream>
#include <stdexcept>
#include <typeinfo>
using namespace std;

template<class T>
class GTUVector {
	
public :
	virtual ~GTUVector() = default;
	
	virtual void push_back(const T& element) = 0;
	virtual const T& at(int idx) const = 0;
	virtual int size() const noexcept = 0;
	virtual bool equal(const GTUVector<T>& oth) const noexcept = 0;	
	
};


template<class T>
class GTUVectorD : public GTUVector<T> {
	
public :
	GTUVectorD() : data(new T[10]), len(0), capacity(10) {
		
	}
	
	GTUVectorD(const GTUVectorD<T>& oth) : data(new T[oth.capacity]), len(oth.len), capacity(oth.capacity) {
		for (int i = 0; i < len; ++i) {
			data[i] = oth.data[i];
		}
	}
	
	const GTUVectorD<T>& operator=(const GTUVectorD<T>& oth) {
		if (this == &oth) return *this;
		
		if (data != nullptr) delete [] data;
		data = new T[oth.capacity];
		len = oth.len;
		capacity = oth.capacity;
		
		for (int i = 0; i < len; ++i) {
			data[i] = oth.data[i];
		}
		
		return *this;
	}
	
	GTUVectorD(GTUVectorD<T>&& oth) noexcept : data(oth.data), len(oth.len), capacity(oth.capacity) {
		oth.data = nullptr;
		oth.len = 0;
		oth.capacity = 0;
	}
	
	const GTUVectorD<T>& operator=(GTUVectorD<T>&& oth) {
		if (this == &oth) return *this;
		
		if (data != nullptr) delete [] data;
		data = oth.data;
		len = oth.len;
		capacity = oth.capacity;
		
		oth.data = nullptr;
		oth.len = 0;
		oth.capacity = 0;
		
		return *this;
	}
	
	virtual void push_back(const T& element) override {
		if (len == capacity) setCapacity(capacity*2);
		data[len] = element;
		++len;
	}	

	virtual const T& at(int idx) const override {
		if (idx < 0 || idx >= len) {
			throw runtime_error("Invalid index");
		}
		return data[idx];
	}	
	
	virtual int size() const noexcept override {
		return len;
	}
	
	virtual bool equal(const GTUVector<T>& oth) const noexcept override {
		if (this == &oth) return true;
		if (typeid(*this) != typeid(oth)) return false;
		
		const GTUVectorD<T>& othV = static_cast<GTUVectorD<T>>(oth);
		if (size() != othV.size()) return false;
		
		bool isEqual = true;
		for (int i = 0; i < len && isEqual; ++i) {
			if (data[i] != oth.data[i]) isEqual = false;
		}
	
		return isEqual;
	}
	
private :
	T* data;
	int len;
	int capacity;
	
	void setCapacity(int newCapacity) {
		if (newCapacity = 0) newCapacity = 10;
		
		T* newData = new T[newCapacity];
		for (int i = 0; i < len; ++i) newData[i] = data[i];
		if (data != nullptr) delete [] data;
		
		data = newData;
		capacity = newCapacity;
	}
};



