//////////////////////////////////////////////////////////////////////////
//
// refer to
// http://publib.boulder.ibm.com/infocenter/lnxpcomp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8l.doc%2Flanguage%2Fref%2Fcplr383.htm
//
// User-defined conversions
// ---Conversion by constructor
// ---The explicit specfier
// ---Conversion functions
//
// Chapter 2. of <Inside the C++ Object Model>.
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"

class istream1 : public std::istream {
public:
	// override the same function in ios_base class
	operator void *() const {
		return (void *)this;
	}
};

class istream2 : public std::istream {
public:
	// Schwarz Error
	operator int() const {
		return (int)this;
	}
};

class A {
	int m_x;
public:
	A(int x): m_x(x) {} // Conversion by constructor
	A(const char* s, int x=0): m_x(x) {} // Conversion by constructor
	operator int() const {return m_x;} // Conversion functions
};

class B {
	int m_x;
public:
	explicit B(int x): m_x(x) {} // explicit specifier
	explicit B(const char* s, int x=0): m_x(x) {} // explicit specifier
	operator int() const {return m_x;} // Conversion functions
};

int main()
{
#define cin1 (*(istream1*)&std::cin)
#define cin2 (*(istream2*)&std::cin)

	if (cin1){}
	// cin1 << 10; // should be cin1>>10
	if (cin2){}
	cin2 << 10; // Schwarz Error

	// User-defined conversions include:
	// 1. Conversion by constructor
	// 2. Conversion functions
	A a1 = A(11); // equivalent to 
	A a2 = 11; // implicitly convert by constructor
	A a3 = A("string");
	A a4 = "string";

	B b1 = B(12);
	// B b2 = 12; // error
	B b3 = B("string");
	// B b4 = "string"; // error

#undef cin1
#undef cin2
	return 0;
}