//////////////////////////////////////////////////////////////////////////
// In GNU libstdc++, there are ... allocators and so on.
// __gnu_cxx::new_allocator (default)
// __gnu_cxx::malloc_allocator
// __gnu_cxx::__pool_alloc
//
// In STLPort (SGI STL), use ... predefines to change allocators. (compat.h)
// #define __STL_USE_NEWALLOC
// #define __STL_USE_MALLOC
// __node_alloc	(_alloc.h)	(default)
//
// In VC STL, only has (default) new allocator.
//////////////////////////////////////////////////////////////////////////
//#define __STL_USE_NEWALLOC
#include <misc/misc.hpp>

#include <memory>
#include <vector>
#include <map>

#if(MISC_PLATFORM == MISC_PLATFORM_UNIX)
#include <malloc.h>
#define OBSERVER malloc_stats(); mallinfo();
#else
#define OBSERVER system("pause");
#endif

template <typename T>
void fun(T& tmap)
{
	OBSERVER
	for (int i=0; i<1024*1024; i++)
		tmap[i] = float(i);
	OBSERVER
	tmap.clear();
	OBSERVER
}

int main()
{
#ifndef MISC_STL_PORT
	std::map<int, float, std::less<int>, misc::new_alloc<std::pair<int,float> >MISC_TALIAS > tmap1;
	fun(tmap1);
	printf("\n");
#endif
	std::map<int, float, std::less<int>, misc::pool_alloc<std::pair<int,float> >MISC_TALIAS > tmap2;
	fun(tmap2);
	return 0;
}