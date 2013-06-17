//////////////////////////////////////////////////////////////////////////
//
// refer to
// http://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/4178176#4178176 (What changes for C++11?)
// http://msdn.microsoft.com/en-us/library/f90831hc.aspx (Lvalues and Rvalues)
// http://msdn.microsoft.com/en-us/library/dd293668.aspx (Rvalue Reference)
// http://msdn.microsoft.com/en-us/library/ms364057(v=vs.80).aspx (NRVO)
// http://en.cppreference.com/w/cpp/language/move_constructor (Move constructors)
// <Inside The C++ Object Model>
//
// Keywords: PODs, trivial class, standard layout, trivially copyable,
// Aggregates, Rvalue, cv-qualified, NRVO (Named Return Value Optimization),
// template deduction, reference collapsing rules.
//
//////////////////////////////////////////////////////////////////////////
#include "misc/misc.hpp"
#include <cstdlib>
#include <cstddef> // for offsetof
#include <type_traits>

class POD {
public:
#if(MISC_ISGCC)
	POD() = default;
	POD(int x): m(x) {}; // Ok, because default ctor
private: // VS bug?
#endif
	int m;
};

class NonPOD : public POD {
public:
	virtual void f(); // virtual function make non-trivial ctor
	int n;
};

class Trivial : public POD {
public:
	POD x; // violate standard layout 5 and 4
protected:
	int y; // violate standard layout 1 and 4
};

class NonTrivial : public Trivial {
public:
	NonTrivial() {} // user-defined default ctor is Nontrivial ctor
};

typedef NonTrivial TriviallyCopyable; // Trivial ¡Ê TriviallyCopyable

class NonTriviallyCopyable : public TriviallyCopyable {
public:
	~NonTriviallyCopyable() {} // user-defined dtor is Nontrivial dtor
};

class StandardLayout : public POD {
public:
	StandardLayout() {printf("StandardLayout Default Ctor\n");} // violate trivial class 1
	~StandardLayout() {printf("StandardLayout Default Dtor\n");} // violate trivial class 1->2 (has a trivial destructor)
	StandardLayout(const StandardLayout&) {printf("StandardLayout Copy Ctor\n");} // non-trivial copy ctor
	StandardLayout(StandardLayout&&) {printf("StandardLayout Move Ctor\n");} // non-trivial move ctor
	StandardLayout& operator = (const StandardLayout&) { // non-trivial copy assignment
		printf("StandardLayout Copy Assignment\n");
		return *this;
	}
	StandardLayout& operator = (const StandardLayout&&) { // non-trivial move assignment
		printf("StandardLayout Move Assignment\n");
		return *this;
	}
};

#ifdef MISC_STL_VC
template <typename T>
void f(T&& a) {
	typedef typename std::remove_reference<T>::type rT;
	(rT(std::forward<T>(a)), rT(a)); // Not define in libstdc++?
}
#endif

class NonStandardLayout : public StandardLayout {
public:
	int n; // two classes have non-static members
};

#define NCOL -25
#define PRINT_IS_POD(_N) printf("%*s%*s%d\n",NCOL,#_N,NCOL,"is pod:",\
	std::is_pod<_N>::value);
#define PRINT_IS_TRIVIAL(_N) printf("%*s%*s%d\n",NCOL,#_N,NCOL,"is trivial:",\
	std::is_trivial<_N>::value);
#ifdef MISC_STL_VC // libstdc++ doesn't support std::is_trivially_copyable?
#define PRINT_IS_TRIVIALLY_COPYABLE(_N) printf("%*s%*s%d\n",NCOL,#_N,NCOL,"is trivially copyable:",\
	std::is_trivially_copyable<_N>::value);
#endif
#define PRINT_IS_STANDARD_LAYOUT(_N) printf("%*s%*s%d\n",NCOL,#_N,NCOL,"is standard layout:",\
	std::is_standard_layout<_N>::value);

int main()
{
// Default Constructor: a constructor that either has no parameters, or
// if it has parameters, all the parameters have default values.

// Trivial Default Constructor: (same with copy ctor/assignment and move ctor/assignment) 
// 1. implicitly defined
// 2. no virtual (functions and base classes)
// 3. non-static data members and direct base classes have trivial constructors

//////////////////////////////////////////////////////////////////////////
// POD (Plain Old Data) http://en.cppreference.com/w/cpp/types/is_pod
// 1. Static initialization 2. Same memory layout compiled with C and C++.
// 1 == memset() is ok; 2 == memcpy() is ok; ? http://www.stroustrup.com/C++11FAQ.html#PODs
// 1 == trivial; 2 == standard layout;
	PRINT_IS_POD(POD);
	PRINT_IS_POD(NonPOD);

	// Trivially copyable (a superset of trivial)
	// Could be safely copied with std::memcpy
	// 1. has no non-trivial copy ctor/assignment and move ctor/assignment
	// 2. has a trivial destructor
	// Trivial class http://en.cppreference.com/w/cpp/types/is_trivial
	// 1. a trivially copyable class with a trivial default constructor.
	
	PRINT_IS_TRIVIAL(Trivial);
	PRINT_IS_TRIVIAL(NonTrivial);
#ifdef MISC_STL_VC
	PRINT_IS_TRIVIALLY_COPYABLE(NonTrivial); // Trivial ¡Ê TriviallyCopyable
	PRINT_IS_TRIVIALLY_COPYABLE(TriviallyCopyable);
	PRINT_IS_TRIVIALLY_COPYABLE(NonTriviallyCopyable);
#endif
	// Standard layout http://en.cppreference.com/w/cpp/types/is_standard_layout
	// The macro offsetof can only be used with standard-layout classes
	// 1. all non-static data members must have the same access control
	// 2. no virtual (functions and base classes)
	// 3. all non-static data members and base classes must be standard layout
	// 4. only one class could has non-static data members in All base classes and itself
	// 5. the first non-static data member couldn't be base class
	PRINT_IS_STANDARD_LAYOUT(StandardLayout);
	PRINT_IS_STANDARD_LAYOUT(NonStandardLayout);

//////////////////////////////////////////////////////////////////////////
	NonPOD *nt1 = (NonPOD*)std::malloc(sizeof(NonPOD)); // vfptr undefined
	free(nt1);
	printf("\nx offsetof NonPOD: %d\n\n",offsetof(NonPOD, n)); // Warning on GCC

//////////////////////////////////////////////////////////////////////////
	printf("\t");
	StandardLayout sl1; // default ctor
	{
		StandardLayout sl2(sl1); // copy ctor
		StandardLayout sl3(static_cast<StandardLayout&&>(sl1)); // move ctor
		sl1 = sl3; // copy assignment
		sl1 = static_cast<StandardLayout&&>(sl3); // move assignment
	}
	printf("\n");
#ifdef MISC_STL_VC
	{
		f(sl1); // T == StandardLayout&, T&& collapse to StandardLayout&. Two copy ctor
		printf("\n");
		f(StandardLayout()); // T == StandardLayout, std::forward<T>(a) == StandardLayout&&, a == StandardLayout&
	}
#endif
	printf("\t");

	return 0;
}