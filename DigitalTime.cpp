#include <iostream>
#include <cctype> // for ctype functions like 'isalpha', 'isdigit' etc.
#include <stdexcept> // for exceptions
using namespace std;

namespace {
	
	int digitToInt(char ch) {
		return (int) ch - (int) '0';
	}
	
	int readHour(istream& istream, int& hour) {
		char ch1, ch2;
		istream >> ch1 >> ch2;
	
		/* Input can be in formats of 13:13 or 1:12.  */	
		if (! (isdigit(ch1) && (isdigit(ch2) || ch2 == ':')) ) {
			throw runtime_error("Invalid time!");
		} 
	
		if (isdigit(ch2)) {
				
			/* If input is in format of 13:13, then we can be able to read ':' */
			char ch3;
			istream >> ch3;
			if (ch3 != ':') {
				throw runtime_error("Invalid time!");
			}
		
			hour = digitToInt(ch1) * 10 + digitToInt(ch2);
			if (hour == 24) hour = 0;
		}
		
		/* If input is in format of 2:23 */
		else {
			hour = digitToInt(ch1);
		}
		
		if (hour < 0 || hour > 23) {
				throw runtime_error("Invalid time!");
		}
		
		return hour;
	}
	
	int readMinute(istream& istream, int& minute) {
		char ch1, ch2;
		istream >> ch1 >> ch2;
		
		/* Check if both of them are digits. */
		if (! (isdigit(ch1) && isdigit(ch2))) {
			throw runtime_error("Invalid time!");
		}
		
		minute = digitToInt(ch1) * 10 + digitToInt(ch2);
		if (minute < 0 || minute > 59) {
			throw runtime_error("Invalid time!");
		}
	
		return minute;
	}
	
}


namespace GTUTime {
	
	class DigitalTime {
		
	public :
		DigitalTime();
		DigitalTime(int hour_, int minute_);
		
		void setTime(int hour_, int minute_);
		void setHour(int hour_);
		void setMinute(int minute_);
		
		int getHour() const noexcept;
		int getMinute() const noexcept;
		
		void advance(int hoursAdded);
		void advance(int hoursAdded, int minutesAdded);
		
		friend ostream& operator<<(ostream& ostream, const DigitalTime& time);
		friend istream& operator>>(istream& istream, DigitalTime& time);
		
	private :
		int hour;
		int minute;
		
	};
		
}

namespace GTUTime {
	
	DigitalTime::DigitalTime() : hour(0), minute(0) {
		
	}
	
	DigitalTime::DigitalTime(int hour_, int minute_) {
		setTime(hour_, minute_);
	}
	
	void DigitalTime::setTime(int hour_, int minute_) {
		if (hour_ < 0 || hour_ > 24 || minute_ < 0 || minute_ > 59) {
			throw runtime_error("Invalid arguments!");
		}
		
		if (hour_ == 24) hour_ = 0;
		hour = hour_;
		minute = minute_;
	}

	void DigitalTime::setHour(int hour_) {
		if (hour_ < 0 || hour_ > 24) {
			throw runtime_error("Invalid arguments!");
		}
		
		if (hour_ == 24) hour = hour_;
	}
	
	void DigitalTime::setMinute(int minute_) {
		if (minute_ < 0 || minute_ > 59) {
			throw runtime_error("Invalid arguments!");
		}
		
		minute = minute_;
	}
	
	int DigitalTime::getHour() const noexcept {
		return hour;
	}
	
	int DigitalTime::getMinute() const noexcept{
		return minute;
	}
	
	void DigitalTime::advance(int hoursAdded) {
		hour += hoursAdded;
		if (hour >= 24) {
			hour %= 24;
		}
	}
	
	void DigitalTime::advance(int hoursAdded, int minutesAdded) {
		advance(hoursAdded);
		minute += minutesAdded;
		if (minute >= 60) {
			hour += minute / 60;
			minute %= 60;
		}
	}
	
	ostream& operator<<(ostream& ostream, const DigitalTime& time) {
		ostream << time.hour << ":";
		if (time.minute < 10) ostream << "0" << time.minute;
		else ostream << time.minute;
		
		return ostream;
	}
	
	istream& operator>>(istream& istream, DigitalTime& time) {
		readHour(istream, time.hour);
		readMinute(istream, time.minute);	
	}
	
}

/* Testing */
using namespace GTUTime;

int main () {
	DigitalTime time1(13, 23);	
	cout << time1 << "\n"; // 13:23
	
	time1.advance(3);
	cout << time1 << "\n"; // 16:23
	
	
	DigitalTime time2;
	cout << time2 << "\n"; // 0:00
	
	cin >> time2;
	cout << time2 << "\n";
	
}
