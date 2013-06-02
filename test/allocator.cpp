#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(allocator_test, standard)
{
	// default constructor
	misc::pool_alloc<int>MISC_TALIAS alloc1;
	// copy constructor
	misc::pool_alloc<int>MISC_TALIAS alloc2(alloc1);
	// template constructor
	misc::pool_alloc<double>MISC_TALIAS alloc3(alloc2);
	// operator ==
	EXPECT_TRUE(alloc1 == alloc2);
	// operator !=
#ifdef MISC_STL_LIBSTDCXX
	EXPECT_FALSE(alloc1 != alloc2); // TODO: why not support different types?
#elif defined(MISC_STL_VC)
	EXPECT_FALSE(alloc1 != alloc3);
#endif
}