#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(Pattern_Search_Test, Standard)
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

	r.push_back(13);
	r.push_back(9);
	r.push_back(0);
	misc::RKSearch(txt, 18, pat, 4, [&](int idx){
		EXPECT_EQ(idx, r.back());
		r.pop_back();
	});
}

TEST(Huffman_Test, Standard)
{
	// case from http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
	std::vector<std::pair<std::string, int>> freq;
	freq.emplace_back("a", 5);
	freq.emplace_back("b", 9);
	freq.emplace_back("c", 12);
	freq.emplace_back("d", 13);
	freq.emplace_back("e", 16);
	freq.emplace_back("f", 45);

	std::vector<std::string> codes;
	std::vector<std::string> expcodes;
	expcodes.push_back("1100");
	expcodes.push_back("1101");
	expcodes.push_back("100");
	expcodes.push_back("101");
	expcodes.push_back("111");
	expcodes.push_back("0");
	misc::Huffman(freq, codes);
	EXPECT_EQ(codes, expcodes);
}