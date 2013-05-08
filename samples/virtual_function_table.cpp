//////////////////////////////////////////////////////////////////////////
//
// refer to 
// http://mentorembedded.github.io/cxx-abi/
// http://blog.csdn.net/haoel/article/details/1948051
// http://stackoverflow.com/questions/3324721/virtual-tables-and-virtual-pointers-for-multiple-virtual-inheritance-and-type-ca
//
// 1. virtual function must be in Virtual-Table (VTable), since for compiler,
// it couldn't determine function address with a Base Class Info.
// (Base Class may be inherited by different Derive Classes)
// 2. The call of virtual function through VTable is pre-compiled as vptr[offset],
// since the offset of function in Base Class is constant for all Derived Class.
// But virtual function isn't always called through VTable, like bp1->Base1::f() 
// 
//
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"

class Base1 {
public:
	virtual void f() { printf("\tBase1::f\n"); }
	virtual void g() { printf("\tBase1::g\n"); }
	virtual void h() { printf("\tBase1::h\n"); }
	// Whatever Derive1 or Derive2, h() always pre-compiled as vptr[2]
};

class Base2 {
public:
	virtual void f() { printf("\tBase2::f\n"); }
	virtual void g() { printf("\tBase2::g\n"); }
	virtual void h2() { printf("\tBase2::h2\n"); }
};

class Base3 {
public:
	virtual void f() { printf("\tBase3::f\n"); }
	virtual void g3() { printf("\tBase3::g3\n"); }
	virtual void h3() { printf("\tBase3::h3\n"); }
};

class Derive1: public Base1 {
public:
	virtual void f() { printf("\tDerive1::f\n"); } // cover Base1
	virtual void g1() { printf("\tDerive1::g1\n"); }
	virtual void h1() { printf("\tDerive1::h1\n"); }
};

class Derive2: public Derive1 {
public:
	virtual void f() { printf("\tDerive2::f\n"); } // cover Base1
	virtual void g() { printf("\tDerive2::g\n"); } // cover Derive1
	virtual void h() { printf("\tDerive2::h2\n"); }
};

class MultiDerive1: public Base1, public Base2, public Base3 {
public:
	virtual void f() { printf("\tMultiDerive1::f\n"); } // cover 3 base class
	virtual void g() { printf("\tMultiDerive1::g\n"); } // cover 2 base class
	virtual void hm() { printf("\tMultiDerive1::hm\n"); }
};

class MultiDerive2: public MultiDerive1 {
public:
	virtual void f() { printf("\tMultiDerive2::f\n"); }
	virtual void g() { printf("\tMultiDerive2::g\n"); }
	virtual void hm() { printf("\tMultiDerive2::hm\n"); }
	virtual void hm2() { printf("\tMultiDerive2::hm2\n"); }
};

void foreachVTable(size_t* p, size_t end) {
	typedef void(*Fun)(void);
	printf("\tEnd: %p\n", end);
	for (int i=0; ; i++) {
		Fun pFun = (Fun)*((size_t*)*p+i);
		if (size_t(pFun) == end) return;
		printf("\tAddress: %p", pFun);
		pFun();
	}
}

void foreachVTable(size_t* p, bool n) {
	printf("Try Debug on VC\n"); // TODO
}

void callf(Base1* p) {
	p->f();
	p->Base1::f();
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
	printf("Address of VTable: %p\n", *(size_t*)&b);
	printf("Address of First Function in VTable: %p\n", *(size_t*)*(size_t*)&b);
	size_t end = *((size_t*)*(size_t*)&b+3);
	printf("Label of VTable ending: %d\n\n", end);

	printf("\nVTable of Base Class:\n");
	foreachVTable((size_t*)&b, END);

	Derive1 d1;
	printf("\nVTable of Derive1 Class:\n");
	foreachVTable((size_t*)&d1, END);

	Derive2 d2;
	printf("\nVTable of Derive2 Class:\n");
#	if(MISC_ISGCC)
	foreachVTable((size_t*)&d2, END);
#	endif

	MultiDerive1 md1;
	printf("\nVTable of MultiDerive1 Class:\n");
	for (int i=0; i<3; i++) {
		printf("VTable %d:\n", i+1);
		foreachVTable((size_t*)&md1+i, MULTIEND((i+1)%3));
	}

	MultiDerive2 md2;
	printf("\nVTable of MultiDerive2 Class:\n");
#	if(MISC_ISGCC)
	for (int i=0; i<3; i++) {
		printf("VTable %d:\n", i+1);
		foreachVTable((size_t*)&md2+i, MULTIEND((i+1)%3));
	}
#	endif

	printf("\nCall function f():\n");
	callf(&md2);

	return 0;
}