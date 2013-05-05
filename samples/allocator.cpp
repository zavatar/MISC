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
#include <map>

#if(MISC_COMPILER & MISC_COMPILER_GCC)
// For GNU libstdc++, try pool alloc.
#include <ext/pool_allocator.h>
#define ALLOCATOR(_Kty, _Ty) __gnu_cxx::__pool_alloc< std::pair<_Kty, _Ty> >
#else
// For STLPort or VC STL, use the default.
#define ALLOCATOR(_Kty, _Ty) std::allocator< std::pair<_Kty, _Ty> >
#endif

#if(MISC_PLATFORM & MISC_PLATFORM_UNIX)
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
	std::map<int, float, std::less<int>, ALLOCATOR(int, float)> tmap;
	fun(tmap);

	return 0;
}