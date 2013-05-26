//////////////////////////////////////////////////////////////////////////
//
// refer to
// http://en.wikipedia.org/wiki/Special_member_functions
// 
// 
// 
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"

class A {
public:
	A() {} // Default constructor
	A(const A&) {printf("Copy constructor\n");} // Copy constructor
	A& operator = (const A&) {printf("Copy assignment\n");return*this;} // Copy assignment
};

class B {
public:
	B() {} // Default constructor
	explicit B(const B&) {printf("Copy constructor\n");} // Copy constructor
	B& operator = (const B&) {printf("Copy assignment\n");return*this;} // Copy assignment
};

int main()
{
	A a1;
	A a2=a1;
	a1=a2;

	B a1;
	// B a2=a1; // compiler error, won't call copy assignment
	a1=a2;
	return 0;
}