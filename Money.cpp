#include <iostream>
#include <cmath>

using namespace std;

namespace {
	int dollarsPart(double amount) {
		int totalCents = amount * 100;
		int dollars = totalCents / 100;
		return dollars;
	}
	 
	int centsPart(double amount) {
		int totalCents = amount * 100;
		int cents = totalCents % 100;
		return cents;
	}
	
	int round(double amount) {
		int dollars = dollarsPart(amount);
		int cents = centsPart(amount);
		if (cents >= 50) return dollars + 1;
		return dollars;
	}
		
}

namespace GTU {
	
	class Money {
		
	public :
		Money() : dollars(0), cents(0) {
						
		}
		
		Money(double amount) {
			setMoney(amount);
			setSigns();
		}
		
		Money(int dollars, int cents) {
			setMoney(dollars, cents);
		}
		
		void setMoney(double amount) {
			dollars = dollarsPart(amount);
			cents = centsPart(amount);
		}
		
		void setMoney(int dollars_, int cents_) {
			dollars = dollars_;
			cents = cents_;
			setSigns();		
		}
		
		void setDollars(int dollars_) {
			dollars = dollars_;
			setSigns();
		}
		
		void setCents(int cents_) {
			cents = cents_;
			setSigns();
		}
		
		double getAmount() const noexcept {
			return (double) dollars + cents / 100;
		}
		
		int getDollars() const noexcept {
			return dollars;
		}	
		
		int getCents() const noexcept {
			return cents;
		}
		
		
		bool operator==(const Money& oth) const noexcept {
			if (this == &oth) return true;
			if (dollars == oth.dollars && cents == oth.cents) return true;
		}
		
		bool operator!=(const Money& oth) const noexcept {
			return !(*this == oth);
		}
		
		bool operator<(const Money& oth) const noexcept {
			if (dollars < oth.dollars) return true;
			else if (dollars == oth.dollars && cents < oth.cents) return true;
			return false; 	
		}
		
		bool operator>(const Money& oth) const noexcept {
			return !(*this < oth);
		}
		
		
		const Money operator+(const Money& oth) const noexcept {
			Money newMoney(dollars + oth.dollars, cents + oth.cents);
			return newMoney;
		}
		
		const Money operator-(const Money& oth) const noexcept {
			Money newMoney(dollars - oth.dollars, cents - oth.cents);
			return newMoney;
		}
		
		
		friend const Money operator-(const Money& oth);
		friend ostream& operator<<(ostream& ostream, const Money& money);
		friend istream& operator>>(istream& istream, const Money& money);
		
		
	private : 
		int dollars;
		int cents;	
		
		/* Sets dollars and cents parts' signs to be the same. */
		void setSigns() {
			if (dollars * cents < 0) {
				if (dollars < 0) cents *= -1;
				else dollars *= -1;
			}
		}	
	};
	
	const Money operator-(const Money& money) {
		return Money(-money.dollars, -money.cents);
	}
	
	ostream& operator<<(ostream& ostream, const Money& money) {
		bool isNegative = false;
		if (money.dollars < 0 || money.cents < 0) isNegative = true;
		
		int absDollars = abs(money.dollars);
		int absCents = abs(money.cents);
		
		if (isNegative) ostream << "-";
		ostream << absDollars << "." << absCents;
		
		return ostream;
	}
	
}

/* Testing */
using namespace GTU;

int main () {

	Money m1(13.73);
	cout << m1 << "\n";	// 13.73
	
	Money m2(-2, 10);
	cout << m2 << "\n"; // -2.10
	
	cout << -m1 << "\n"; // -13.73
	cout << m1 + m2 << "\n"; // 11.63
	
	
	
	return 0;
}
