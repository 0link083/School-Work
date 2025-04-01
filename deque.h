// deque.h 
// Michael Shipley 10805660
// 9/8/2021

// I learned that the error handling can be more troublesome than expected in a program like this.
// I had some logic errors of my own which delayed the project a few hours. Shoulda started sooner.

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <cassert>

using std::logic_error;

template<typename T>
class Deque {
private:
	enum { CHUNK = 10 };

	T* internalArray; // This is the pointer to the internal array. The pointer may change what it points to.
	size_t frontV; // interger iterator for front used element. Insert before this, remove at this.
	size_t backV; // integer iterator for back empty element. Insert at this, remove before this.
	size_t sizeV; // size == sizeof(internalArray), not the used elements but all possible elements.

	void expand() {
		T* temp = new T[size() + CHUNK];
		sizeV = sizeV + CHUNK;
		/*
		size_t oldElements = size(); // This is to save calculation time on our loop.
		for (size_t i = 0; i < oldElements; i++) {
			temp[frontV + (CHUNK / 2) + i] = internalArray[frontV + i]; // copies elements into array from old array in original order.
		}
		*/
		std::copy(begin(), end(), &temp[frontV + CHUNK/2]); // Copy using the wonderful standard library into the new array about where it was + half of Chunk. This recenters the array.
		assert(std::equal(begin(), end(), &temp[frontV+CHUNK/2])); // Assertion for defensive Programming
		frontV = frontV + (CHUNK / 2); // We moved forward in our internal array
		backV = backV + (CHUNK / 2); // We moved forward in our internal array
		delete[] internalArray;
		internalArray = temp;
	}

public:
	Deque() { // Allocates a default-size (CHUNK) array
		internalArray = new T[CHUNK];
		frontV = backV = (CHUNK / 2); //Assign front and back to the number representation of the location halfway through the array.
		sizeV = CHUNK;
	}
	~Deque() { // Deletes array heap memory
		delete[] internalArray;
	}
	Deque(const Deque&) = delete; // Disables copy
	Deque& operator=(const Deque&) = delete; // Disables assignment

	void push_front(T element) { // Adds new element to the front (left end)
		if (frontV == 0) {  // I am trying to be explicit that this is the front of the array at 0.
			expand();
		}
		frontV--;
		internalArray[frontV] = element;
		
	}
	void push_back(T element) { // Adds new element to the back (right end)
		if (backV == sizeV) {  // address check for end of array. can be fooled if we store pointers of the last element.
			expand();
		}
		internalArray[backV] = element;
		backV++;
	}
	T& front() { // Returns a reference to the first used element
		if (frontV == backV)
			throw (logic_error("Out of range.")); // We expect the .cpp tp handle the errors. We were just asked to throw them.
		T& a = internalArray[frontV];
		return a; // Returns the address of the element currently in the front.
	}
	T& back() { // Returns a reference to the last used element
		if (frontV == backV)
			throw (logic_error("Out of range."));
		T& b= internalArray[backV-1];
		return b; // Returns the address of the element currently in the back.
	}
	T& at(size_t pos) { // Just for iterator notation
		if ((frontV == backV) || (pos < 0) || (pos >= size())) {
			throw(logic_error("Out of range."));
		}
		T& c = internalArray[(frontV + pos)];
		return c;
	}
	void pop_front() { // "Removes" first deque element(just change front_)
		if (frontV == backV) return;
		assert(frontV > 0);
		frontV++;
	}
	void pop_back() { // "Removes" last deque element(just change back_)
		if (frontV == backV) return;
		assert(backV>0);
		backV--;
	}
	size_t size() const { // Returns the # of used items. NOTE:size_t is defined in <cstddef>
		return (backV - frontV);
	}
	T* begin() { // Returns a pointer to the first element
		return &internalArray[frontV];
	}
	T* end() { // Returns a pointer to one position past the last element
		return &internalArray[backV];
	}
};
