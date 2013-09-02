#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(Fibonacci_Test, Standard)
{
	EXPECT_EQ(misc::fibonacci_n(0), 0);
	EXPECT_EQ(misc::fibonacci_n(1), 1);
	EXPECT_EQ(misc::fibonacci_n(2), 1);
	EXPECT_EQ(misc::fibonacci_n(3), 2);
	EXPECT_EQ(misc::fibonacci_n(20), 6765);
}

TEST(Rod_Cutting_Test, CLRS)
{
	float p[11] = {0,1,5,8,9,10,17,17,20,24,30};
	float rt[11] = {0,1,5,8,10,13,17,18,22,25,30};
	int st[11] = {0,1,2,3,2,2,6,1,2,3,10};
	std::vector<int> ln;
	misc::rod_cutting(p, 7, [&ln](int l){
		ln.push_back(l);
	});
	EXPECT_EQ(misc::rod_cutting(p, 7), rt[7]);

	std::unique_ptr<float[]> r(new float[11]);
	std::unique_ptr<int[]> s(new int[11]);
	misc::rod_cutting_bottomup(r.get(), s.get(), p, 10);
	for (int i=0; i<11; i++) {
		EXPECT_EQ(r[i], rt[i]);
		EXPECT_EQ(s[i], st[i]);
	}
}