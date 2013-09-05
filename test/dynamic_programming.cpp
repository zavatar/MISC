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

TEST(Rod_Cutting_Test, SpecialCase)
{ // from CLRS
	float p[11] = {0,1,5,8,9,10,17,17,20,24,30};
	int ln[2] = {1,6};
	int k=0;
	float r = misc::rod_cutting(p, 7, [&ln,&k](int l){
		EXPECT_EQ(l, ln[k++]);
	});
	EXPECT_EQ(r, 18);
}

TEST(LIS_Test, SpecialCase)
{ // http://en.wikipedia.org/wiki/Longest_increasing_subsequence
	int x[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	int r0[6] = {0, 2, 6, 9, 11, 15};

	int k=6;
	int l0 = misc::fastLIS(x, 16, [&r0,&k](int a){
		EXPECT_EQ(a, r0[--k]);
	});
	EXPECT_EQ(l0, 6);

	int r1[6] = {0, 4, 6, 9, 13, 15};
	k = 6;
	int l1 = misc::LIS(x, 16, [&r1,&k](int a){
		EXPECT_EQ(a, r1[--k]);
	});
	EXPECT_EQ(l1, 6);
}

TEST(LCS_Test, SpecialCase)
{ // http://en.wikipedia.org/wiki/Longest_common_subsequence_problem
	char x[5] = {'A','G','C','A','T'};
	char y[3] = {'G','A','C'};
	int l = misc::LCS(x, 5, y, 3, [&x,&y](int i, int j){
		EXPECT_EQ(x[i], y[j]);
	});
	EXPECT_EQ(l, 2);

	char x1[] = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"; // 29
	char y1[] = "GTCGTTCGGAATGCCGTTGCTCTGTAAA"; // 28
	char z1[] = "GTCGTCGGAAGCCGGCCGAA"; // 20
	int k = 20;
	int l1 = misc::LCS(x1, 29, y1, 28, [&x1,&y1,&z1,&k](int i, int j){
		EXPECT_EQ(x1[i], y1[j]);
		EXPECT_EQ(x1[i], z1[--k]);
	});
	EXPECT_EQ(l1, 20);
}

TEST(edit_distance_Test, SpecialCase)
{
	char x[5] = {'A','G','C','A','T'};
	char y[3] = {'G','A','C'};
	int e = misc::edit_distance(x, 5, y, 3, [&x,&y](int i, int j){
		//printf("%c,%c\n", x[i], y[j]);
	});
	EXPECT_EQ(e, 3);

	char x1[] = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"; // 29
	char y1[] = "GTCGTTCGGAATGCCGTTGCTCTGTAAA"; // 28
	int e1 = misc::LCS(x1, 29, y1, 28, [&x1,&y1](int i, int j){
		//printf("%c,%c\n", x1[i], y1[j]);
	});
	EXPECT_EQ(e1, 20);
}