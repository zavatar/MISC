#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(Rod_Cutting_Test, CLRS)
{
	float p[10] = {1,5,8,9,10,17,17,20,24,30};
	float r[11] = {0,1,5,8,10,13,17,18,22,25,30};
	std::vector<int> ln;
	misc::rod_cutting(p, 7, [&ln](int l){
		ln.push_back(l);
	});
	EXPECT_EQ(misc::rod_cutting(p, 7), r[7]);

	std::unique_ptr<float[]> rp(new float[10]);
	std::unique_ptr<int[]> s(new int[10]);
	misc::rod_cutting_bottomup(rp.get(), s.get(), p, 10);
	for (int i=0; i<10; i++)
		EXPECT_EQ(rp[i], r[i+1]);
}