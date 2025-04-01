// XMLProject.cpp
// This is an adapted version from code Samples, I should just have to add error handling, in theory.
// employeedb2.cpp: Reads employee data into a fixed-length record file
//
// Note use of binary file mode (required on Windows; ignored on *NIX)

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <memory>
#include <iterator>
#include <cstddef>
using namespace std;

static int lineNum = 0; // Just to see how many lines are read

// Modifies a String into an UPPERCASE version of itself
void toUpper(string& s) { // We use this to remove the need for case checking in our tags.
	for (auto &c : s)
		c = toupper(c);
}

void lineNumPrint(string& line) {
	stringstream linestream;
	linestream << line;
	linestream >> ws;
	line = linestream.str(); //Removing whitespace
	cout << "Line " << ++lineNum << ": " << line << endl;
}

// For strings
bool checkTag(string &tagName, string &tagtype, string &line, istream &f) {
	// <tagName>data</tagName>
	toUpper(tagName);
	cout << tagtype << " :StRiJNg " << line << endl;
	if (line == tagName) {
		try {
			if (tagtype != "") {
				runtime_error e(tagName);
				throw e;
			}
			cout << tagName << " tag found." << endl;
			// Get the space between this and the closing tag, it holds needed information. 
			// if another tag is encountered, throw an error and exit this tag.
			if (getline(f, line, '<')) { // delimit by <
				tagtype = line; // Turn the data into a usable form.
				lineNumPrint(line);
				if (getline(f, line, '>')) {
					toUpper(line);
					lineNumPrint(line);
					try {
						if (line != "/" + tagName) {
							tagName = "/" + tagName;
							runtime_error e(tagName);
							throw e;
						}
						cout << tagName << " close tag found." << endl;
					}
					catch (runtime_error &e) {
						cerr << e.what() << " threw an error, no close tag found for " << e.what() << endl;
						// We actually largely ignore a missing closing tag here.
					}
				}
				else {
					return false; // eof
				}
			}
			else {
				return false; // eof
			}
		}
		catch (runtime_error &e) {
			cerr << e.what() << " attempted to be rewritten, do not duplicate tags." << endl;
			// We will ignore the second tag entry.
			cout << tagName << ": [" << tagtype << "]" << endl;
		}
		return true;
	}
}

// For int
bool checkTag(string &tagName, int &tagtype, string &line, istream &f) {
	// <tagName>data</tagName>
	toUpper(tagName);
	if (line == tagName) {
		try {
			if (tagtype != 0) {
				runtime_error  e(tagName);
				throw e;
			}
			cout << tagName << " tag found." << endl;
			// Get the space between this and the closing tag, it holds needed information. 
			// if another tag is encountered, throw an error and exit this tag.
			if (getline(f, line, '<')) {
				lineNumPrint(line);
				tagtype = stoi(line); // Turn the data into a usable form.
				if (getline(f, line, '>')) {
					toUpper(line);
					lineNumPrint(line);
					try {
						if (line != "/" + tagName) {
							runtime_error e("/" + tagName);
							throw e;
						}
						cout << tagName << " close tag found." << endl;
					}
					catch (runtime_error &e) {
						cerr << e.what() << " threw an error, no close tag found for " << e.what() << endl;
						// We actually largely ignore a missing closing tag here.
					}
				}
				else {
					return false; // eof
				}
			}
			else {
				return false; // eof
			}
		}
		catch (runtime_error &e) {
			cerr << e.what() << " attempted to be rewritten, do not duplicate tags." << endl;
			// We will ignore the second tag entry.
		}
		return true;
	}
}

// For double
bool checkTag(string &tagName, double &tagtype, string &line, istream &f) {
	// <tagName>data</tagName>
	toUpper(tagName);
	if (line == tagName) {
		try {
			if (tagtype != 0.0) {
				runtime_error e(tagName);
				throw e;
			}
			cout << tagName << " tag found." << endl;
			// Get the space between this and the closing tag, it holds needed information. 
			// if another tag is encountered, throw an error and exit this tag.
			if (getline(f, line, '<')) {
				lineNumPrint(line);
				tagtype = stod(line); // Turn the data into a usable form.
				if (getline(f, line, '>')) {
					toUpper(line);
					lineNumPrint(line);
					try {
						if (line != "/" + tagName) {
							runtime_error e(tagName);
							throw e;
						}
						cout << tagName << " close tag found." << endl;
					}
					catch (runtime_error &e) {
						cerr << e.what() << " threw an error, no close tag found for " << e.what() << endl;
						// We actually largely ignore a missing closing tag here.
					}
				}
				else {
					return false; // eof
				}
			}
			else {
				return false; // eof
			}
		}
		catch (runtime_error &e) {
			cerr << e.what() << " attempted to be rewritten, do not duplicate tags." << endl;
			// We will ignore the second tag entry.
		}
		return true;
	}
}

class Employee {
	int id;
	string name;
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
	static void stobuf(const string& s, char* buf, size_t limit) {
		// Compute the numbers of chars to transfer (can't exceed limit-1)
		size_t nchars{ min(limit - 1,s.size()) };

		// Copy and null-terminate
		s.copy(buf, nchars);
		buf[nchars] = '\0';
	}
	
public:
	Employee() : name(""), address(""), city(""), state(""), country(""), phone("") {
		id = 0;
		salary = 0.0;
	}
	Employee(Employee &employee) : name(employee.name), address(employee.address), city(employee.city), state(employee.state), country(employee.country), phone(employee.phone) {
		this->salary = employee.salary;
		this->id = employee.id;
	}
	Employee(int id, const string& name, const string& address,
		const string& city, const string& state, const string& country, const string& phone, double salary)
		: name(name), address(address), city(city), state(state), country(country), phone(phone){
		this->salary = salary;
		this->id = id;
	}
	~Employee() = default;
	friend ostream& operator<<(ostream& os, const Employee& e) {
		return os << "id " << e.id << endl <<
			"name " << e.name << endl <<
			"address " << e.address << endl <<
			"city " << e.city << endl <<
			"state " << e.state << endl <<
			"country " << e.country << endl << 
			"phone " << e.phone << endl << 
			"salary " << e.salary << endl << endl;
	}
	
	void write(ostream& os) {
		EmployeeRec outbuf; //The struct
		outbuf.id = id;
		outbuf.salary = salary;
		stobuf(name, outbuf.name, sizeof(outbuf.name) - 1);
		stobuf(address, outbuf.address, sizeof(outbuf.address) - 1);
		stobuf(city, outbuf.city, sizeof(outbuf.city) - 1);
		stobuf(state, outbuf.state, sizeof(outbuf.state) - 1);
		stobuf(country, outbuf.country, sizeof(outbuf.country) - 1);
		stobuf(phone, outbuf.phone, sizeof(outbuf.phone) - 1);
		os.write(reinterpret_cast<const char*>(&outbuf), sizeof outbuf);
	}

	static Employee* fromXML(istream& f) {
		if (f) {
			string line;

			// Read/write records
			//ofstream empdat("employee.bin", ios::out | ios::binary | ios::trunc);

			
			//Flags are true on open tag and false on close
			bool empFlag = false;

			double salary = 0.0;
			int id = 0;
			string name = "";
			string address = "";
			string city = "";
			string state = "";
			string country = "";
			string phone = "";

			string _salary = "SALARY";
			string _phone = "PHONE";
			string _country = "COUNTRY";
			string _state = "STATE";
			string _city = "CITY";
			string _address = "ADDRESS";
			string _id = "ID";
			string _name = "NAME";

			f >> skipws;

			while (getline(f, line, '<')) {
				{
					try 
					{	
						getline(f, line, '>');
							
							toUpper(line);
							lineNumPrint(line);

							//<Employee> </Employee>
							if (line == "EMPLOYEE" && empFlag == false) { //Line will probably just be EMPLOYEE since it will delemit by <>
								try {
									if (empFlag) {
										runtime_error e("Employee tag started before the previous ended.");
										throw e;
									}
									cout << "Employee tag found." << endl;
									empFlag = true;

									// We have a new Employee, lets initialize its readables.
									id = 0;
									name = "";
									address = "";
									city = "";
									state = "";
									country = "";
									phone = "";
									salary = 0.0;
								}
								catch (runtime_error &e) {
									cerr << e.what() << endl;
									//Since they want a graceful exit, we should probably end the tag for them, but not today
								}
							}
							else if (line == "/EMPLOYEE") {
								try {
									if (!empFlag) {
										runtime_error e("Employee tag closed before it was opened. Unformated data lost.");
										throw e;
									}
									cout << "Emp close tag found." << endl;
									empFlag = false;
									try {
										if (name == "" || id == 0) {
											runtime_error e("Name and ID must be defined.");
											throw e;
										}
										return(new Employee(id, name, address,
											city, state, country, phone, salary)); // Return unique pointer of newly constucted employee to vector.
									}
									catch (runtime_error &e) {
										cerr << e.what(); // Displays the error
										// This will keep routing with partial information.
									}
								}
								catch (runtime_error &e) {
									cerr << e.what() << endl;
									// I can't fix this error for them.
									//So we will wait until we reach the end of the file or have a good data entry
								}
								// Leave after finding a new tag
							}

							else  { // If we can assume another tag, we should. Otherwise we lose it.
								// <Salary> </Salary>
								if (!checkTag(_salary, salary, line, f)) {
									return nullptr; //if we reach the eof
								}

								// <phone> </phone>
								if (!checkTag(_phone, phone, line, f)) {
									return nullptr; //if we reach the eof
								}

								// <country> </country>
								if (!checkTag(_country, country, line, f)) {
									return nullptr; //if we reach the eof
								}

								// <state> </state>
								if (!checkTag(_state, state, line, f)) {
									return nullptr; //if we reach the eof
								}
								// <city> </city>
								if (!checkTag(_city, city, line, f)) {
									return nullptr; //if we reach the eof
								}

								// <address> </address>
								if (!checkTag(_address, address, line, f)) {
									return nullptr; //if we reach the eof
								}

								// <id> </id>
								if (!checkTag(_id, id, line, f)) {
									return nullptr; //if we reach the eof
								}

								// <name> </name>
								if (!checkTag(_name, name, line, f)) {
									return nullptr; //if we reach the eof
								}

							}	
						
					}
					catch (runtime_error &e) {
						cerr << e.what() << endl; // Catching uncaught errors.
					}
				}
			}
		}
	}
};

int main(int argc, string argv[]) {
	try {
		int argc = 2;
		string argv[2] = { "./XMLProject", "emp.txt" };
		try {
			if (argc != 2) {
				if (argc < 2) {//Too little arguments
					runtime_error e("usage: ./XMLProject <filename>: creates an object for XML formatting from input file."); // This is an acceptable use of the program. Maybe not useful, but certainly acceptable. But it should go to std::cerr
					throw e;
				}
				else if (argc > 2) { //Too many arguments
					runtime_error e("Too many arguments, there is only one expected filename. If you wish to do multiple, run only one at a time.");
					throw e;
				}
			}
		}
		catch (runtime_error &e) {
			cerr << e.what() << endl;
			return -1;
		}
		string filename(argv[1]);
		ifstream f(filename);
		try {
			if (!f) {
				runtime_error e("HALT: This file does not exist.");
				throw e;
			}
		}
		catch (runtime_error &e) {
			cerr << e.what() << endl;
			return -1; // We can not fix a dead file.
		}

		unique_ptr<vector<unique_ptr<Employee>>> records(new vector<unique_ptr<Employee>>); // A vector of unique pointers to Employee objects.

		while (f){
			Employee* temp = new Employee();
			records->emplace_back(unique_ptr<Employee> (temp->fromXML(f)));

			//empdat.close();

			/*
			// Read records
			fstream emprecs("employee.bin", ios::in | ios::out | ios::binary);
			Employee emp = Employee::read(emprecs);
			while (emp.isValid()) {
				cout << emp << endl;
				emp = Employee::read(emprecs);
			}
			cout << endl;

			// Move around in file
			emprecs.clear();                        // Clear EOF from previous read loop
			emprecs.seekg(0, ios::beg);              // Rewind
			emp = Employee::read(emprecs);
			cout << "record 0: " << emp << endl;
			auto pos = emprecs.tellg();             // Save position [1] for later

			// Overwrite first record
			emp.setJob("Bottle Washer");
			emprecs.seekp(0, ios::beg);              // Position for write
			emp.write(emprecs);

			// Verify change
			emprecs.seekg(0, ios::beg);              // Position for read
			emp = Employee::read(emprecs);
			cout << "record 0 again: " << emp << endl;

			// Read the third record
			emprecs.seekg(Employee::recSize(), ios::cur);   // Skip next record ([1])
			emp = Employee::read(emprecs);
			cout << "record 2: " << emp << endl;

			// Read the second record
			emprecs.seekg(pos);
			emp = Employee::read(emprecs);
			cout << "record 1: " << emp << endl;

			// Read last record
			emprecs.seekg(-Employee::recSize(), ios::end);
			emp = Employee::read(emprecs);
			cout << "last record: " << emp << endl;

			*/
		}
		for(int i = 0; i < records->size();++i) {
			cout << *(records->at(i)) << endl;
		}
		cout << **(records->begin()) << endl;
		
		char w;
		cin >> w;
		return 0;
	}
	catch (runtime_error &e) {
		cerr << "This was not caught properly: " << e.what() << endl;
		return -1;
	}
	catch (...) {
		cerr << "An unknown error has occured." << endl;
		return -2;
	}
}

/* Output:

*/