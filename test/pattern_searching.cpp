#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(KMPSearch_Test, Standard)
{
	char txt[] = "AABAACAADAABAAABAA";
	char pat[] = "AABA";
	std::vector<int> r;
	r.push_back(13);
	r.push_back(9);
	r.push_back(0);
	misc::KMPSearch(txt, 18, pat, 4, [&](int idx){
		EXPECT_EQ(idx, r.back());
		r.pop_back();
	});
}