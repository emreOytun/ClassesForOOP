#include <iostream>
#include <vector>
using namespace std;

class DayOfYear {
	public :
		DayOfYear();
		DayOfYear(int day, int month);
		DayOfYear(const DayOfYear& oth);
		~DayOfYear();
		
		DayOfYear operator=(const DayOfYear& oth);
		bool operator==(const DayOfYear& oth) const;
		bool operator!=(const DayOfYear& oth) const;
		DayOfYear& operator++();
		DayOfYear operator++(int);
		DayOfYear& operator--();
		DayOfYear operator--(int);
		
		friend ostream& operator<<(ostream& ostream, const DayOfYear& date);
		friend istream& operator>>(istream& istream, DayOfYear& date);
		
		static int activeObjectsNum();
		static bool isValidDate(int day, int month);
		static const int dayNumOfMonths[12];
		
	private :
		int day;
		int month;
		static int activeObjects;
};

int DayOfYear::activeObjects = 0;
const int DayOfYear::dayNumOfMonths[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool DayOfYear::isValidDate(int day, int month) {
	bool result = true;
	if (!(1<=month && 12<=month)) result = false;
	else if (day<=0 || day>=dayNumOfMonths[month-1]) result = false;
	
	return result;
}

DayOfYear::DayOfYear() : day(1), month(1) {
	++activeObjects;
}

DayOfYear::DayOfYear(int day, int month) {
	if (isValidDate(day, month)) {
		this->day = day;
		this->month = month;
		++activeObjects;
	}
	else {
		cerr << "Invalid arguments!";
		exit(-1);
	}
}

DayOfYear::DayOfYear(const DayOfYear& oth) {
	if (this != &oth) {
		day = oth.day;
		month = oth.month;	
		++activeObjects;
	} 
}

DayOfYear::~DayOfYear() {
	--activeObjects;
}

DayOfYear DayOfYear::operator=(const DayOfYear& oth) {
	if (this != &oth) {
		day = oth.day;
		month = oth.month;
	}
}

bool DayOfYear::operator==(const DayOfYear& oth) {
	if (this == &oth) return true;
	if (day == oth.day && month == oth.month) return true;
	return false;
}

bool DayOfYear::operator!=(const DayOfYear& oth) {
	return !((*this)==oth);
}

DayOfYear& DayOfYear::operator++() {
	if (day == dayNumOfMonths[month-1]) {
		day = 1;
		if (month == 12) month = 1;
		else ++month;
	}	
	
	else ++day;
}

DayOfYear DayOfYear::operator++(int) {
	DayOfYear copy = (*this);
	++(*this);
	return copy;
}

DayOfYear& DayOfYear::operator--() {
	if (day == 1) {
		if (month == 1) month = 12;
		else --month;
		
		day = dayNumOfMonths[month-1];
	}
	
	else --day;
}

DayOfYear DayOfYear::operator--(int) {
	DayOfYear copy = (*this);
	--(*this);
	return copy;
}

ostream& operator<<(ostream& ostream, const DayOfYear& oth) {
	ostream << oth.day << "/" << oth.month;
	return ostream;
}

istream& operator>>(istream& istream, DayOfYear& oth) {
	istream >> oth.day >> oth.month;
	return istream;
}

int DayOfYear::activeObjectsNum() { 
	return activeObjects;
}


/***********************************/

class DayOfYearSet {
	
public :	
	/* Alive obje sayisini tutmak icin default constructor ve destructor'da muhakkak yazilmak zorunda !!!! */
	DayOfYearSet();	
	DayOfYearSet(vector<DayOfYear> list);
	DayOfYearSet(const DayOfYearSet& oth);
	~DayOfYearSet();
	
	void add(const DayOfYear& newDate);
	void remove(int idx);
	int size() const;
	
	friend ostream& operator<<(ostream& ostream, const DayOfYearSet& set);	
	bool operator==(const DayOfYearSet& oth);
	bool operator!=(const DayOfYearSet& oth);
	
	DayOfYear& operator[](int idx);
	const DayOfYear& operator[](int index) const;
	
	const DayOfYearSet operator+(const DayOfYearSet& oth);
	const DayOfYearSet operator-(const DayOfYearSet& oth);
	const DayOfYearSet operator^(const DayOfYearSet& oth);
	
	friend const DayOfYearSet operator!(const DayOfYearSet& oth);
	
	static int numOfAliveObjects(); 
	
private :
	DayOfYear* data;	// Pointer'in varsa BIG THREE YAZILMAK ZORUNDA : 1) Copy constructor 2) Assignment(=) operator 3) Destructor
	int len;
	int capacity;
	static int aliveObjects;
	void adjustCapacity(int newCapacity);
};

int DayOfYearSet::aliveObjects = 0;
int DayOfYearSet::numOfAliveObjects() {
	return DayOfYearSet::aliveObjects;
}

DayOfYearSet::DayOfYearSet() : len(0), capacity(10), data(nullptr) {
	adjustCapacity(10);
	++aliveObjects;
}
	
DayOfYearSet::DayOfYearSet(vector<DayOfYear> list) {
	for (auto element : list) {
		add(element);
	}
	++aliveObjects;
}
	
DayOfYearSet::DayOfYearSet(const DayOfYearSet& oth) {
	for (int i = 0; i < oth.len; ++i) {
		add(oth[i]);
	}
	++aliveObjects;
}

DayOfYearSet::~DayOfYearSet() {
	delete [] data;
	data = nullptr;	// DELETE ETTIKTEN SONRA DATA = NULLPTR OLARAK SET ET !!!!
	--aliveObjects;
}

void DayOfYearSet::add(const DayOfYear& newDate) {
	/* SET YAZDIGIN ICIN EKLEME YAPARKEN ELEMANIN ONCEDEN OLUP OLMADIGINI KONTROL ET !!!! */
	bool canAdded = true;
	for (int i = 0; i < len && canAdded; ++i) {
		if (data[i] == newDate) canAdded = false;
	} 
	
	if (canAdded) {
		/* Eklemeden once capacity'i kontrol et !!! */
		if (len == capacity) {
			adjustCapacity(capacity*2);
		}
		data[len] = newDate;
		++len;
	}
}

void DayOfYearSet::adjustCapacity(int newCapacity) {
	DayOfYear* newData = new DayOfYear[newCapacity];
	for (int i = 0; i < len; ++i) {
		newData[i] = data[i];
	}
	if (data != nullptr) delete [] data;	// DELETE ETMEDEN ONCE NULLPTR OLUP OLMADIGINI KONTROL ET !!!
	data = newData;
	capacity = newCapacity;
}

void DayOfYearSet::remove(int idx) {
	/* Index'i kontrol ediyorum. */
	if (idx<0 || idx>=len) {
		cerr << "ERROR: Invalid index argument.";
		exit(-1);
	}
	
	/* Kaydirma yapiyorum. */
	for (int i = idx+1; i < len; ++i) {
		data[i-1] = data[i];
	}
	
	/* Len'i azaltip capacity'i dusurmem gerkeip gerekmedigini kontrol ediyorum. */
	--len;
	if (len%10 == 0) {
		adjustCapacity(len);
	}
}

ostream& operator<<(ostream& ostream, const DayOfYearSet& set) {
	for (int i = 0; i < set.len; ++i) {
		ostream << set.data[i] << "\n";
	}	
	return ostream;
}

bool DayOfYearSet::operator==(const DayOfYearSet& oth) {
	if (this == &oth) return true;
	bool res = true;
	for (int i = 0; i < len && res; ++i) {
		if (data[i] != oth[i]) res = false;
	}
	return res;
}

bool DayOfYearSet::operator!=(const DayOfYearSet& oth) {
	return !(*this == oth);
}

const DayOfYear& DayOfYearSet::operator[](int idx) const {
	/* Index kontrolu yap !! */
	if (idx<0 || idx>=len) exit(-1);
	return data[idx];
}

DayOfYear& DayOfYearSet::operator[](int idx) {
	if (idx<0 || idx>=len) exit(-1);
	return data[idx];
}

/* Union : 
	1) Get the copy of *this object into the unionSet.
	2) For each DayOfYear object in the other set, check if it's not in the unionSet.
	3) If it's not in the unionSet, then add it.
*/
const DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet& oth) {
	DayOfYearSet unionSet(*this);

	for (int i = 0; i < oth.len; ++i) {
		bool canAdded = true;
		for (int j = 0; j < len && canAdded; ++j) {
			if (data[j] == oth[i]) canAdded = false;
		}
		if (canAdded) unionSet.add(oth[i]);
	}

	return unionSet;
}

/* Difference : 
	1) Bu objeyi diffSet'e kopyala.
	2) Other set uzerinde gez, oth setteki bir obje diffSet'tede varsa bu objeyi sil.
*/
const DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet& oth) {
	DayOfYearSet diffSet(*this);
	
	for (int i = 0; i < oth.len; ++i) {
		bool canRemove = false;
		int removeIdx = -1;
		for (int j = 0; j < diffSet.len && !canRemove; ++j) {
			if (diffSet[j] == oth[i]) {
				canRemove = true;
				removeIdx = j;	
			}
		}
		if (canRemove) diffSet.remove(removeIdx);
	}

	return diffSet;
}

/* Intersection : Her ikisi uzerinde de gez, elemanin ortak olup olmadigini bul. Ortaksa interSet'e ekle. */
const DayOfYearSet DayOfYearSet::operator^(const DayOfYearSet& oth) {
	DayOfYearSet interSet;
	
	for (int i = 0; i < len; ++i) {
		bool canAdded = false;
		for (int j = 0; j < oth.len && !canAdded; ++j) {
			if (data[i] == oth.data[j]) canAdded = true; 
		}
		if (canAdded) interSet.add(data[i]);
	}
	
	return interSet;
}


/* Test driver : */
int main () {
	
	DayOfYear d1(1, 12);
	cout << "Active objects : " << DayOfYear::activeObjectsNum() << "\n";
	cout << d1 << "\n";
	cout << ++d1 << "\n";
	cout << --d1 << "\n";
	cout << d1++ << "\n";
	cout << d1-- << "\n";
	cout << d1 << "\n";
	
	DayOfYear d2 = d1;
	cout << "Active objects : " << DayOfYear::activeObjectsNum() << "\n";
	cout << "d1 : " << d1 << "\n";
	cout << "d2 : " << d2 << "\n";
	
	if (d1 == d2) {
		cout << "d1 is equal to d2\n";
	}
	else {
		cout << "d1 is not equal to d2\n";
	}
	
	if (true) {
		DayOfYear newObject;
		cout << "Active objects : " << DayOfYear::activeObjectsNum() << "\n";
	} 
	cout << "Active objects : " << DayOfYear::activeObjectsNum() << "\n";
	
	cin >> d1;
	cout << "d1 : " << d1 << "\n";
	
	
	return 0;
}
