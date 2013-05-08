//////////////////////////////////////////////////////////////////////////
//
// Refer to
// http://www.cnblogs.com/neoragex2002/archive/2007/11/01/VC8_Object_Layout_Secret.html
// http://www.cppblog.com/chemz/archive/2007/06/12/26135.html
//
// Using /d1reportSingleClassLayoutDiamondSub2 and /d1reportAllClassLayout
// to see the layout of class DiamondSub2 in VC
//
//////////////////////////////////////////////////////////////////////////
#include "misc/misc.hpp"

// Diamond Inheritance Hierarchy
class Base1 {
public:
	virtual void f() { printf("\tBase1::f\n"); }
	virtual void g() { printf("\tBase1::g\n"); }
	virtual void l() { printf("\tBase1::l\n"); }
	virtual void r() { printf("\tBase1::r\n"); }
	int m_val[2];
};

class DeriveL1: Base1 {};
class DeriveR1: Base1 {};
class Diamond1: DeriveL1, DeriveR1 {};
class DiamondSub1: Diamond1 {};

class DeriveL2: public virtual Base1 {
public:
	virtual void l() { printf("\tDeriveL2::l\n"); }
	int m_val[2];
};
class DeriveR2: public virtual Base1 {
public:
	virtual void r() { printf("\tDeriveR2::r\n"); }
	int m_val[2];
};
class Diamond2: public DeriveL2, public DeriveR2 {
public:
	virtual void g() { printf("\tDiamond2::g\n"); }
	int m_val;
};
class DiamondSub2: public Diamond2 {
public:
	int m_val;
};

#define EVAL(E) printf("\t" #E " = %d\n", (E) );
#define INCLASS(d,E,V) printf("\t"#E"(%d)\tAddress: %d-%d+["#V"]\t",\
	sizeof(E), (size_t)(E*)&d - (size_t)&d,\
	sizeof(E)-sizeof(V) + ((size_t)(E*)&d - (size_t)&d));

int main( int argc, char *argv[] )
{
	printf("Normal Diamond Inheritance Hierarchy:\n");
	EVAL(sizeof(Base1));
	EVAL(sizeof(DeriveL1));
	EVAL(sizeof(DeriveR1));
	EVAL(sizeof(Diamond1));
	EVAL(sizeof(DiamondSub1));

	printf("\nVirtual Diamond Inheritance Hierarchy:\n");
	DiamondSub2 ds2;
	printf("\tMemory of DiamondSub2 (%d):\n", sizeof(DiamondSub2));
	INCLASS(ds2, Diamond2, Base1);
	printf("[DeriveL2][DeriveR2]\n");
	INCLASS(ds2, DeriveL2, Base1);
	printf("[tbtable:%d][int2]\n",*((size_t*)*(size_t*)(DeriveL2*)&ds2+1));
	INCLASS(ds2, DeriveR2, Base1);
	printf("[tbtable:%d][int2]\n",*((size_t*)*(size_t*)(DeriveR2*)&ds2+1));
	printf("\tBase1(%d)\tAddress: %d-%d\t\n",
		sizeof(Base1), (size_t)(Base1*)&ds2 - (size_t)&ds2, sizeof(ds2));

    return 0; 
}