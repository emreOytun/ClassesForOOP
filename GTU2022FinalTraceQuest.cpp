#include <iostream>
using namespace std;


class A {
	public :
		A() {
			cout << "const\n";
		}
		
		A(const A& oth) {
			cout << "copy const\n";
		}
		
		A(A&& oth) noexcept {
			cout << "move const\n";
		}
		
		const A& operator=(const A& oth) {
			cout << "copy assigned\n";
		}
		
		const A& operator=(A&& oth) {
			cout << "move assigned\n";
		}

		~A() {
			cout << "dest\n";
		}
};

A fun(A a) {
	return a;
}

int main () {
	
	A a1;
	a1 = fun(A());
	
	return 0;
}
