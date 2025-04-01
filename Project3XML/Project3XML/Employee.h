// Employee.h
// Contains the SPECIFICATION of the Employee class as defined in the project spec, plus whatever else was needed.
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream> // Since iostream is guarded and I need it to use string, I have included it in my .h file. I would love to know how to avoid this though.

using namespace std;


class Employee {
private:
	string name;
	int id;
	string address;
	string city;
	string state;
	string country;
	string phone;
	double salary;
	struct EmployeeRec { 
		int id;         
		char name[31];         
		char address[26];         
		char city[21];         
		char state[21];         
		char country[21];         
		char phone[21];         
		double salary; 
	};

public:
	Employee();
	void display(std::ostream&) const;				// Write a readable Employee representation to a stream   
	void write(std::ostream&) const;				// Write a fixed-length record to current file position   
	void store(std::iostream&) const;				// Overwrite (or append) record in (to) file   
	void toXML(std::ostream&) const;				// Write XML record for Employee   
	static Employee* read(std::istream&);			// Read record from current file position   
	static Employee* retrieve(std::istream&,int);	// Search file for record by id   
	static Employee* fromXML(std::istream&);		// Read the XML record from a stream 
	bool isValid() const; // Used to determine if the object should exist past closing a xml tag
	void setSalary(const int&);
};

#endif