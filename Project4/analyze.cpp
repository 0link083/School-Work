// analyze.cpp
// Collects data from .dat and .ini files to display areas under a smoothed curve 

// Please note that a negative invariant of the pulses is not supported.

#include <vector>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <functional>
#include <numeric>
#include <stdexcept> // for runtime_error
#include <cassert> // for assertions
#include <cstddef> // for size_t

using namespace std;

// This structure assists in the smoothing calculation and it is initialized by a .ini file.
struct PulseParameters {
	int vt;
	int width;
	int pulse_delta;		 // Gaps between data pulses
	double drop_ratio;		 // A number less than 1
	double below_drop_ratio; // The number of (collected) values less than the given drop ratio.
};

//Read file reads in an ini file and initializes arguments to a struct by refrence.
void readFileForPulseParameters(PulseParameters &p, string const &filename) {
	ifstream ini = ifstream(filename);
	string s;
	bool flags[] = { false,false,false,false,false };
	while (ini) {
		getline(ini, s, '=');
		if (s == "vt") {
			if (flags[0] == true) {
				runtime_error e("Duplicate " + s + " tag");
				throw e;
			}
			getline(ini, s);
			try {
				p.vt = stoi(s);
				flags[0] = true;
			}
			catch (invalid_argument &e) {
				runtime_error e2("invalid value for vt");
				throw e2;
			}

		}
		else if (s == "width") {
			if (flags[1]) {
				runtime_error e("Duplicate " + s + " tag");
				throw e;
			}
			getline(ini, s);
			try {
				p.width = stoi(s);
				flags[1] = true;
			}
			catch (invalid_argument &e) {
				runtime_error e2("invalid value for width");
				throw e2;
			}

		}
		else if (s == "pulse_delta") {
			if (flags[2]) {
				runtime_error e("Duplicate " + s + " tag");
				throw e;
			}
			getline(ini, s);
			try {
				p.pulse_delta = stoi(s);
				flags[2] = true;
			}
			catch (invalid_argument &e) {
				runtime_error e2("invalid value for pulse_delta");
				throw e2;
			}

		}
		else if (s == "drop_ratio") {
			if (flags[3]) {
				runtime_error e("Duplicate " + s + " tag");
				throw e;
			}
			getline(ini, s);
			try {
				p.drop_ratio = stod(s);
				flags[3] = true;
			}
			catch (invalid_argument &e) {
				runtime_error e2("invalid value for drop_ratio");
				throw e2;
			}

		}
		else if (s == "below_drop_ratio") {
			if (flags[4]) {
				runtime_error e("Duplicate " + s + " tag");
				throw e;
			}
			getline(ini, s);
			try {
				p.below_drop_ratio = stod(s);
				flags[4] = true;
			}
			catch (invalid_argument &e) {
				runtime_error e2("invalid value for below_drop_ratio");
				throw e2;
			}

		}
		else if (s == "" || s == " " || s == "\n" || s[0] == '#') { // if whitespace or a comment
			; //do nothing
		}
		else {
			runtime_error e("Incorrect data type " + s + " in ini file, exiting.");
			getline(ini, s); // We need to disregard anything after this equals sign
			throw e;
		}
	}

	if (!(flags[0] && flags[1] && flags[2] && flags[3] && flags[4])) {
		runtime_error e("A value in the ini file was uninitialized, do not use bad ini files. Exiting.");
		throw e; // This will be caught outside the function as it has to exit main.
	}

}

void readFile(vector<string> &inputVector, string filename) {
	ifstream input_file = ifstream(filename);
	istream_iterator<string> front(input_file);
	istream_iterator<string> eos;
	vector<string> temp(front, eos);
	inputVector = temp;
}

// Takes a string vector, and inserts the name of all known .dat files in the current directory that open into it.
void insert_dat_file_names_into_vector(vector<string> &fileNames){
	// REQUIRES G++ COMPILER
	for (const auto& entry : std::filesystem::directory_iterator(".")) {
		auto path = entry.path();
		if (is_regular_file(entry) && path.extension() == ".dat") {
			auto fsize = entry.file_size();
			auto fname = path.filename().string();
			fileNames.emplace_back(fname);
		}
	}
}
// Appends to a vector of strings based on input from a file.
void readFileForPulse(vector<string> &pulse, string filename) {
	vector<string>temp;
	readFile(temp, filename);
	/*
	ostream_iterator<string> output(cout, " ");
	copy(temp.begin(), temp.end(), output); // This checks to see if the file actually inputs correctly. Which it did at one point.
	*/
	copy(temp.begin(), temp.end(), back_inserter(pulse));
	/* REQUIRES G++ COMPILER
	for (const auto& entry : filesystem::directory_iterator(".")) {
		auto path = entry.path();
		if (is_regular_file(entry) && path.extension() == ".dat") {
			auto fsize = entry.file_size();
			auto fname = path.filename().string();
			cout << fname << " (" << fsize << ")\n";
			getchar();
		}
	}
	*/
}

void vectorstoi(vector<string> &pulseString, vector<int> &pulse) {
	transform(pulseString.begin(), pulseString.end(), back_inserter(pulse), [](string s) { return stoi(s); });
} 

// modifies vectors,
// multiplies each element of a vector by -1 in place.
void negationOfVector(vector<int> &v) {
	transform(v.begin(), v.end(), v.begin(), [](int i) { return -1 * i; });
}

void smoothAlgorithm(const vector<int> &v, vector<int> &v2) {
	for (int i = 3; i < (v.size() - 4); i++) {
		v2[i] = ((v[i - 3] + (2 * v[i - 2]) + (3 * v[i - 1]) + (3 * v[i]) + (3 * v[i + 1]) + (2 * v[i + 2]) + v[i + 3]) / 15);
	}
}

void processPulse(const vector<int> pulse, const vector<int> smoothPulse, const PulseParameters pulseParameters) {
	vector<int> sumVector; // Used to hold values in a pulse for requisiton.
	bool pulseFlag = false; // I use this to determine if the pulse is in need of sumation.
	auto tempWidth = pulseParameters.width;
	auto peak = 0; // The value of the peak, it's possible that 0 being the initial peak disrupts it from attending negative values.
	auto peakAt = 0; // For iterators at the peak
	auto pulseBeginLocation = 0; // For storing information on piggybacks and starts of peaks.
	auto tempDelta = pulseParameters.pulse_delta; // to prevent from entering piggyback protocol every ten seconds.
	for (size_t i = 0;i<smoothPulse.size()-2; ++i) {
		if ((smoothPulse[i + 2] - smoothPulse[i]) > pulseParameters.vt) { // IF we find a pulse
			if (pulseFlag && tempDelta == 0) { // Piggy back or new pulse, the peak!=0 is for a performance boost
				vector<int> tempBelow; //This is for finding information on elements that are between the peak of the first pulse and the start of the second.
				copy_if(pulse.begin()+peakAt, pulse.begin()+i-1, back_inserter(tempBelow), 
					[pulseParameters, peak](int j) {return (j<pulseParameters.drop_ratio*peak); });
				if (tempBelow.size() > pulseParameters.below_drop_ratio) { 
					tempWidth = pulseParameters.width;
					cout << "Found piggyback at " << pulseBeginLocation << endl;
					pulseBeginLocation = i;
					
					sumVector.clear();
					assert(sumVector.empty());
				}
				else {
					pulseFlag = false;
					size_t pulseArea = accumulate(sumVector.begin(), sumVector.end(), 0);
					sumVector.clear();
					cout << pulseBeginLocation << " (" << pulseArea << ")" << endl; 
					tempWidth = pulseParameters.width;
					i--; // This fixed an issue where I was an index off for some unknown reason.
				}

				tempDelta = pulseParameters.pulse_delta;
				tempBelow.clear();

			}
			else if (!pulseFlag) { //This should trigger when we first encounter a pulse.
				pulseBeginLocation = i;
				pulseFlag = true;
				tempWidth = pulseParameters.width;
			}
		}

		if (pulseFlag) { //This should trigger after we hit a pulse and want to record it.
			if (tempDelta > 0) { // I hate how many times this will be checked and not used, but it should fix the problem of not having multiple piggybacks.
				tempDelta--;
			}

			if (tempWidth > 0) {
				tempWidth--;
				sumVector.push_back(pulse[i]);
				if (peak < pulse[i]) {
					peak = pulse[i]; //If value is greater assign new peak
					peakAt = i;
				}
			}
			else { // This is when we reach the end of a pulse.
				pulseFlag = false;
				size_t pulseArea = accumulate(sumVector.begin(), sumVector.end(), 0);
				sumVector.clear();
				cout << pulseBeginLocation << " (" << pulseArea << ")" << endl;
				tempWidth = pulseParameters.width;
				i--;
			}
		}
	}
}

void processFile(string const &filename, PulseParameters const &pulseParameters) {
	vector<string> pulseString;
	readFileForPulse(pulseString, filename);
	cout << filename << ":" << endl;
	vector<int> pulse;

	vectorstoi(pulseString, pulse);

	negationOfVector(pulse);
	vector<int> smoothPulse(pulse.begin(), pulse.end());
	smoothAlgorithm(pulse, smoothPulse);
	processPulse(pulse, smoothPulse, pulseParameters);
	cout << endl;
}

int main(int argc, char* argv[]) {
	PulseParameters pulseParameters;
	string ini_filename;
	if (argc == 2) {
		ini_filename = argv[2];
	}
	else {
		ini_filename = "gage2scope.ini"; //Debugging purposes on VisualStudio code.
	}

	try {
		readFileForPulseParameters(pulseParameters, ini_filename); // reads through .ini files to initialize variables.
		//readFileForPulseParameters(pulseParameters, "error4.ini");
	}
	catch (runtime_error &e) {
		cerr << e.what() << endl << "Exiting due to ini file constraints." << endl;
		return -1; // return from main with an error code.
	}

	vector<string> iniFiles;
	insert_dat_file_names_into_vector(iniFiles);

	// Consider this temporary until I find a better way to implement Filesystem universally.
	for (auto i = iniFiles.begin(); i < iniFiles.end(); i++) {
		processFile(*i,pulseParameters);
	}
	/*
	processFile("as_ch01-0537xx_Record1042.dat", pulseParameters);
	processFile("2_Record2308.dat", pulseParameters);
	processFile("2_Record3388.dat", pulseParameters);
	*/

}
