//////////////////////////////////////////////////////////////////////////
//
// Refer to
// http://www.phpcompiler.org/articles/virtualinheritance.html#Downcasting
// http://www.cnblogs.com/neoragex2002/archive/2007/11/01/VC8_Object_Layout_Secret.html
// http://www.cppblog.com/chemz/archive/2007/06/12/26135.html
// 
// Using /d1reportSingleClassLayoutDiamondSub2 and /d1reportAllClassLayout
// to see the layout of class DiamondSub2 in VC
//
// Or Debug using WinDbg on VS2012
// http://blogs.msdn.com/b/mariohewardt/archive/2012/06/05/visual-studio-2012-and-windbg-integration.aspx
//
//////////////////////////////////////////////////////////////////////////
#include "misc/misc.hpp"

#if(MISC_ISVC)
// Warning C4250: http://msdn.microsoft.com/en-us/library/6b3sy7ae(v=vs.80).aspx
#pragma warning( disable : 4250 )
#endif

// Diamond Inheritance Hierarchy
class Base1 {
public:
	virtual void f() { printf("\tBase1::f\n"); }
	virtual void g() { printf("\tBase1::g\n"); }
	virtual void l() { printf("\tBase1::l\n"); }
	virtual void r() { printf("\tBase1::r\n"); }
	virtual void g2(){ printf("\tBase1::g2\n");}
	int m_val[2];
};

class DeriveL1: public Base1 {
public:
	virtual void l() { printf("\tDeriveL1::l\n"); }
	int m_val[2];
};
class DeriveR1: public Base1 {
public:
	virtual void r() { printf("\tDeriveR1::r\n"); }
	int m_val[2];
};
class Diamond1: public DeriveL1, public DeriveR1 {
public:
	virtual void g() { printf("\tDiamond1::g\n"); }
	int m_val;
};
class DiamondSub1: public Diamond1 {
public:
	int m_val;
};

class DeriveL2: public virtual Base1 {
public:
	virtual void l() { printf("\tDeriveL2::l\n"); }
	virtual void g2(){ printf("\tDeriveL2::g2\n"); }
	int m_val[2];
};
class DeriveR2: public virtual Base1 {
public:
	virtual void r() { printf("\tDeriveR2::r\n"); }
	virtual void g2(){ printf("\tDeriveR2::g2\n");}
	int m_val[2];
};
class Diamond2: public DeriveL2, public DeriveR2 {
public:
	virtual void g() { printf("\tDiamond2::g\n"); }
	virtual void g2(){ printf("\tDiamond2::g2\n");}// if commented, g2 will be ambiguous
	int m_val;
};
class DiamondSub2: public Diamond2 {
public:
	int m_val;
};

#	if(MISC_ISGCC)
#	pragma message("Try VS2012 to see the layout of classes\n")
#	elif(MISC_ISVC)
#	pragma message("Build this project and see the layout of classes in Output\n")
#	endif

int main( int argc, char *argv[] )
{
	printf("Compare directly invoke\n");
	DiamondSub1 ds1;
	DiamondSub2 ds2;
	ds1.DeriveL1::f(); ds1.DeriveR1::f(); // ds1.f(); ambiguous
	ds2.f();
	ds1.DeriveL1::l(); ds1.DeriveR1::l();
	ds2.l(); ds2.r(); // ds1.l(); ds1.r(); ambiguous
	ds1.g(); ds2.g();

	printf("Compare virtually invoke\n");
	Base1* b1 = (DeriveL1*)&ds1; // &ds1 ambiguous, (DeriveL1*) help choose inheritance path
	Base1* b2 = &ds2;
	b1->f(); b2->f();
	b1->g(); b2->g();
	b1->l(); b2->l();
	b1->r(); b2->r();

    return 0; 
}