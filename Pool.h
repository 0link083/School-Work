//pool.cpp
// Michael Shipley
#include <iostream>
#include <cstddef>

using namespace std;

class Pool {
	void** poolList; // This is an array of voidptr that holds the locations of blocks of memory together. 
	size_t usedList; // This is a way to keep track of how many elements... exist...
	size_t objSize, block;
	void* freeptr; // This is the linked list head that keeps track of where preallocated memory is. It often equals itself.
	char* tempo = nullptr; // So I can return and keep things.............................................

public:
	Pool(size_t elemSize, size_t blockSize = 5) {
		objSize = elemSize;
		block = blockSize;  // I want to keep track of these two values for later pool creation
		cout << "Initializing a pool with element size " << objSize << "and block size " << block << endl; //IN EXPECTED OUTPUT
		poolList[0]; // INITIALIZE TO ZERO size. important later...
		freeptr = nullptr; // INTIALIZE to nullptr.
		newBlock(elemSize, blockSize); // Create an array of char (since char holds byte sized values)
	}
	~Pool() {
		/* I had a realizeation that the used list was never allocated on the heap directly. */
		// delete[] usedList; // Deconstruct usedList.

		freeptr = nullptr; // Deconstruct freeList. Aka get rid of any mention it exists and the rest will never know or care.

		/* for (auto i = 0; i < sizeof(poolList); i++) { // Deconstruct the pools using the poolList
			delete poolList[i]; // Delete each pool.... could this have been done through delete[]? yes
		} */
		delete[] poolList; // Deconstruct the poolList
	}
	void* allocate() { // Gets the pointer to a pre-allocated block of memory in the pool
		if (freeptr == nullptr) {
			newBlock(objSize, block);
		}
		cout << "Cell allocated at " << freeptr << endl;
		tempo = *(reinterpret_cast<char**>(freeptr));
		*(reinterpret_cast<void**>(freeptr)) = freeptr; // Assign freeptr to the value inside freeptr. Deleting an item to the linked list.

		usedList++;
		return tempo; // temp holds our free location.

	}
	void deallocate(void* obj) { // This will free the object on the used list and add that location to the free list. 
		// Make the value stored at the address given by obj equal to the address stored currently in freeptr.
		cout << "Cell deallocated at " << freeptr << endl;
		*(reinterpret_cast<void**>(obj)) = freeptr; //Take the ADDRESS of the ith element, if this were objects, and store FREEPTR inside
		freeptr = *(reinterpret_cast<char**>(freeptr)); // Assign the value inside freeptr to freeptr. Adding an item from the linked list.
		// freeptr now should hold the recently freed address to be the start of the list.	
		usedList--;
	}

	// done when the memory was full on our list so freeptr==nullptr
	void newBlock(size_t elemSize, size_t blockSize) {
		increaseList();

		char* pool = new char[elemSize * blockSize]; // Allocate the memory needed for the new poooooool on the HEAP.
		poolList[sizeof(poolList)] = pool; // Make the last element, or the free element, apart of the new list.
		cout << "Expanding pool..." << endl;

		cout << "Linking cells starting at " << poolList[0] << endl;
		for (auto i = 0; i < blockSize; i++) {
			*(reinterpret_cast<void**>(pool[elemSize*i])) = freeptr; //Take the ADDRESS of the ith element, if this were objects, and store FREEPTR inside
			freeptr = *(reinterpret_cast<char**>(pool[elemSize*(i)])); //Take the ADDRESS of the ith element, if this were objects, and store that in FREEPTR
		}
	}

	void increaseList() {
		/* DEEP COPY */
		void** newList[sizeof(poolList) + 1];
		memcpy(newList, poolList, sizeof(poolList)); // Make a copy of the WHOLE list and send it to new list...
		delete[] poolList;
		memcpy(poolList, newList, sizeof(newList));
		delete[] newList;
	}

	void displayStatus() {
		cout << endl << "Live Cells: " << usedList << ", Free Cells: " << sizeof(poolList) - usedList << endl;
		displayFreeList();
	}

	void displayFreeList() {
		void* temp = freeptr;
		cout << "Free list:" << endl;
		while (temp != nullptr) {
			cout << temp << endl;
			temp = *(reinterpret_cast<char**>(temp)); //Take the ADDRESS of the ith element, if this were objects, and store that in temp
		}
		cout << endl;
	}
	/*void decreaseList() {
		// DEEP COPY
		void** newList[sizeof(poolList) - 1];
		bool nulflag = true; //I'll use this to change my for loop operation
		for (auto i = 0; i < sizeof(poolList)+1; i++) {
			if (poolList[i] == nullptr)
				nulflag = false;

			if (nulflag) {
				memcpy(newList[i], poolList[i], sizeof(poolList)); // Makes a copy of an element.
			} else {
				memcpy(newList[i], poolList[i+1], sizeof(poolList)); // Make a copy of an element whilst avoiding the nullvalue.
			}
		}
		delete[] poolList;
		memcpy(poolList, newList, sizeof(newList));
		delete[] newList;
	}*/
};

