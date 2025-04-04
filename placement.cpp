// placement.cpp: Illustrates placement new
#include <new>	// Defines the standard, 1-arg placement new
#include <iostream>
#include <stddef.h>
using namespace std;

// A sample class to place in an array
// All its functions trace themselves to cout
class Thing {
	int m, n;
public:
	Thing(int i = 0, int j = 0) {
		m = i;
		n = j;
		cout << "Thing(" << m << "," << n << ") initialized\n";
	}
	~Thing() {
		cout << "Thing(" << m << "," << n << ") destroyed\n";
	}
	Thing(const Thing& t) : m(t.m), n(t.n) {
		cout << "Thing(" << m << "," << n << ") copied\n";
	}
	Thing& operator=(const Thing& t) {
		m = t.m;
		n = t.n;
		cout << "Thing(" << m << "," << n << ") assigned\n";
		return *this;
	}

	void* operator new (size_t nbytes, void* p) {
		return p;
	}

	//I dabble in the new...
	void* operator new(size_t nbytes, int i, string& s) { // This function is designed to prove that an overload can take multiple parameters like functions.
		void * ptr = malloc(nbytes); // Allocation of memory of the heap. Perhaps later we can replace this to use only designated memory. That is for a later test.
		if (ptr != NULL) { // C defined malloc so this must be NULL
			for (auto j = 0; j < i; ++j) 
				cout << "This is location " << j << ". This is to prove multiparam new." << endl; // This shows that the int passed in is indeed that int.
			printf("string in memory location: [%s]\n", s); // This shows the string passed in is in the same place. We can not express the string though.
		}
		return ptr; // we return the memory allocated in the first place.
	}

	void set_m(int new_m) {
		m = new_m;
		cout << "m assigned to " << m << endl;
	}
	void set_n(int new_n) {
		n = new_n;
		cout << "n assigned to " << n << endl;
	}
	friend ostream& operator<<(ostream& os, const Thing& t) {
		return os << '(' << t.m << ',' << t.n << ')';
	}
};

int main() {
	// Create an array of Things on the heap the naive way
	Thing* p1 = new Thing[5];
	for (int i = 0; i < 3; ++i) {
		p1[i].set_m(i + 1);
		p1[i].set_n(i + 2);
	}
	// Display and deallocate them
	for (int i = 0; i < 3; ++i)
		cout << p1[i] << ' ';
	cout << endl;
	delete[] p1;	// Clean up
	cout << "\n";

	// Now use placement new instead
	char* p2 = new char[sizeof(Thing) * 5];
	for (int i = 0; i < 3; ++i)
		new (p2 + i * sizeof(Thing)) Thing(i + 1, i + 2);
	for (int i = 0; i < 3; ++i)
		cout << *reinterpret_cast<Thing*>(p2 + i * sizeof(Thing)) << ' ';
	cout << endl;
	for (int i = 2; i >= 0; --i)
		reinterpret_cast<Thing*>(p2 + i * sizeof(Thing))->~Thing();
	

	// THIS is to test a multi input overload operator. It only proves the concept, it doesn't actually do a thing.
	int i = 1;
	string s1 = "test";
	printf("string in memory location: [%s]\n", s1);
	Thing* t = new (i,s1) Thing(0,0);
	cout << *reinterpret_cast<Thing*>(t) << endl;
	
	/*
	char placeHold;
	cin >> placeHold; // Holds console open for view.
	*/
}