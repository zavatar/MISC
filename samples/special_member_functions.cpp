//////////////////////////////////////////////////////////////////////////
//
// refer to
// http://en.wikipedia.org/wiki/Special_member_functions
// 
// 
// 
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"
#include <vector>

class A {
public:
	A() {} // Default constructor
	A(const A&) {printf("Copy constructor\n");} // Copy constructor
	A& operator = (const A&) {printf("Copy assignment\n");return*this;} // Copy assignment
};

class B {
public:
	B() {printf("B Default constructor\n");} // Default constructor
	explicit B(const B&) {printf("Copy constructor\n");} // Copy constructor
	B& operator = (const B&) {printf("Copy assignment\n");return*this;} // Copy assignment
	explicit B(B&&) {printf("Move constructor\n");} // Move constructor
	B& operator = (B&&) {printf("Move assignment\n");return*this;} // Move assignment
	~B() {} // Default destructor
};

class C : public B {
public:
	C() {}
	C(const C&) {}
	C(const C&&) {}
	C& operator = (const C&) {}
	C& operator = (const C&&) {}
};

int main()
{
	A a1;
	A a2=a1; // regard as conversion
	a1=a2;
	printf("\n");

	B b1;
	B b2;
	// B b2=b1; // compiler error, won't call copy assignment
	b1=b2;
	printf("\n");

	C c1;
	C c2(c1);
	C c3(static_cast<C&&>(c1));
	printf("\n");

	std::vector<int> v1(10);
	std::vector<int> v2(static_cast<std::vector<int>&&>(v1));
	return 0;
}