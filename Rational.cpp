#include <iostream>
#include <algorithm>
using namespace std;

namespace {
	int gcd(int num1, int num2) {
		int absNum1 = abs(num1);
		int absNum2 = abs(num2);
		
		/* Buyuk olani numerator'a, kucuk olana denom'a koy. */
		int num, denom, rest;
		if (absNum1 > absNum2) {
			num = absNum1;
			denom = absNum2;
		}
		else {
			num = absNum2;
			denom = absNum1;
		}
		
		/* Num, denom, rest'in yerlerini rest==0 olmadigi surece kaydir ve tekrar dene. */
		int gcd = -1;
		bool isDone = false;
		while (!isDone) {
			rest = num % denom;
			if (rest == 0) {
				gcd = denom;
				isDone = true;
			}
			else {
				num = denom;
				denom = rest;
			}
		}
		
		return gcd;
	}
}

class Rational {
	
public :
	Rational(int _num = 0, int _denom = 1);	
	Rational(const Rational& oth);	// setDenominator denomanitor icin kullanilmali !!!!!!!!
	~Rational();
	const Rational operator=(const Rational& oth);
	
	void setNumerator(int _num);
	void setDenominator(int _denom);	// Denominator 0 olmamali !!!!!!!!
	void setRational(int _num, int _denom);
	
	int getNumerator() const;
	int getDenominator() const;
	
	void simplify();
	
	friend ostream& operator<<(ostream& ostream, const Rational& rational);
	
	bool operator==(const Rational& rational) const;
	bool operator!=(const Rational& rational) const;
	
	Rational& operator++();
	const Rational operator++(int);
	
	const Rational operator+(const Rational& oth) const;
	const Rational operator-(const Rational& oth) const;
	const Rational operator*(const Rational& oth) const;
	const Rational operator/(const Rational& oth) const;	// Bolen 0 olmamali !!!!!!
	
	friend const Rational operator-(const Rational& oth);
	
	static int numOfAliveObjects();
private :
	int num;
	int denom;
	void adjustSigns();	// Num ve denominator set edildikten sonra isareti ayarlamak icin cagrilacak.
	static int aliveObjects;
	
};

int Rational::aliveObjects = 0;
int Rational::numOfAliveObjects() { return aliveObjects; }

Rational::Rational(int num, int denom) : num(num) {
	setDenominator(denom);
	adjustSigns();
	++aliveObjects;
}

Rational::Rational(const Rational& oth) {
	num = oth.num;
	denom = oth.denom;
	++aliveObjects;
}

Rational::~Rational() {
	--aliveObjects;
}

void Rational::setNumerator(int _num) {
	num = _num;
	adjustSigns();
}

void Rational::setDenominator(int _denom) {
	if (_denom == 0) {
		cerr << "ERROR: Denominator cannot be 0.\n";
		exit(-1);
	}
	denom = _denom;
	adjustSigns();
}

void Rational::setRational(int _num, int _denom) {
	num = _num;
	setDenominator(_denom);	// Setdenominator kullanilmali !!!!!!
}

int Rational::getNumerator() const { return num; }
int Rational::getDenominator() const { return denom; }

void Rational::simplify() {
	int gcd_ = gcd(num, denom);
	num /= gcd_;
	denom /= gcd_;
}

ostream& operator<<(ostream& ostream, const Rational& rational) {
	ostream << rational.num << "/" << rational.denom;
	return ostream;
}

bool Rational::operator==(const Rational& oth) const{
	if (this == &oth) return true;
	if (num == oth.num && denom == oth.denom) return true;
	return false;
}

bool Rational::operator!=(const Rational& oth) const{
	return !(*this == oth);
}

Rational& Rational::operator++() {
	num += denom;
	return *this;
}

const Rational Rational::operator++(int) {
	Rational copy = *this;
	++(*this);
	return copy;
}

const Rational Rational::operator+(const Rational& oth) const {
	Rational res;
	if (denom == oth.denom) {
		res.setRational(num+oth.num, denom);
	}
	else {
		int num1 = num*oth.denom;
		int num2 = oth.num*denom;
		res.setRational(num1+num2, denom*oth.denom);
	}
	
	return res;
} 

const Rational Rational::operator-(const Rational& oth) const {
	return (*this + Rational(-oth.num, oth.denom));
}

const Rational Rational::operator*(const Rational& oth) const {
	return Rational(num*oth.num, denom*oth.denom);
}

const Rational Rational::operator/(const Rational& oth) const {
	if (oth.num == 0) {							// BOLERKEN BOLENIN NUMERATOR'I 0 OLMAMALI !!!!!!
		cerr << "ERROR: Cannot divide by 0.\n";
		exit(-1);
	}
	return Rational(num*oth.denom, denom*oth.num);
}

void Rational::adjustSigns() {
	if (denom < 0) {
		num *= -1;
		denom *= -1;
	}
}

int main () {	
	return 0;
}



