#include <iostream>
#include <vector>
using namespace std;

class Person {

public :
	Person();
	Person(const string& fullName, const string& identityNo, const string& birthDate); 
	
	Person(const Person& oth);
	const Person& operator = (const Person& oth);
	~Person();
	
	void setIdentityNo(const string& identityNo);	/* Since copying the string could be expensive, put const& there. */
	void setBirthDate(const string& birthDate);
	void setName(const string& name);
	
	const string& getName() const;	/* Since it'll return a data member it can return reference, because it's not local. */
	const string& getIdentityNo() const;
	const string& getBirthDate() const;

private :
	string fullName;
	string identityNo;
	string birthDate;
	string* readBooks;
};

Person::Person() : readBooks(nullptr) {
	cout << "Person " + fullName + " default constructor\n";
}

Person::Person(const string& fullName, const string& identityNo, const string& birthDate) : fullName(fullName), readBooks(nullptr) {
	setIdentityNo(identityNo);
	setBirthDate(birthDate);
	cout << "Person " + fullName + " parameter constructor\n";
}

Person::Person(const Person& oth) : readBooks(nullptr) {
	cout << "Person " + fullName + " copy constructor\n";
}

const Person& Person::operator= (const Person& oth) {
	cout << "Person " + fullName + " assignment operator\n";
}  

Person::~Person() {
	if (readBooks != nullptr) delete [] readBooks;
	cout << "Person " + fullName + " destructor\n";
}

void Person::setIdentityNo(const string& identityNo_) {
	if (identityNo_.length() == 11) identityNo = identityNo_;
	else exit(-1); 
}

void Person::setBirthDate(const string& birthDate_) {
	birthDate = birthDate_;
}

void Person::setName(const string& name_) {
	fullName = name_;
}

const string& Person::getName() const {
	return fullName;
}

const string& Person::getIdentityNo() const {
	return identityNo;
}

const string& Person::getBirthDate() const {
	return birthDate;
}

class Student : public Person {

public : 
	Student();
	Student(const string& fullName, const string& identityNo, const string& birthDate);
	Student(const string& fullName, const string& identityNo, const string& birthDate,
	 		const vector<string>& lessons, const vector<double>& grades);
	
	/* Copy constructor and assignment operator MUST be written since base class's copy const. and assignment operator not called by default. */
	Student(const Student& oth);
	const Student& operator = (const Student& oth);
	
	/* No need to write destructor for base class since it'll be called after destruction of this class's object. */
	~Student();
	
private : 
	vector<double> grades;	
	vector<string> lessons;
};

Student::Student() {
	cout << "Student default constructor\n";
}

Student::Student(const string& fullName, const string& identityNo, const string& birthDate) : Student() {		
	cout << "Student " + getName() + " parameter constructor1\n";	
}

Student::Student(const string& fullName, const string& identityNo, const string& birthDate,
	 		const vector<string>& lessons, const vector<double>& grades) : Person(fullName, identityNo, birthDate), lessons(lessons), grades(grades) {
	cout << "Student " + getName() + " parameter constructor2\n";
}

Student::Student(const Student& student) : Person(student) {
	cout << "Student " + getName() + " copy constructor\n";
}

const Student& Student::operator =(const Student& oth) {
	Person::operator =(oth);
	cout << "Student " + getName() + " destructor\n";
}

Student::~Student() {
	cout << "Student " + getName() + " destructor\n";
}

int main () {
	Student s1;	
	cout << "---------\n";
	
	Student s2("Emre Oytun", "12345678911", "2001");
	cout << "---------\n";

	Student s3(s1);
	cout << "----------\n";
}



