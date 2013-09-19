//////////////////////////////////////////////////////////////////////////
//
// refer to
// http://en.wikipedia.org/wiki/Special_member_functions
// 
// NVRO, named return value optimization
// 
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"
#include <vector>

class A {
public:
	A() {printf("\tA Default constructor\n");} // Default constructor
	A(const A&) {printf("\tA Copy constructor\n");} // Copy constructor
	A& operator = (const A&) {printf("\tA Copy assignment\n");return*this;} // Copy assignment
	~A() {printf("\tA Default destructor\n");} // Default destructor
};

class B {
public:
	B() {printf("\tB Default constructor\n");} // Default constructor
	explicit B(const B&) {printf("\texplicit B Copy constructor\n");} // Copy constructor
	B& operator = (const B&) {printf("\tB Copy assignment\n");return*this;} // Copy assignment
	explicit B(B&&) {printf("\texplicit B Move constructor\n");} // Move constructor
	B& operator = (B&&) {printf("\tB Move assignment\n");return*this;} // Move assignment
	~B() {printf("\tB Default destructor\n");} // Default destructor
};

class C : public B {
public:
	C() {printf("\tC Default constructor\n");}
	C(const C&) {printf("\tC Copy constructor\n");}
	C(const C&&) {printf("\tC Move constructor\n");}
	C& operator = (const C&) {printf("\tC Copy assignment\n");return*this;}
	C& operator = (const C&&) {printf("\tC Move assignment\n");return*this;}
	~C() {printf("\tC Default destructor\n");}
};

class D {
public:
	D() {printf("\tD Default constructor\n");}
	D(const D&) {printf("\tD Copy constructor\n");}
	D(const D&&) {printf("\tD Move constructor\n");}
	D& operator = (const D&) {printf("\tD Copy assignment\n");return*this;}
	D& operator = (const D&&) {printf("\tD Move assignment\n");return*this;}
	~D() {printf("\tD Default destructor\n");}
};

D NVRO() {
	D d; // must have ctor
	return d;
}

int main()
{
	{
		A a1;
		A a2 = a1; // regard as conversion/ ctor
		A a3 = A(a2); // only once ctor
		a1=a2;
	}
	printf("\n");
	{
		B b1;
		B b2(b1);
		// B b2 = B();
		// B b2 = b1; // compiler error, won't call copy assignment and ctor is explicit
		b1=b2;
	}
	printf("\n");
	{
		C c1;
		C c2(c1);
		C c3(static_cast<C&&>(c1));
	}
	printf("\n");
	{
		std::vector<B> v1(2,B());
		std::vector<B> v2(static_cast<std::vector<B>&&>(v1)); // v1 is stolen by v2
		printf("emplace_back:\n");
		v1.emplace_back();
		printf("push_back:\n");
		v1.push_back(B());
		printf("\n");
	}
	printf("NVRO:\n");
	{ // NVRO under release
		NVRO();
	}
	return 0;
}