// Employee.cpp
// Contains the IMPLEMENTATION of the Employee class as defined in the project spec, plus whatever else was needed.
#include "Employee.h" // I may have looked up how this works, and realized that Visual Studio requires it to be in the Resource files.
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

Employee::Employee() {
	phone = country = state = city = address = name = ""; // This should set all of the string attributes to the empty string.
	salary = 0.0;
	id = -1; // This value should not be a value that we expect as input, so -1 seemed reasonable.
};

void Employee::display(std::ostream &os) const
{
	//Displays contents of this employee to the os asked for.
	os << "id: " << id << endl;
	os << "name: " << name << endl;
	os << "address: " << address << endl;
	os << "city: " << city << endl;
	os << "state: " << endl;
	os << "country: " << country << endl;
	os << "phone: " << phone << endl;
	os << "salary: " << salary << endl;
	os << endl;
}


void Employee::write(std::ostream &os) const
{
	EmployeeRec outbuf;
	outbuf.id = id;
	strncpy(outbuf.name, name.c_str(), 31)[31] = '\0';
	strncpy(outbuf.address, address.c_str(), 26)[26] = '\0';
	strncpy(outbuf.city, city.c_str(), 21)[21] = '\0';
	strncpy(outbuf.state, state.c_str(), 21)[21] = '\0';
	strncpy(outbuf.country, country.c_str(), 21)[21] = '\0';
	strncpy(outbuf.phone, phone.c_str(), 21)[21] = '\0';
	outbuf.salary = salary;
	os.write(reinterpret_cast<const char*>(&outbuf), sizeof outbuf);
}

void Employee::store(std::iostream &ios) const
{
	// COMPLEX STUFF TO CHECK FILE GO TO END OF FILE AND WRITE THERE ETC
	toXML(ios);
}

void Employee::toXML(std::ostream &os) const
{
	os << "<employee>" << endl;
	os << "\t<name>" << name << "</name>" <<endl; //note the /t for tab format of xml properties
	os << "\t<id>" << id << "</id>" << endl;
	os << "\t<address>" << address << "</address>" << endl;
	os << "\t<city>" << city << "</city>" << endl;
	os << "\t<state>" << state << "</state>" << endl;
	os << "\t<country>" << country << "</country>" << endl;
	os << "\t<phone>" << phone << "</phone>" << endl;
	os << "\t<salary>" << salary << "</salary>" << endl;
	os << "</employee>" << endl; 
}

Employee* Employee::read(std::istream &is)
{
	if (is.peek() == EOF)
		return nullptr; // returns when read end of file
	return new Employee(/*parameters from the recieved*/); // We return a new employee based on the input we recieved.   PERHAPS FACTORY?
}

Employee* Employee::retrieve(std::istream &is, int id)
{
	int badID = -1; //Until I can properly read XML I defaulted this. since this is actually wrong.
	// Parse through Employee tags to find an Id tag that matches the one in parmeter, return that WHOLE EMPLOYEE
	read(is); //read the stream given for the employee id.
	if (is.peek() ==EOF || id == badID){
		return nullptr; // returns when read end of file or the id is not found in the file.
	}
}

Employee* Employee::fromXML(std::istream &is)
{
	string temp;
	int next = is.peek();
	if(next == EOF)
		return nullptr; // returns when read end of file
	getline(is, temp); // Gets current line for analysis

}

bool Employee::isValid() const {
	if(id == -1 || name == "") return false; //These both must have values to be a valid object according to the spec.
	return true;
}

void Employee::setSalary(const int& i) {
	salary = i;
}