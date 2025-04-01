// Project 7, CS 3060, Block Access Algorithm
// Michael Shipley and John Jolly

#include <cstddef> // for size_t
#include <vector> // for vector
#include <algorithm> // for for_each
#include <iostream> // for cin and cout

using std::size_t; // better unsigned int. 
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

void greeting() {
	cout << "Assignment 7: Block Access Algorithm" << endl << "By: Michael Shipley" << endl;
}

//returns the difference of x and y
size_t diff(size_t x, size_t y) {
	return (std::max(x, y) - std::min(x, y));
}

size_t FCFS(vector<size_t> const &block_list) {
	size_t seek_value = 0;
	for (size_t i = 1; i < block_list.size(); ++i) {
		seek_value += diff(block_list[i], block_list[i - 1]);
	}
	return seek_value;
}

size_t SSTF(vector<size_t> const &block_list) {
	vector<size_t> temp(block_list.begin(), block_list.end());
	size_t seek_value = 0;
	size_t indexj = 1; // For storing j
	while (temp.size()>2) {
		indexj = 1;
		for (size_t j = 2; j < temp.size(); ++j) {
			if (diff(temp[0], temp[j]) < diff(temp[0], temp[indexj])) { // if the difference between the minimum distance is smaller than the old minimum
				indexj = j;
			}
		}
		seek_value += diff(temp[indexj], temp[0]);
		temp[0] = temp[indexj];
		temp.erase(temp.begin()+indexj);
	}
	seek_value += diff(temp[0], temp[1]);
	return seek_value;
}

size_t NCL(vector<size_t> const &block_list) {
	vector<size_t> lesser;
	vector<size_t> greater;
	lesser.emplace_back(block_list[0]);
	size_t seek_value = 0;
	for (size_t i = 1; i < block_list.size();i++) {
		if (block_list[i] < block_list[0]) {
			lesser.emplace_back(block_list[i]);
		}
		else if (block_list[i] > block_list[0]) {
			greater.emplace_back(block_list[i]);
		}
	}
	seek_value += SSTF(greater); // Why redo the work?
	//seek_value += diff(*std::min_element(greater.begin(), greater.end()),*std::min_element(lesser.begin(), lesser.end()));
	seek_value += SSTF(lesser); // When it had already been done?
	return seek_value;
}


size_t CL(vector<size_t> const &block_list) {
	vector<size_t> lesser;
	vector<size_t> greater;
	lesser.emplace_back(block_list[0]);
	auto minElem = (std::min_element(block_list.begin(), block_list.end()));
	size_t seek_value = 0;
	for (size_t i = 1; i < block_list.size(); i++) {
		if (block_list[i] < block_list[0]) {
			lesser.emplace_back(block_list[i]);
		}
		else if (block_list[i] > block_list[0]) {
			greater.emplace_back(block_list[i]);
		}
	}
	std::sort(greater.begin(), greater.end());
	std::reverse(greater.begin(), greater.end());
	seek_value += SSTF(lesser); // Why redo the work?
	seek_value += diff(*greater.begin(), *minElem);
	seek_value += SSTF(greater); // When it had already been done?
	return seek_value;
}

int main() {
	greeting();
	
	vector<size_t> block_list; // A vector simply because we do not know how long it will be, and a vector has fast access to each element forward.
	// NOTE: Vector chosen over forward list because we are inserting elements at the back of the container, otherwise a list would have been superior.
	// Also size_t is a known and consistent memory size than a standard int, thus it is more predicatable in large scale.
	size_t input;
	while (cin) {
		cin >> input;
		block_list.emplace_back(input); // Create the list in place into block_list
	}
	if(block_list.back() == 0)	block_list.erase(block_list.end()-1); //I'm removing a weird element in my debugging.
	
	cout << "FCFS Total Seek: " << FCFS(block_list) << endl;
	cout << "SSTF Total Seek: " << SSTF(block_list) << endl;
	cout << "LOOK Total Seek: " << NCL(block_list) << endl;
	cout << "C-LOOK Total Seek: " << CL(block_list) << endl;
	return 0;
}