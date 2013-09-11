//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////

#include <misc/misc.hpp>

#include <loki/Typelist.h>
#include <loki/HierarchyGenerators.h>

namespace TlPrivate {
#if MISC_ISGCC
	// C++11, need compiling with g++ -std=c++0x
	template<typename T>  
	void output(T&& value)  
	{  
		std::cout << value << std::endl;
	}
	template<typename First, typename... Rest>  
	void output(First&& first, Rest&&... rest)  
	{  
		std::cout << first << ",";
		output(std::forward<Rest>(rest)...);
	}
	template<typename T>  
	T sum(T&& value)  
	{  
		return value;  
	}  
	template<typename First, typename Second, typename... Rest>  
	First sum(First&& first, Second&& second, Rest&&... rest)  
	{  
		return sum(first + second, std::forward<Rest>(rest)...);  
	}
#endif
	template <class T> 
	struct Holder 
	{
		//#pragma message("Holder")
		T value_;
	}; 

	class BBase {};
	class Window {};
	class Button {};
	class ScrollBar {};

	template <class T, class Base> 
	class EventHandler : public Base 
	{ 
	public: 
		virtual void OnEvent(T& obj, int eventId); 
	};

}

int main()
{
#if MISC_ISGCC
	// C++11, need compiling with g++ -std=c++0x
	double d = 2.3;  
	TlPrivate::output(42,"hello",d,'a');  
	TlPrivate::output("hello",d,'a');  
	TlPrivate::output(d,'a');  
	TlPrivate::output('a');  
	TlPrivate::output(TlPrivate::sum(1), TlPrivate::sum(1, 2), TlPrivate::sum(1, 2, 3));
#endif
	typedef Loki::TL::MakeTypelist<bool, char, int, float, double>::Result MyTypelist;

	typedef Loki::TL::Reverse<MyTypelist>::Result MyTypelistReversed;

	typedef Loki::TL::Append<MyTypelist, MyTypelistReversed>::Result MyTypelistSymmetrical;

	std::cout << Loki::TL::Length<MyTypelistReversed>::value << std::endl;

	std::cout << Loki::TL::IndexOf<MyTypelistSymmetrical, float>::value << std::endl <<
		typeid(Loki::TL::TypeAt<MyTypelistSymmetrical, 6>::Result).name() << std::endl;

	// 3.13.1 Generating Scattered Hierarchies
	typedef Loki::GenScatterHierarchy
		<
		Loki::TL::MakeTypelist
		<
		bool,
		char,
		int
		>::Result,
		TlPrivate::Holder
		>
		MyScatterHierarchy;
	// 3*4
	std::cout << sizeof(MyScatterHierarchy) << std::endl;

	// Deal with ambiguity using NoDuplicates
	Loki::GenScatterHierarchy
		<
		Loki::TL::NoDuplicates
		<
		Loki::TL::MakeTypelist
		<
		int,
		int,
		int
		>::Result
		>::Result,
		TlPrivate::Holder
		> ma0;
	Loki::Field<int>(ma0);

	Loki::Tuple<Loki::TL::NoDuplicates<MyTypelistSymmetrical>::Result> ma1;
	Loki::Field<int>(ma1);

	// 3.13.2 Generating Tuples
	typedef Loki::Tuple<MyTypelist> MyTuple;
	MyTuple mt;
	Loki::Field<0>(mt) = true;
	Loki::Field<1>(mt) = 'A';
	Loki::Field<2>(mt) = 256;
	Loki::Field<3>(mt) = 1.f;


	// 3.13.3 Generating Linear Hierarchies
	typedef Loki::GenLinearHierarchy
		< 
		Loki::TL::MakeTypelist
		<
		TlPrivate::Window,
		TlPrivate::Button,
		TlPrivate::ScrollBar
		>::Result,
		TlPrivate::EventHandler,
		TlPrivate::BBase
		> 
		MyEventHandler;
	// 1*4
	std::cout << sizeof(MyEventHandler) << std::endl;

	return 0;
}