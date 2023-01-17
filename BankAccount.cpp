#include <iostream>
using namespace std;

// UNNAMED NAMESPACE : SADECE BU CPP DOSYASI ICINDEN GORULEBILEN, GENELLIKLE SADECE BU DOSYADA KULLANACAGIMIZ HELPER FONKSIYONLARI ICIN KULLANILIR.
namespace {
	int dollarsPart(double amount);
	int centsPart(double amount);
	int round(double num);
	double fraction(double percent);

	
	int dollarsPart(double amount) {
		return static_cast<int>(amount);
	}
	
	int centsPart(double amount) {	// Once kr'a cevir, ordan kurus kismini bulabilirsin !!!
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

namespace GTU {	// HEM HEADER'DA HEM CPP DOSYASINDA KODUNU NAMESPACE ICINE YAZACAKSIN.

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
		
		bool operator==(const BankAccount& oth) const;	// ONEMLI: Operator nesnenin datasini degistirmiyorsa const olarak isaretle !!!!!
		bool operator!=(const BankAccount& oth) const;
		bool operator>(const BankAccount& oth) const;
		
		const BankAccount operator+(const BankAccount& oth) const; // ONEMLI: Operatoru const olarak isaretlemen lazim ki const obje icinde calisabilsin veya concate toplama islemi yapabilsin !!!
		
		friend const BankAccount operator!(const BankAccount& oth);	// Burada nesne sag tarafa gelecegi icin global operatorler olmali !!!!
		friend const BankAccount operator-(const BankAccount& oth); 
		
		friend ostream& operator<<(ostream& ostream, const BankAccount& acc);
		friend istream& operator>>(istream& istream, BankAccount& acc);
		
	private : 
		/* If amount is negative, both dollars and cents parts are negative. */
		int accountDollars;
		int accountCents;
		double rate;
	
	};
	
	/* Constructorlarda DIKKAT : RATE NEGATIF OLAMAZ, SETTER'DA KONTROL EDILMELI VE SETTER KULLANILMALI !!! */
	BankAccount::BankAccount() : accountDollars(0), accountCents(0) {
		setRate(rate);
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
	
	/* Rate'in negatif olmamasi gerekiyor, CHECK ET !! */
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
	
	const BankAccount BankAccount::operator+(const BankAccount& oth) const {	// Once kuruslar toplamini bul, ordan dolar ve cent kismini bulursun !!!
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

using namespace GTU;	// EGER NAMESPACE ICINE YAZDIYSAN MAIN'DE BUNU KULLANICAKSIN !!
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

