#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(allocator_test, construct)
{
	misc::pool_alloc<int>MISC_TALIAS().allocate(1);
	EXPECT_TRUE(true);
}