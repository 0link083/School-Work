// deque.h
// Author: Michael Shipley
// This is the header file to deque, which is a double ended queue.
template <typename T>
class Deque {
		// Private Variables
	private:
		int size;
		Node* first<T>;
		Node* last<T>;

	// Public Functions
	public:
		Deque<T>() {
			size = 0; // Size should be zero to start.
			last = first = nullptr; // Set both Node pointers to null pointer
		}
		~Deque() {
			if (first != nullptr) delete first; // The destructor should call the first nodes destructor.
		}
		// pushes a value to the front of the deque
		void push_front(int value) {
			if(first == nullptr)
				last = first = new Node(value, nullptr, nullptr); // Assign the front and the back pointers to the Node created.
			else 
				first = first->left = new Node(value, nullptr, first); // Stitch the new node on the left side of the structure, and make it the new first.
			size++; // increment the size of the structure
		}
		// pushes a value to the back of the deque
		void push_back(int value) {
			if (first == nullptr)
				last = first = new Node(value, nullptr, nullptr); // Assign the front and the back pointers to the Node created.
			else 
				last = last->right = new Node(value, last, nullptr); // Stitch the new node on the right side of the structure, and make it the new last.
			size++; // increment the size of the structure
		}
		void pop_front() {
			if (size == 0) return; // remove the empty case.
			Node* temp = first;
			first = first->right;
			first->left = nullptr;
			temp->right = nullptr;
			delete temp;
			size--;
		}
		void pop_back() {
			if (size <= 0) return; // remove the empty case.
			Node* temp = last;
			last = last->left;
			last->right = nullptr;
			temp->left = nullptr;
			delete temp;
			size--;
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
			return size;
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

