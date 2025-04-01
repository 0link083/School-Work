// BitArray.h
// Michael Shipley CS 3370

#ifndef BITARRAYH
#define BITARRAYH

#include <vector>
#include <cstddef>
#include <climits>
#include <string> // One day I'll understand why this isn't included in std library
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib> // itoa
#include <exception>

using std::endl;
using std::cout;
using std::cerr;
using std::logic_error;
using std::runtime_error;
using std::size_t;
using std::vector;
using std::string;
using std::for_each;

template<class IType = size_t> //Defaults to size_t but should work with any unsigned type.
class BitArray {
	enum {BITS_PER_WORD = CHAR_BIT * sizeof(IType)}; // This is to make sure that we aren't assuming the size of a word, or the size of a byte.
	friend class reference;
	vector<IType> internalVector;
	size_t _size;

	void set(size_t pos) { //Sets to 1 at pos
		*this[pos] |= (1u << pos%BITS_PER_WORD);
	}
	void set()	{ // Sets all to 1
		for (; internalVector.begin()!=internalVector.end(); ++internalVector.begin()) {
			*internalVector.begin() = ~0u;
		}
	}
	void reset(size_t pos) {
		*this[pos] &= ~(1u << pos%BITS_PER_WORD);
	}
	void reset() {
		for_each(internalVector.begin(), internalVector.end(), [](IType i) {i = 0U;});
	}

public:
	class reference {
		BitArray& b;
		size_t pos;
		size_t index;
	public:
		reference(BitArray<IType>& bitStructure, size_t p) : b(bitStructure) {
			pos = p % bitStructure.get_BITS_PER_WORD();
			index = p / bitStructure.get_BITS_PER_WORD();
		}
		~reference() = default;
		reference& operator=(bool bit) {
			// Set the bit in position pos to true or false, per bit
			if (bit)
				b.internalVector[index] |= (1u << pos) - (1u << pos - 1); // shift by pos bits to the left, subtract the bits before it out... maybe it's better to bitwise and wwith zeros? then bit wise or, to set bit
			else
				b.internalVector[index] &= ~(0u << pos) - (1u << pos - 1); // shift to unset bit
			return *this;
		}
		reference& operator=(const reference& x) {
			if (*this)
				b.internalVector[index] |= (1u << pos); //shift by pos bits to the left then bit wise or, to set bit
			else
				b.internalVector[index] &= ~(1u << pos); //shift to unset bit
			return *this;
		}
		operator bool() const { // This can only be a const
			// Return true or false per the bit in position pos
			return b.internalVector[index] & (1u << pos);
		}
		bool operator~() const {
			return !(b.internalVector[index] & (1u << pos));
		}
		bool operator^(const bool other) const { // Returning a bool because this should be an expression used to validate not assign.
			return (*this ^ other); //Bitwise XOR via two operators should not change it's elements
		}
		reference& operator^=(const reference& other) {
			*this = *this ^ other; // Should change it's element this
			return *this; //returning the changed reference bit to allow chaining.
		}
		reference& operator|(const bool modifier) {
			b.internalVector[index] |= (modifier << pos) | modifier;
		}
		void flip() {
			if (*this)
				*this = 0;
			else
				*this = 1;
		}
		reference& set() {
			*this = 1;
			return *this;
		}
		reference& unset() {
			*this = 0;
			return *this;
		}
		reference& operator==(reference& other) {
			return *this == *other;
		}
		reference& operator==(bool other) {
			return *this == other;
		}
	};
	
	size_t size() const { // Number of bits used in use in the vector, not the number of bits possible
		return _size;
	}
	size_t capacity() {
		return internalVector.capacity * BITS_PER_WORD;
	}
	bool checkAccess(size_t pos) {
		try {
			if (pos > size()) {
				std::logic_error e("The position that was accessed was out of the vector.");
				throw e;
			}
		}
		catch (std::logic_error &e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}

	// Comparison ops
	bool operator==(const BitArray<IType>& other) const {
		return this->internalVector == other.internalVector;
	}

	bool operator!=(const BitArray<IType>& other) const {
		return this->internalVector != other.internalVector;
	}

	bool operator<(const BitArray<IType>& other) const {
		return this->size() < other.size();
	}

	bool operator<=(const BitArray<IType>& other) const {
		return this->size() <= other.size();
	}

	bool operator>(const BitArray<IType>& other) const {
		return this->size() > other.size();
	}

	bool operator>=(const BitArray<IType>& other) const {
		return this->size() >= other.size();
	}

	// Object Management
	size_t get_BITS_PER_WORD() {
		return BITS_PER_WORD;
	}
	explicit BitArray(size_t numOfBits = 0) {
		// Set a number of zeros based on the parameter
		for (size_t i = numOfBits / BITS_PER_WORD; i >= 0; --i) {
			internalVector.emplace_back(0U);
		}
		_size = numOfBits;
	}
	explicit BitArray(const string& BitString) {
		// String to bits
		// Take each character and append it to the vector.
		_size = 0;
		for (size_t i = 0; i < BitString.length(); ++i) {
			if (BitString.at(i) == "0") {
				insert(i, 0);
			}
			else if (BitString.at(i) == "1") {
				insert(i, 1);
			}
			// Otherwise ignore the character.
		}
	}
	BitArray(const BitArray<IType>& other) {
		cout << "copy constructor" << endl; // Copy constructor
		this->_size = other._size;
		this->internalVector = other.internalVector;
	} 
	BitArray<IType>& operator=(const BitArray<IType>& other) {
		cout << "copy assignment" << endl; // Copy assignment
		this->_size = other._size;
		this->internalVector = other.internalVector;
	}
	BitArray(BitArray<IType>&& other) noexcept { // Move constructor
		this->internalVector = other.internalVector;
		this->_size = other._size;
		cout << "move constructor" << endl;
	}
	BitArray<IType>& operator=(BitArray&& other) noexcept { // Move assignment
		this->internalVector = other.internalVector;
		this->_size = other._size;
		cout << "move assignment" << endl;
	}
	
	size_t capacity() const { // # of bits the current allocation can hold
		return internalVector.capacity()*BITS_PER_WORD; // Returns number of used bits.
	}

	// Mutators
	BitArray<IType>& operator+=(bool val) { // Append a bit
		insert(size()+1,val);
	}
	BitArray<IType>& operator+=(const BitArray<IType>& other) { // Append a BitArray
		insert(size()+1, other);
	}
	void erase(size_t pos, size_t nbits = 1) { // Remove “nbits” bits at a position
		// Remove bits from pos to pos+n-1 (standard iter notation)
		// Also move the proceeding bits into their location. This is not the same as reset.
		if (pos >= size()) {
			pos = size() + 1; 
		}
		*this[pos] <<= (pos + nbits - 1);
	}
	void insert(size_t pos, bool val) { // Insert a bit at a position (slide "right")
		if (pos >= size()) 
			pos = size() + 1; // guarentees that we emplace at the end of our current indexing
		if (internalVector.size() > pos / BITS_PER_WORD || internalVector.empty()) {
			internalVector.emplace_back(val);
			++_size;
		}
		else if (internalVector.size() <= pos / BITS_PER_WORD) {
			// This is now making the use of a vector... regretable.
			// shift every bit to the right of the current bit by notation of bitArray[pos] to make room for the bit you HAD to place in the middle of it for some reason.
			*this[pos] >> val; // In theory this only shifts bits after position and adds the new bit in this place. But I'm not so sure of this. Computationally expensive.
			++_size;
		}
	}
	void insert(size_t pos, const BitArray<IType>& other) // Insert an entire BitArray object
	{
		//Perhaps a right shift is in order?
		if ( pos >= size())
			pos = size()+1;
		for (size_t i = 0u; i < other.size(); ++i) {
			*this[pos + i] >> 1u; // Shift 1 to the right, and then
			*this[pos + i] = other[i]; // put something where it used to be.
		}
		_size += other.size();
	}



	// Bitwise ops
	
	bool operator[](size_t pos) const {
		if (!checkAccess(pos)) return; 
		bool returnval = reference(*this, pos);
		return returnval;
	}
	reference& operator[](size_t pos) {
		if (!checkAccess(pos)) return;
		if ((pos / BITS_PER_WORD) > internalVector.size()) {
			internalVector.emplace(0U); // Should make a new vector entry expansion without increasing the size of the BitArray object. 
		}
		return reference(*this, pos);
	}
	BitArray<IType> operator~() const {
		BitArray<IType> b = *this; //copy this bit array
		b.toggle(); // Flip the copied array
		return b; // return that flipped array
	}
	BitArray<IType> operator<<(unsigned int pos) const { // Shift operators…
		// LEFT SHIFT BY POS
		// return the shifted version. Is this mutable? no, its const
		BitArray<IType> b = *this;
		b[0] << pos;
		return b;
	}
	BitArray<IType> operator>>(unsigned int pos) const {
		BitArray<IType> b = this;
		b[0] >> pos;
		return b;
	}
	BitArray<IType>& operator<<=(unsigned int pos) {
		return this <<= pos;
	}
	BitArray<IType>& operator>>=(unsigned int pos) {
		return this >>= pos;
	}	


	void toggle(size_t pos) {
		if (!checkAccess(pos)) return; 
		if(this[pos] == false)
			this[pos].set();
		else
			this[pos].reset();
	}
	void toggle() {  // Toggles all bits
		for (size_t i = 0; i < internalVector.size()*BITS_PER_WORD; ++i) {
			if (this[i] == false) 
				this[i].set();
			else 
				this[i].reset();
		}
	}


	// Extraction ops
	BitArray<IType> slice(size_t pos, size_t count) const // Extracts a new sub-array
	{
		if (!checkAccess(pos+count-1)) return; // If the furthest element is outside
		return BitArray<IType>( (1u >> pos + count) - 1u >> pos); // returns the chunk of bits as a new string constructed BitArray.
	}

	// Counting ops

	size_t count() const { // The number of 1-bits present
		// go sequentially through each bit and add if 1, ignore if 0. 
		size_t _count = 0u;
		for (size_t i = 0u; i < internalVector.size(); ++i) {
			if (internalVector[i]) _count++;
		}
		return _count;
	}
	bool any() const { // Optimized version of count() > 0
		// go through sequentially until a bit is 1 then return true, else return false
		for (; internalVector.begin() != internalVector.end(); internalVector.begin()++) {
			if (*internalVector.begin() > 0) return true;
		}
		return false;
	}

	// String conversion
	string to_string() const {
		std::stringstream ss;
		std::string num_as_string;
		// I don't think this works the way I want it to.
		for_each(internalVector.begin(), internalVector.end(), [&](IType num) {num_as_string =std::to_string(num); ss << std::stoul(num_as_string, 0, 2); });
		return ss.str();
	}

	

	// Stream I/O (define these in situ—meaning the bodies are inside the class)
	friend std::ostream& operator<<(std::ostream& stream, const BitArray<IType>& bitArray)  {
		stream << bitArray.to_string();
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, BitArray<IType>& bitArray)  {
		string s;
		stream >> s;
		bitArray += BitArray(s); // Append the new bit array object constructed via string form.
		return stream;
	}
};

#endif // !BitArray.h