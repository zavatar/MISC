//////////////////////////////////////////////////////////////////////////
//
// refer to http://exceptionsafecode.com/
// http://4thmouse.com/mystuff/articles/UsingExceptionsEffectively.html#N100A2
//
// Separation of Error Detection from Error Handling
//
// Guideline:
// 1. Throw by value, Catch by reference
// 2. Do not use dynamic exception specifications
// 3. RAII, Responsibility Acquisition Is Initialization
//
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"
#include <stdexcept>
#include <exception>
#include <string>
#include <fstream>

#include <future>

class A {
public:
	A() {printf("A ctor\n");}
	~A() {printf("A dtor\n");}
	virtual void who() {printf("I'm A\n");}
};
class B: public A{
public:
	virtual void who() {printf("I'm B\n");}
};

void fun1()
{
	throw B(); // Throw by value
}

void fun2()
{
	A a1; // will be destructed
	fun1(); // throw cross fun2 to main
	A a2; // will never execute
}

// Function Try Blocks

// C++11, Moving exceptions between threads
int tfun()
{
	throw 2;
	return 1;
}

void run1()
{
	std::future<int> f = std::async(std::launch::async,tfun);
	std::exception_ptr eptr(nullptr);
	try {
		f.get();
	} catch (...) {
		eptr = std::current_exception();
	}
	if (eptr != std::exception_ptr())
		std::rethrow_exception(eptr);
}

// C++11, Nesting exceptions
#ifdef MISC_STL_LIBSTDCXX
// prints the explanatory string of an exception. If the exception is nested,
// recurses to print the explanatory of the exception it holds
void print_exception(const std::exception& e, int level =  0)
{
	std::cerr << std::string(level, ' ') << "exception: " << e.what() << '\n';
	try {
		std::rethrow_if_nested(e);
	} catch(const std::exception& e) {
		print_exception(e, level+1);
	} catch(...) {}
}
// sample function that catches an exception and wraps it in a nested exception
void open_file(const std::string& s)
{
	try {
		std::ifstream file(s);
		file.exceptions(std::ios_base::failbit);
	} catch(...) {
		std::throw_with_nested( std::runtime_error("Couldn't open " + s) );
	}
}
void run2()
{
    try {
        open_file("nonexistent.file");
    } catch(...) {
        std::throw_with_nested( std::runtime_error("run() failed") );
    }
}
#endif
int main()
{
	try {
		fun2();
	} catch (A& e) { // Catch by reference
		e.who();
	}

	try {
		run1();
	} catch (int i) {
		printf("run1: %d\n",i);
	}

#ifdef MISC_STL_LIBSTDCXX
	try {
		run2();
	} catch (const std::exception& e) {
		print_exception(e);
	}

	static_assert(noexcept(2 + 3), "");
	static_assert(not noexcept(throw 23), "");
#endif
	
	return 0;
}