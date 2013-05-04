#include <misc/misc.hpp>

#include <memory>
#include <map>

#if((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC)
#include <malloc.h>
#include <ext/pool_allocator.h>
#endif

//#define NEW_ALLOC

int main()
{
#	if(((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC) && !defined(__MINGW32__))
	malloc_stats();
#	endif
	std::map<int, float, std::less<int>
#	if(((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC) && !defined(NEW_ALLOC))
		,__gnu_cxx::__pool_alloc<std::pair<int, float> >
#	endif
	> tmap;

	for (int i=0; i<1024*1024; i++)
		tmap[i] = float(i);

#	if(((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC) && !defined(__MINGW32__))
	malloc_stats();
#	else
	system("pause");
#	endif

	tmap.clear();

#	if(((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC) && !defined(__MINGW32__))
	malloc_stats();
#	else
	system("pause");
#	endif

	return 0;
}