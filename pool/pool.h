//pool.cpp
// Michael Shipley
#ifndef poolH
#define poolH

#include <cstddef> // byte, size_t
#include <iostream> //cout, endl
#include <vector> //vector for dynamic internal array
#include <algorithm> //for_each

using std::cout;
using std::endl;
using std::byte;
using std::size_t;
using std::vector;

class Pool {
public:
	vector<byte*>* poolMemory; // This is an array of voidptr that holds the locations of blocks of memory together. 
	size_t usedList; // This is a way to keep track of how many elements... exist...
	size_t objSize; // Stored information on sizeof(MyObject)
	size_t block_Size; // Stored information on defined block size
	void* freeptr; // This is the linked list head that keeps track of where preallocated memory is. 

	Pool(const size_t elemSize, const size_t blockSize = 5) {
		objSize = elemSize; //Suggest Removal here././
		block_Size = blockSize;  // I want to keep track of these two values for later pool creation
		cout << "Initializing a pool with element size " << elemSize << "and block size " << blockSize << endl; //IN EXPECTED OUTPUT
		poolMemory = new vector<byte*>; // INITIALIZE TO ZERO size. important later...
		// newBlock(elemSize, block_Size); // Create an array of byte
	}
	~Pool() {
		/*
		for (size_t i = 0; i < sizeof(poolMemory); i++) {
			delete[] poolMemory[i];//Delete each of the chunks.
		}
		*/
		delete poolMemory; // Deconstruct the poolMemory, since that is all that is on the heap.
	}
	void* allocate() { // Gets the pointer to a pre-allocated block of memory in the pool
		if (freeptr == nullptr) {
			newBlock();
		}
		cout << "Cell allocated at " << freeptr << endl;
		void* temp = freeptr; // Assign temp to what free pointer is currently pointing to.
		freeptr = *(reinterpret_cast<byte**>(freeptr)); // Assign freeptr to the value inside freeptr. Deleting an item to the linked list.
		cout << "old cell trace: "<< freeptr << endl;
		usedList++;
		return temp; // temp holds our free location.

	}
	void deallocate(void* &obj) { // This will free the object on the used list and add that location to the free list. 
		// Make the value stored at the address given by obj equal to the address stored currently in freeptr.
		if (obj == nullptr) return; //We can't deallocate nothing now can we?
		void* temp = &(*reinterpret_cast<byte**>(obj));
		*(reinterpret_cast<byte**>(obj)) = (reinterpret_cast<byte*>(freeptr)); // Assign the value inside freeptr to freeptr. Adding an item to the free list.
		freeptr = temp; //Take the ADDRESS of the object, and store FREEPTR inside
		cout << "Cell deallocated at " << freeptr << endl;
		//*(reinterpret_cast<byte**>(freeptr)) = *(reinterpret_cast<byte**>(obj)); // Assign the value inside freeptr to freeptr. Adding an item to the free list.
		// freeptr now should hold the recently freed address to be the start of the list.	
		usedList--;
	}
	void displayStatus() {
		cout << endl << "Live Cells: " << usedList << ", Free Cells: " << sizeof(poolMemory) - usedList << endl;
		profile();
	}

	void profile() {
		void* temp = freeptr;
		cout << "Free list:" << endl;
		while (temp!=nullptr) {
			cout << temp << endl;
			temp = (*reinterpret_cast<byte**>(temp));
		}
		cout << endl;
	}

	void read(void* p) {
		cout << p << endl;
	}

	// done when the memory was full on our list so freeptr==nullptr
	void newBlock() {
		byte* freshBlock = new byte[objSize * block_Size]; // Allocate the memory needed for the new block on the HEAP.
		cout << "Expanding pool..." << endl;

		cout << "Linking cells starting at " << freshBlock << endl;
		for (size_t i = 0; i < block_Size; i++) {
			(reinterpret_cast<byte**>(freshBlock))[(objSize*i)/4] = reinterpret_cast<byte*>(freeptr); // Make the current element hold whatever freeptr is holding.
			freeptr = &reinterpret_cast<byte**>(freshBlock)[(objSize*i)/4]; //Take the ADDRESS of the ith element, and store it to free ptr.
			//cout << "freshBlock at " << &reinterpret_cast<byte**>(freshBlock)[objSize*i / 4] << ": " << reinterpret_cast<byte**>(freshBlock)[objSize*i / 4] << endl;
		} 
		poolMemory->push_back(freshBlock); // Make a new pool memory with one more index to push our new block onto.
		profile();
	}
};

#endif // !poolH