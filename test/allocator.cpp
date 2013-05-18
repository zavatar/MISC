#include <misc/misc.hpp>

int main()
{
	int Error(0);
	misc::pool_alloc<int>MISC_TALIAS().allocate(1);
	return Error;
}