// tbitarray.cpp: A cursory test for the BitArray class
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "bitarray.h"
#include "test.h"
using namespace std;

// Test program
int main() {
   BitArray<> b;
   const BitArray<> b1{b}; // Test copy constructor
   
   // Test empty Bitarray properties
   test_(b.size() == 0);
   test_(b.count() == 0);
   test_(b.capacity() == 0);
   test_(!b.any());
   
   // Validate construction and to_string()
   BitArray<> b2{5};
   test_(b2.size() == 5);

   test_(b2.to_string() == "00000");

   // Test copy, assign, equality, and from_string
   BitArray<> b3{b2};

   ostringstream os;
   os << "101" << 'a' << "0101";
   istringstream is{os.str()};
   b3 = BitArray<>{};
   is >> b3;
   test_(b3.to_string() == "101");
   is.get();
   is >> b3;
   test_(b3.to_string() == "0101");
   os.str("");
   os << 'a';
   istringstream is2{os.str()};
   is2 >> b3;
   test_(!is2);
   test_(b3.to_string() == "0101");

      // Test move operations
   BitArray<> b4{move(b3)};
   BitArray<> b4b;
   b4b = move(b4);
   test_(b4b.to_string() == "0101");
   
   BitArray<> b9{"11111111111111111111111111000000000000000000000000000011"};
   ostringstream ostr;
   ostr << b9;
   test_(ostr.str() == "11111111111111111111111111000000000000000000000000000011");
   test_(b9.count() == 28);

   BitArray<> b13("");
   test_(b13.size() == 0);

      BitArray<> x{"011010110"}; // Also tests string constructor
   test_(x.count() == 5);
   test_(x.any());
   BitArray<> y{~x};
   nothrow_(x.toggle());
   test_(x == y);
   test_(x.to_string() == "100101001");
 
   report_();
}

/* Output (should have at least 4 move assignments):
move assignment      
move assignment
move assignment
move constructor
move assignment

Test Report:

   Number of Passes = 19
   Number of Failures = 0

*/
