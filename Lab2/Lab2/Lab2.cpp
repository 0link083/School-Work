// Lab2.cpp
// 9/6/2021
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;
using std::cin;

void partA();
void partB();
void partC();
void partD();
void partE();

int main() {
	cout << endl << "-------\nProgram Start" << endl;

	cout << endl << endl;
	partA();
	cout << endl << endl;
	partB();
	cout << endl << endl;
	partC();
	cout << endl << endl;
	partD();
	cout << endl << endl;
	partE();
	cout << endl << endl;

	cout << endl << "Program End\n-------" << endl;
	/*
	I wrote this in Visual Studio, so this was my debugging window. 
	char x;
	cin >> x;
	*/

	return 0;
}

void partA() {
	int a[] = {10,15,4,25,3,-4};
	int *p = &a[2];
	
	cout << "*(p+1): " << *(p+1) << endl;
	cout << "p[-1]: " << p[-1] << endl;
	cout << "p - a: " << p - a << endl;
	cout << "a[*p++]: " << a[*p++] << endl;
	cout << "*(a+a[2]): " << *(a+a[2]) << endl;
}

void partB() {
	char s[] = "desolate", *p = s;
	cout << *p++ << endl;
	cout << *(p++) << endl;
	cout << (*p)++ << endl;
	cout << *++p << endl;
	cout << *(++p) << endl;
	cout << ++*p << endl;
	cout << ++(*p) << endl;
	cout << s << endl;
}

#define type(x) cout << #x " = " << typeid(x).name() << endl;
#define bytes(x) cout << "sizeof " #x " = " << sizeof x << endl;
#define describe(x) type(x) bytes(x)
void partC() {   
	int a[2][3][4][5] =    
	{      
		{        
			{{0,1,2,3,4},{5,6,7,8,9},{0,1,2,3,4},{5,6,7,8,9}},
			{{0,1,2,3,4},{5,6,7,8,9},{0,1,2,3,4},{5,6,7,8,9}},
			{{0,1,2,3,4},{5,6,7,8,9},{0,1,2,3,4},{5,6,7,8,9}},      
		},
		{        
			{{0,1,2,3,4},{5,6,7,8,9},{0,1,2,3,4},{5,6,7,8,9}},
			{{0,1,2,3,4},{5,6,7,8,9},{0,1,2,3,4},{5,6,7,8,9}},
			{{0,1,2,3,4},{5,6,7,8,9},{0,1,2,3,4},{5,6,7,8,9}},
		}    
	};
	describe(a);
	type(a+1);    
	describe(a[1]);
	type(a[1]+1);
	describe(a[1][1]);
	type(a[1][1]+1);
	describe(a[1][1][1]);
	type(a[1][1][1]+1);
	describe(a[1][1][1][1]);
	cout << a[1][1][1][1] << endl;
}

class C{
public:    
	void f() {
		cout << "C::f\n";
	}    
	void g() {
		cout << "C::g\n";
	}
};
void partD(){ 
	C c;    
	
	// Using an object    
	void (C::*pmf)() = &C::f;
	(c.*pmf)();     // Executes c.f()
	pmf = &C::g;    
	(c.*pmf)();     // Executes c.g()    
					
	// Using pointer to an object
	C* cp = &c;    
	pmf = &C::f;    
	(cp->*pmf)();   // Executes cp->f()    
	pmf = &C::g;
	(cp->*pmf)();   // Executes cp->g()
}

void partE() {
	int a[1][2][3][4];
	cout << "Dimensions of Layer 1: " << sizeof(*a) << endl; // We don't need to defrerence this because arrays are aliases to the pointer at the first location already.
	cout << "Dimensions of Layer 2: " << sizeof(**a) << endl; // This is the a derefrenced to the second layer.
	cout << "Dimensions of Layer 3: " << sizeof(***a) << endl; // This is the a derefrenced to the third layer.
	cout << "Dimensions of Layer 4: " << sizeof(****a) << endl; // This is the a derefrenced to the fourth layer
}