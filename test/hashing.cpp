#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(FNV_1a_Test, Standard)
{
	srand( (unsigned int)time(NULL) );
	int val = rand();
	EXPECT_EQ(misc::FNV_1a<int>()(val), misc::FNV_1a<int>()(val));

	bool tmp[4] = {1,1,1,0};
	EXPECT_EQ(misc::FNV_1a<bool>()(tmp[0]), misc::FNV_1a<bool>()(tmp[2]));
	EXPECT_EQ(misc::FNV_1a<bool>()(false), misc::FNV_1a<bool>()(false));

	// bool*
	EXPECT_NE(misc::FNV_1a<bool*>()(&tmp[0]), misc::FNV_1a<bool*>()(&tmp[1]));

	// float
	EXPECT_EQ(misc::FNV_1a<bool>()(.0f), misc::FNV_1a<bool>()(-.0f));

	// std::string
	std::string str = "Stand back! I've got jimmies!";
	EXPECT_EQ(misc::FNV_1a<std::string>()(str), misc::FNV_1a<std::string>()(str));

	// Paul_Larson_hash
	EXPECT_EQ(misc::Paul_Larson_hash(str.c_str()),
		misc::Paul_Larson_hash(str.c_str()));

	// Rabin_Karp
	misc::rabin_karp rk(str.c_str(), str.size());
	val = rk.hash();
	EXPECT_NE(val, rk.rehash('A'));
}