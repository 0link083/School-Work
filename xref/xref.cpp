// Project 5 C++ Software Developmment
// Containers Project

#include <cstddef> //size_t
#include <iostream> // cout, cerr
#include <algorithm>
#include <map> // map for ordered pairs of keys (lineNumber), pair (string) and (line ocurrances)
#include <utility> // pair
#include <string> // string
#include <fstream> // for input file streams
#include <sstream> // string stream
#include <regex> // Now I have two problems
#include <cctype>

using std::size_t;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::pair;
using std::string;
using std::ifstream;
using std::stringstream;
using std::map;
using std::for_each;
using std::to_string;
using std::tolower;

#define MAX_LINE_NUMBER 9

std::regex valid_begin_format("[a-zA-Z].*");
std::regex valid_string_format("[a-zA-Z\'\-]+");

struct pairComp {
	bool operator()(const string& left, const string& right) const {
		char const* leftc = left.c_str();
		char const* rightc = right.c_str();
		for (; *leftc != '\0' && *rightc != '\0'; ++leftc, ++rightc) {
			if (tolower(*leftc) != tolower(*rightc)) // if the first character isn't we don't care.
				return tolower(*leftc) < tolower(*rightc);
			else if (*leftc != *rightc) {
				if (*(leftc + 1) == '\0' && *(rightc + 1) == '\0')
					return *leftc < *rightc;
			}
		}
		return tolower(*leftc) < tolower(*rightc);
	}
};


template <class fwdIter> // Yes I know these belong in .h files.
size_t iterDistance(fwdIter iterLow, fwdIter iterHigh) {
	size_t iterDist = 0;
	while (iterLow != iterHigh) {
		++iterDist;
		++iterLow;
	}
	return iterDist;
}

// Cross Refrence Generator
// Reads Text File
// extracts word-like tokens containing letters, hypens, and apostrophees; no numerals must begin with letter
// print a listing of the line # where each token appears along with the # of times it does appear, in the format line-number:count
// Case is seperate, but they can follow eachother. meaning A and a are seperate but displayed one after the other.
// The longest word will be the format for the key, showing the " : " following. (Use string formatting like %<num>s for that.)
// Have a defined constant for the max number of words that appear when printing. Like 9. 9 is good. I think it doesn't want to be magic.
// 

int main(int argc, string argv[]) {
	string filename;
	if (argc == 1) {
		//cout << "usage: ./xref Strings.txt" << endl << "displays word counts and line occurances of words in the text file to standard out. Please input a filename: " << endl;
		cin >> filename;
	}
	else if (argc == 2) {
		filename = argv[1];
	}
	//cout << "Reading " << filename << endl;
	ifstream file(filename);
	if (!file) {
		cerr << "File is bad, exiting with error code -1." << endl;
		return -1;
	}

	map<string, map<size_t, size_t>, pairComp> atlas; // An Atlas is a big map. it has a key, with a pair, and a way to compare its keys 
	// This map contains the string of the token (First, Key) <0>, 
	// with size_t in the pair denoting the location of the pair (Second)<1>. 

	stringstream line;
	size_t lineNumber = 1; // This will increment for each line of the txt file and be stored in the map Atlas.
	size_t max_length = 0;
	string word;
	string input;
	while (file) {
		// Validate line
		getline(file, input);
		line << input; // Put the string into a string stream
		input.clear();
		while(line){
			line >> word;
			if (std::regex_match(word, valid_begin_format)) { // Try the first letter
				std::smatch s;
				if (std::regex_match(word, s, valid_string_format)) {
					word = s.str(); // Newly formatted string
					atlas[word][lineNumber]++; // insert the pair into the atlas.
					if (max_length < word.length()) max_length = word.length();
				} // This should throw out illegal characters, and still consider the string, IT DOES NOT CURRENTLY
			} // If the character is illegal it is thrown out of consideration.
			word.clear();
		}
		line.clear();
		++lineNumber;
	}

	size_t somenum = 0;

	/*auto innerPrint = [&somenum, &max_length](pair<size_t, size_t>& inner) {
		
	};*/

	auto print = [&max_length, &somenum](auto& n) {
		cout << n.first;
		for (size_t i = n.first.length(); i < max_length; ++i) {
			cout << " "; // This was a formatting requirement.
		}
		cout<<" : ";
		auto m = n.second.begin();
		for (; m != n.second.end(); ++m) {
			++somenum;
			if (somenum == MAX_LINE_NUMBER)
			{
				cout << endl;
				for (size_t i = 0; i < max_length; ++i) {
					cout << " "; // This was a formatting requirement.
				}
				cout << " : ";
				somenum = 0;
			}
			cout << m->first << ':' << m->second << ", ";
		}
		cout << endl;
		somenum = 0;
	};

	for_each(atlas.begin(), atlas.end(), print);

	return 0;
}