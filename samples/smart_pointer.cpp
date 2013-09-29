//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
#include "misc/misc.hpp"

#include <memory>
#include "loki/SmartPtr.h"

using namespace std;

class A {
public:
	A():id(C++){printf("Make A%d\n",id);}
	~A(){printf("Kill A%d\n",id);}
	void printself(){printf("I'm A%d\n",id);}
	static void restart(){C=0;}
private:
	static int C;
	int id;
};
int A::C = 0;

int (*fun1)(int,int);
int*(*fun2)(void(*)(int,int),int);
int*(*fun2Arr[2])(void(*)(int,int),int);
//int (*)(int,int) (*fun3)(void(*)(int,int),int);
//int ((*fun3)(void(*)(int,int),int))(int,int);
  int ( *fun3 (void(*)(int,int),int))(int,int);

int main()
{
// unique_ptr
printf("unique_ptr\n");
	{
		// case 1: exception
		try {
			A* rp = new A;
			unique_ptr<A> p(new A);
		} catch(...){}
		// case 2: transfer ownership
		unique_ptr<A> p1(new A);
		p1 = unique_ptr<A>(new A);
		{
			unique_ptr<A> p2(move(p1));
		}
		printf("after kill\n");
	}
// shared_ptr
printf("\nshared_ptr\n");
	{
		A::restart();
		shared_ptr<A> sp(new A);
		vector<shared_ptr<A>> arr(4,sp);
		for_each(arr.begin(), arr.end(), [&](shared_ptr<A>&p){
			p->printself();
		});
	}
// weak_ptr
printf("\nweak_ptr\n");
	{
		A::restart();
		weak_ptr<A> wp;
		{
			auto p = shared_ptr<A>(new A);
			wp = p;
			if(auto p = wp.lock())
				p->printself();
		}
		if(auto p = wp.lock())
			p->printself();
		else
			printf("empty\n");
	}
	return 0;
}