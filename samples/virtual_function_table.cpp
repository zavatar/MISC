//////////////////////////////////////////////////////////////////////////
//
// refer to http://blog.csdn.net/haoel/article/details/1948051
//
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"

class Base1 {
public:
	virtual void f() { printf("\tBase1::f\n"); }
	virtual void g() { printf("\tBase1::g\n"); }
	virtual void h() { printf("\tBase1::h\n"); }
};

class Base2 {
public:
	virtual void f() { printf("\tBase2::f\n"); }
	virtual void g() { printf("\tBase2::g\n"); }
	virtual void h() { printf("\tBase2::h\n"); }
};

class Base3 {
public:
	virtual void f() { printf("\tBase3::f\n"); }
	virtual void g() { printf("\tBase3::g\n"); }
	virtual void h() { printf("\tBase3::h\n"); }
};

class Derive1: public Base1 {
public:
	virtual void f() { printf("\tDerive1::f\n"); } // Ðéº¯Êý¸²¸Ç
	virtual void g1() { printf("\tDerive1::g1\n"); }
	virtual void h1() { printf("\tDerive1::h1\n"); }
};

class MultiDerive1: public Base1, public Base2, public Base3 {
public:
	virtual void f() { printf("\tMultiDerive1::f\n"); } // Ðéº¯Êý¸²¸Ç
	virtual void g1() { printf("\tMultiDerive1::g1\n"); }
	virtual void h1() { printf("\tMultiDerive1::h1\n"); }
};

void foreachVirtual_Table(size_t* p, size_t end) {
	typedef void(*Fun)(void);
	printf("\tEnd: %p\n", end);
	for (int i=0; ; i++) {
		Fun pFun = (Fun)*((size_t*)*p+i);
		if (size_t(pFun) == end) return;
		printf("\tAddress: %p", pFun);
		pFun();
	}
}

void foreachVirtual_Table(size_t* p, bool n) {
	printf("Try Debug on VC\n"); // TODO
}

#if(MISC_ISGCC)
#define END size_t(0)
#define MULTIEND(_t) size_t(0-4*(_t))
#elif(MISC_ISVC)
#	if(defined(_DEBUG))
#	define END size_t(0)
#	define MULTIEND(_t) size_t(0)
#	else
#	define END bool(0)
#	define MULTIEND(_t) bool(0)
#	endif

#endif

int main()
{
	Base1 b;
	printf("Address of Virtual-Table: %p\n", *(size_t*)&b);
	printf("Address of First Function in Virtual-Table: %p\n", *(size_t*)*(size_t*)&b);
	size_t end = *((size_t*)*(size_t*)&b+3);
	printf("Label of Virtual-Table ending: %d\n\n", end);

	printf("\nVirtual-Table of Base Class:\n");
	foreachVirtual_Table((size_t*)&b, END);

	Derive1 d1;
	printf("\nVirtual-Table of Derive1 Class:\n");
	foreachVirtual_Table((size_t*)&d1, END);

	MultiDerive1 md1;
	printf("\nVirtual-Table of MultiDerive1 Class:\n");
	for (int i=0; i<3; i++) {
		printf("Virtual-Table %d:\n", i+1);
		foreachVirtual_Table((size_t*)&md1+i, MULTIEND((i+1)%3));
	}

	return 0;
}