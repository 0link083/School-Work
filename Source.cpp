#include <iostream>

using namespace std;

void func1() {
	int a[] = { 10,15,4,25,3,-4 };
	int *p = &a[2];
	cout << endl;
	cout << "*p : " << *p << endl;
	cout << "*(p+1) : " << *(p + 1) << endl;
	cout << "p[-1] : " << p[-1] << endl;
	cout << "p-a : " << (p - a) << endl; 
	cout << "a[p++] : " << a[*p++] << endl;
	cout << "*(a + a[2]) : " << *(a + a[2]) << endl;
}

void func2() {
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
void func3() {
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
	type(a + 1);
	describe(a[1]);
	type(a[1] + 1);
	describe(a[1][1]);
	type(a[1][1] + 1);
	describe(a[1][1][1]);
	type(a[1][1][1] + 1);
	describe(a[1][1][1][1]);
	cout << a[1][1][1][1] << endl;
}
class C
{
public:
	void f() { cout << "C::f\n"; }
	void g() { cout << "C::g\n"; }
};

void func4()
{
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


int main() {
	func1();
	func2();
	func3();
	func4();
	
	return 0;
}


