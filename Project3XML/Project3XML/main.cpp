// main.cpp
// Contains the driver for the program, this is what runs...
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "Employee.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "There was not an argument provided." << endl;
		return 1; // Error indicating bad arguments
	}
	ifstream f(argv[1]);
	if(f){
		string line;
		ofstream empData("employee.bin", ios::out | ios::binary | ios::trunc);
		vector<unique_ptr<Employee>> vectorOfEmps;
	}
	else {
		cout << "There was not a proper argument provided." << endl;
		return 2; // Error indicating bad file
	}

	// Literally I keep it just to have SANITY
	cout << "Works... sort of. Nothing has actually happened here." << endl;
	std::getchar();
	return 0; 
}