#include <iostream>
using namespace std;

class Employee {
	
public :
	Employee(const string& name, int age);
	virtual ~Employee();
	
	const string& getName() const;
	int getAge() const;
	
	void setName(const string& name_);
	void setAge(int age);
	
	virtual void printCheck() const = 0;
	
private :
	string name;
	int age;
};

Employee::Employee(const string& name, int age) : name(name) {
	setAge(age);	// Age should be checked before setting !
}

Employee::~Employee() {
	
}

const string& Employee::getName() const {
	return name;
}

int Employee::getAge() const {
	return age;
}

void Employee::setName(const string& name_) {
	name = name_;
}

void Employee::setAge(int age_) {
	if (age_ < 0) exit(-1);
	age = age_;
}

class HourlyEmployee : public Employee {
	
public :
	HourlyEmployee(const string& name, int age);
	HourlyEmployee(const string& name, int age, double wageRate, double hours);
	
	HourlyEmployee(const HourlyEmployee& oth);
	HourlyEmployee& operator=(const HourlyEmployee& oth);
	
	double getWageRate() const;
	double getHours() const;
	
	void setWageRate(double wageRate_);
	void setHours(double hours_);
	
	virtual void printCheck() const override;
	
private :
	double wageRate;
	double hours;
};

HourlyEmployee::HourlyEmployee(const string& name, int age) : Employee(name, age), wageRate(0), hours(0) {
	
}

HourlyEmployee::HourlyEmployee(const string& name, int age, double wageRate, double hours) : Employee(name, age) {
	setWageRate(wageRate);
	setHours(hours);
} 

HourlyEmployee::HourlyEmployee(const HourlyEmployee& oth) : Employee(oth) {
	wageRate = oth.wageRate;
	hours = oth.hours;
}

HourlyEmployee& HourlyEmployee::operator=(const HourlyEmployee& oth) {
	Employee::operator=(oth);
	wageRate = oth.wageRate;
	hours = oth.hours;
}

double HourlyEmployee::getHours() const {
	return hours;
}

double HourlyEmployee::getWageRate() const {
	return wageRate;
}

void HourlyEmployee::setHours(double hours_) {
	if (hours_ < 0) exit(-1);
	hours = hours_;
}

void HourlyEmployee::setWageRate(double wageRate_) {
	if (wageRate_ < 0) exit(-1);
	wageRate = wageRate_;
}

void HourlyEmployee::printCheck() const {
	cout 
	<< "Name : " << getName() << endl
	<< "Age : " << getAge() << endl
	<< "WageRate: " << wageRate << endl
	<< "Hours: " << hours << endl;
}

int main () {
	Employee *e1 = new HourlyEmployee("Emre", 21, 12, 40);
	e1->printCheck();
}





