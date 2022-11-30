#include <iostream>
#include <cctype>	// isdigit, isalpha fonksiyonlari icin !!!!!!
using namespace std;


namespace {
	int digitToInt(char c) {
		return (int(c) - int('0'));
	}
	
	void readMinute(istream& istream, int &minute) {
		char c1, c2;
		istream >> c1 >> c2;
		
		if (! (isdigit(c1) && isdigit(c2)) ) {	// Ikisi de digit mi diye inputlari kontrol et !!
			cerr << "ERROR : Illegal input in readMinute\n";
			exit(-1);
		}
	
		minute = digitToInt(c1)*10 + digitToInt(c2);
		
		if (minute < 0 || minute > 59) {	// Minute icin kontrol et !!
			cerr << "ERROR : Illegal input in readMinute\n";
			exit(-1);
		}
	}
	
	void readHour(istream& istream, int& hour) {
		char c1, c2;
		istream >> c1 >> c2;
		
		/* Input kontrolu yap : 10:02 veya 1:02 girilmis olabilir.   */
		if (! (isdigit(c1) && (isdigit(c2) || c2 == ':')) ) {
			cerr << "Invalid argument for readHour.\n";
			exit(-1);
		}
		
		if (c2 == ':') {
			hour = digitToInt(c1);
		}
		else {
			hour = digitToInt(c1)*10 + digitToInt(c2);
			
			istream >> c2;	// Iki noktayi'da okumam lazim bunu oku ve ':' olup olmadigini kontrol et !!!
			if (c2 != ':') {
				cerr << "Invalid argument for readHour.\n";
				exit(-1);
			}
		}
		
		if (hour == 24) hour = 0; // saat 24 ise 0'a set et. !!!
		if (hour < 0 || hour > 23) {
			cerr << "Invalid argument for readHour.\n";
		}
	}
	
}


namespace GTUTime {
	
	class DigitalTime {
		
	public :
		DigitalTime(int hour_, int minute_);
		DigitalTime();
		
		int getHour() const;
		int getMinute() const;
		
		void advance(int minutesAdded);
		void advance(int hoursAdded, int minutesAdded);
		
		bool operator==(const DigitalTime& oth) const;
		
		friend ostream& operator<<(ostream& ostream, const DigitalTime& time);
		friend istream& operator>>(istream& istream, DigitalTime& time);
		
	private :
		int hour;
		int minute;
		
	};
	
	DigitalTime::DigitalTime() : hour(0), minute(0) {
	}
	
	DigitalTime::DigitalTime(int hour_, int minute_) {
		if (! (0<=hour_ && hour_<=24 && 0<=minute_ && minute_<=59)) {
			cerr << "Invalid argument.\n";
			exit(-1);
		}
		if (hour_ == 24) hour = 0;	// Saat 24 olarak verilebilir biz bunu 0 olarak set ederiz. !!!
		else hour = hour_;
		minute = minute_;
	}
	
	int DigitalTime::getHour() const { return hour; }
	int DigitalTime::getMinute() const { return minute; }
	
	void DigitalTime::advance(int minutesAdded) {
		int totalMinutes = minute + minutesAdded;
		
		minute = totalMinutes % 60;
		hour += totalMinutes / 60;
		hour = hour % 24;
	}
	
	void DigitalTime::advance(int hoursAdded, int minutesAdded) {
		advance(minutesAdded);
		hour = (hour + hoursAdded) % 24;
	}
	
	ostream& operator<<(ostream& ostream, const DigitalTime& time) {
		ostream << time.hour << ":";
		if (time.minute < 10) ostream << "0";
		ostream << time.minute;
		return ostream;
	}
	
	istream& operator>>(istream& istream, DigitalTime& time) {
		readHour(istream, time.hour);
		readMinute(istream, time.minute);
	}
	
}

using namespace GTUTime; 	// NAMESPACE'I MAINDEN ONCE KULLANMAYI UNUTMA !!!!!!!!
int main () {
	DigitalTime time;
	cin >> time;
	
	time.advance(30);
	cout << time;
	
	return 0;
}
