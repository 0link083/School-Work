// Lab2.cpp
// 9/6/2021
#include<iostream>

using std::cout;

int main() {	
	int a[] = {10,15,4,25,3,-4};
	int *p = &a[2];
	
	cout << "*(p+1)" << *(p+1) << endl;
	cout << "p[—1]" << p[—1] << endl;
	cout << "p — a" << p — a << endl;
	cout << "a[*p++]" << a[*p++] << endl;
	cout << "*(a+a[2])" << *(a+a[2]) << endl;
	
	return 0;
}