#include <iostream>
using namespace std;

// UNNAMED NAMESPACE : It can be seen only from this .cpp file.
namespace {
	int dollarsPart(double amount);
	int centsPart(double amount);
	int round(double num);
	double fraction(double percent);

	
	int dollarsPart(double amount) {
		return static_cast<int>(amount);
	}
	
	int centsPart(double amount) {	// Converts to cents first, then get the cents part.
		int totalCents = amount*100;
		int cents = totalCents % 100;
		return cents;
	}
	
	int round(double num) {
		int dollars = dollarsPart(num);
		int cents = centsPart(num);
		if (cents < 50) return dollars;
		else return dollars+1;
	}
	
	double fraction(double percent) {
		return percent*0.01;
	}
}

namespace GTU {

	class BankAccount {
		
	public :
		
		BankAccount();	
		BankAccount(double amount, double rate);
		BankAccount(int dollars, int cents, double rate);
		BankAccount(int dollars, double rate);
		
		void update();
		void input();
		
		string toString() const;
		void output() const;
			
		double getBalance() const;
		double getRate() const;
		int getDollars() const;
		int getCents() const;
		
		void setBalance(double balance);
		void setBalance(int dollars, int cents);
		void setRate(double newRate);
		
		bool operator==(const BankAccount& oth) const; // If operator does not change any members, then put 'const' !!
		bool operator!=(const BankAccount& oth) const;
		bool operator>(const BankAccount& oth) const;
		const BankAccount operator+(const BankAccount& oth) const;
		
		friend const BankAccount operator!(const BankAccount& oth);	// They must be global since the object will be at the right part of the operator !!
		friend const BankAccount operator-(const BankAccount& oth); 
		
		friend ostream& operator<<(ostream& ostream, const BankAccount& acc);
		friend istream& operator>>(istream& istream, BankAccount& acc);
		
	private : 
		/* If amount is negative, both dollars and cents parts are negative. */
		int accountDollars;
		int accountCents;
		double rate;
	
	};
	
	BankAccount::BankAccount() : accountDollars(0), accountCents(0) {
		setRate(rate);	// setRate is used since we should check the validity of rate. !!
	}
	
	BankAccount::BankAccount(double amount, double rate) : accountDollars(dollarsPart(amount)), accountCents(centsPart(amount)) {
		setRate(rate);
	}
	
	BankAccount::BankAccount(int dollars, int cents, double rate) : accountDollars(dollars), accountCents(cents) {
		setRate(rate);
	}
	
	BankAccount::BankAccount(int dollars, double rate) : accountDollars(dollars) {
		setRate(rate);
	}
	
	void BankAccount::setBalance(double balance) {
		accountDollars = dollarsPart(balance);
		accountCents = centsPart(balance);
	}
	
	void BankAccount::setBalance(int dollars, int cents) {
		accountDollars = dollars;
		accountCents = cents;
	}
	
	/* Check if rate is negative first, then assign !! */
	void BankAccount::setRate(double newRate) {
		if (newRate < 0) {
			cerr << "ERROR Rate is negative.\n";
			exit(-1);
		}
		rate = newRate;
	}
	
	double BankAccount::getBalance() const {
		return accountDollars + accountCents*0.01;
	}
	
	double BankAccount::getRate() const {
		return rate;
	}
	
	int BankAccount::getDollars() const {
		return accountDollars;
	}
	
	int BankAccount::getCents() const {
		return accountCents;
	}
	
	void BankAccount::update() {
		double balance = getBalance();
		double newBalance = balance * rate;
		accountDollars = dollarsPart(newBalance);
		accountCents = centsPart(newBalance);
	}
	
	string BankAccount::toString() const {
		int absDollars = abs(accountDollars);
		int absCents = abs(accountCents);
		
		string res = "";
		res += "Account Balance : $";
		if (accountDollars<0 || accountCents<0) {
			res += "-";
		} 
		res += to_string(absDollars) + "." + to_string(absCents) + "\n";
		res += "Rate: " + to_string(rate) + "%\n";
	
		return res;
	}
	
	void BankAccount::output() const {
		cout << toString();
	}
	
	void BankAccount::input() {
		double amount;
		cout << "Enter an amount : ";
		cin >> amount;
		accountDollars = dollarsPart(amount);
		accountCents = centsPart(amount);
	}
	
	bool BankAccount::operator==(const BankAccount& oth) const {
		if (this == &oth) return true;
		if (accountDollars == oth.accountDollars && accountCents == oth.accountCents) return true;
		return false;
	}
	
	bool BankAccount::operator!=(const BankAccount& oth) const {
		return !(*this == oth);
	}
	
	bool BankAccount::operator>(const BankAccount& oth) const {
		if (accountDollars > oth.accountDollars) return true;
		if (accountDollars == oth.accountDollars && accountCents > oth.accountCents) return true;
		return false;
	}
	
	const BankAccount BankAccount::operator+(const BankAccount& oth) const {
		int firstCents = accountDollars*100 + accountCents;
		int secondCents = oth.accountDollars*100 + oth.accountCents;
		int totalCents = firstCents + secondCents;
		
		int newDollars = totalCents / 100;
		int newCents = totalCents % 100;
		return BankAccount(newDollars, newCents, rate);
	}
	
	const BankAccount operator!(const BankAccount& acc) {
		BankAccount newAccount(-acc.accountDollars, -acc.accountCents, acc.rate);
		return newAccount;
	}
	
	ostream& operator<<(ostream& ostream, const BankAccount& acc) {
		ostream << acc.toString();
		return ostream;
	}
	
	istream& operator>>(istream& istream, BankAccount& acc) {
		istream >> acc.accountDollars >> acc.accountCents;
		return istream;
	}
	
	const BankAccount operator-(const BankAccount& oth) {
		return !oth;
	}

}

using namespace GTU;
int main () {
	const BankAccount acc1(1.50, 0.21);
	acc1.output();
	cout << "\n";
	
	cout << -acc1 << "\n";
	cout << !acc1 << "\n";
	
	const BankAccount acc2(-1.50, 0.21);
	cout << acc1 + acc2 << "\n";
	cout << acc1 + acc2 + acc1 + acc2 + acc2 << "\n";
	
	return 0;
}

