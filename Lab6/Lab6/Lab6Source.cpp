#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <array>

using namespace std;

void f(int n) {
	cout << n << "\n";
}

template<class InputIt, class UnaryFunction, class UnaryPredicate>
constexpr UnaryFunction for_each_if(InputIt first, InputIt last, UnaryFunction f, UnaryPredicate p)
{
	for (; first != last; ++first) {
		if(p(*first))
			f(*first);
	}
	return f; // implicit move since C++11
}

template<class InputIt>
int range(InputIt first, InputIt last, int increment) {
	for (; first != last; ++first)
		(*first) = increment++;
	return increment;
}

int main() {
	//array<int, 4> a = { 1,2,3,4 };
	vector <int> a = { 1,2,3,4 };
	for_each_if(a.begin(), a.end(), f, ([](int x) {return ((x % 2) == 0);}));
	
	//could not include a since it was already defined.
	vector<int> b = { 1,3,2,4 };
	cout << is_sorted(a.begin(), a.end()) << endl; // 1
	cout << is_sorted(b.begin(), b.end()) << endl; // 0
	
	array<int, 4> c;
	int n = range(c.begin(), c.end(), 1);
	array<int, 2> d;
	range(d.begin(), d.end(), n);
	copy(c.begin(), c.end(), ostream_iterator<int>(cout, " ")); // 1 2 3 4
	cout << endl;
	copy(d.begin(), d.end(), ostream_iterator<int>(cout, " ")); // 5 6
	cout << endl;

	getchar();
}


/* Output:
2
4
1
0
1 2 3 4
5 6
*/
