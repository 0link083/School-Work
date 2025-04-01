// deque.h
// Author: Michael Shipley
// This is the header file to deque, which is a double ended queue.

#include <vector>
using namespace std;

template <typename T>
class Deque {
	vector<T> deVector; // I realized that the implementation must be an array.
	int* first = deVector.front;
	int* last = deVector.back;
	int size = sizeof(deVector);
	// Public Functions
	public:
		Deque<T>() {
			size = 0; // Size should be zero to start.
			last = first = nullptr; // Set both Node pointers to null pointer

		}
		/*~Deque() {
			if (first != nullptr) delete first; // The destructor should call the first nodes destructor.
		}*/
		// pushes a value to the front of the deque
		void push_front(int value) {
			deVector.emplace(deVector.front);
		}
		// pushes a value to the back of the deque
		void push_back(int value) {
			deVector.push_back(value);
		}
		void pop_front() {
			deVector.erase(deVector.front);
		}
		void pop_back() {
			deVector.pop_back();
		}
		int& at(int iterator) {
			/*if (size <= 0) {
				int x = 0;
				return x; // Unused hopefully case where structure is empty.
			}*/ // Replaced because expectation is logical error
			Node* temp = first;
			for (auto x : iterator)
				temp = temp->right;
			return temp.getReferenceOfValue();
		}
		int& front() {
			return front.getReferenceOfValue();
		}
		int& back() {
			return back.getReferenceOfValue();
		}
		int size() {
			return sizeof(deVector);
		}
};

template <typename T>
struct Node {
	// Stucts don't care about visibility.
	T value;
	Node* left, right;
	Node(T value, Node* left, Node* right) {
		this.value = value;
		this.left = left;
		this.right = right;
	}

	// returns the refrence of value, so it can be manipulated.
	&T getReferenceOfValue() {
		return &value;
	}
};

