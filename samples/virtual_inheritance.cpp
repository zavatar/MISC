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
#include "misc/setup.hpp"

#if(MISC_ISVC)
// Warning C4250: http://msdn.microsoft.com/en-us/library/6b3sy7ae(v=vs.80).aspx
#pragma warning( disable : 4250 )
#endif

// Diamond Inheritance Hierarchy
class Base1 {
public:
	virtual void f() {}
	virtual void g() {}
	virtual void l() {}
	virtual void r() {}
	int m_val[2];
};

class DeriveL1: public Base1 {
public:
	virtual void l() {}
	int m_val[2];
};
class DeriveR1: public Base1 {
public:
	virtual void r() {}
	int m_val[2];
};
class Diamond1: public DeriveL1, public DeriveR1 {
public:
	virtual void g() {}
	int m_val;
};
class DiamondSub1: public Diamond1 {
public:
	int m_val;
};

class DeriveL2: public virtual Base1 {
public:
	virtual void l() {}
	int m_val[2];
};
class DeriveR2: public virtual Base1 {
public:
	virtual void r() {}
	int m_val[2];
};
class Diamond2: public DeriveL2, public DeriveR2 {
public:
	virtual void g() {}
	int m_val;
};
class DiamondSub2: public Diamond2 {
public:
	int m_val;
};

int main( int argc, char *argv[] )
{
#	if(MISC_ISGCC)
#	pragma message("Try VS2012 to see the layout of classes\n")
#	elif(MISC_ISVC)
#	pragma message("Build this project and see the layout of classes in Output\n")
#	endif
    return 0; 
}