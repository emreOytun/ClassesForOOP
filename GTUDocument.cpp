#include <iostream>
#include <vector>
#include <map>
#include <string> // to_string; stoi,stof,stod functions
#include <stdexcept> // for exceptions
using namespace std;

template<class T>
class GTUDocument {

public:
	virtual ~GTUDocument() = default;
	
	virtual const T& at(int idx) const = 0;
	virtual T& at(int idx) = 0;
	virtual int find(const T& line) const = 0; 
	virtual void insert(const T& line) = 0;
};



class GTUEmail : public GTUDocument<string> {
	
public:
	virtual const string& at(int idx) const override {
		if (idx < 0 || idx >= lines.size()) {
			throw runtime_error("Invalid index");
		}
	
		return lines[idx];
	}
	
	virtual string& at(int idx) override {
		if (idx < 0 || idx >= lines.size()) {
			throw runtime_error("Invalid index");
		}
	
		return lines[idx];
	}
	
	virtual int find(const string& line) const override {
		bool isFound = false;
		int idx = -1;
		
		for (int i = 0; i < lines.size() && !isFound; ++i) {
			if (lines[i] == line) {
				isFound = true;
				idx = i;
			}
		}
		
		if (!isFound) {
			throw runtime_error("Not found");
		}
		
		return idx;
	}
	
	virtual void insert(const string& line) override {
		lines.push_back(line);
	} 


private :
	vector<string> lines;
};


class GTUDictionary : public GTUDocument<string> {
	
public :
	
	virtual void insert(const string& line) override {
		string key = to_string(keyLineMap.size()); // to keep the insertion order, give them ascending(artan in Turkish) keys according to the map size.
		keyLineMap[key] = line;
	}
	
	virtual const string& at(int idx) const override {
		string key = to_string(idx); // From number to string
		auto it = keyLineMap.find(key);
		
		if (it == keyLineMap.end()) {
			throw runtime_error("Invalid index");
		}
		
		return keyLineMap.at(key);
	}
	
	virtual string& at(int idx) override {
		string key = to_string(idx); // From number to string
		auto it = keyLineMap.find(key);
		
		if (it == keyLineMap.end()) {
			throw runtime_error("Invalid index");
		}
		
		return keyLineMap[key];
	}
	
	virtual int find(const string& line) const override {
		
		bool isFound = false;
		string key;
		
		for (auto it = keyLineMap.begin(); it != keyLineMap.end() && !isFound; ++it) {
			const pair<string, string>& p = *it;
			if (p.second == line) {
				key = p.first;
				isFound = true;
			}
		}
		
		if (!isFound) {
			throw runtime_error("Not found");
		}
		
		return stoi(key); // stoi, stof, stod functions: From string to number
		
	}

private :
	map<string, string> keyLineMap;
};

int main () {
	
	GTUDictionary d1;
	d1.insert("Emre Oytun");
	d1.insert("Ali Veli");
	
	cout << d1.find("Emre Oytun") << "\n";
	cout << d1.find("Ali Veli") << "\n";
	
	cout << d1.at(0) << "\n";
	cout << d1.at(1) << "\n";
	
	return 0;	
}
