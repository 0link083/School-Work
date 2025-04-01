#include "Pool.h"
#include <new>

using namespace std; // BAD PRACTICE....

static Pool* pool; // File Scope

class MyObject {
	int id;
	string name;
private:
	MyObject(int i, const string& nm) : name(nm) {
		id = i;
	}
public:
	//Overload operator
	static void* operator new(size_t t) {
		void* p = pool->allocate();
		return p;
	}
	static void operator delete (void*p) {
		return pool->deallocate(p);
	}

	static MyObject* create(int id, const string& name) {
		void* val = nullptr;
		val = new MyObject(id, name);
		return reinterpret_cast<MyObject*>(val);
	}
	
};


