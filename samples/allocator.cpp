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

template <int N>
struct Byte {
	char _b[N];
};

int main()
{
	misc::pool_alloc<Byte<1>> byte1;
	misc::pool_alloc<Byte<8>> byte8;
	misc::pool_alloc<Byte<33>> byte33;
	misc::pool_alloc<Byte<128>> byte128;
	std::vector<Byte<8>*> pbyte8;
	// malloc 40*RUP(1)=40*8 bytes, 1*8 return, 19*8 add to flist[0]
	auto p1 = byte1.allocate(1);
	// left 20*8 in chunk
	for (int i=0; i<19; i++) // use out of flist[0]
		pbyte8.push_back(byte8.allocate(1));
	// add one node to flist[15], left 160-128=32
	auto p128 = byte128.allocate(1);
	// add left 32 to flist[3] and malloc 40*RUP(33)+N=40*40+N bytes
	// 1*40 return, 19*40 add to flist[4], left 20*40+N in chunk
	// N = RUP(_S_heap_size >> 4)
	auto p33 = byte33.allocate(1);

	// deallocate
	byte1.deallocate(p1, 1);
	for (auto p : pbyte8)
		byte8.deallocate(p, 1);
	byte128.deallocate(p128, 1);
	byte33.deallocate(p33, 1);

#ifndef MISC_STL_PORT
	std::map<int, float, std::less<int>, 
		misc::new_alloc<std::pair<int,float> >MISC_TALIAS > tmap1;
	fun(tmap1);
	printf("\n");
#endif
	std::map<int, float, std::less<int>, 
		misc::pool_alloc<std::pair<int,float> >MISC_TALIAS > tmap2;
	fun(tmap2);
	return 0;
}