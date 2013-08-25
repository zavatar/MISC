#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(sorting_test, standard)
{
	const int N = 97;
	int a[N];
	int i=0;
	std::for_each(a, a+N, [&i](int &a){ a=i++; });
	srand( (unsigned int)time(NULL) );

	for (int k=0; k<100; k++) 
	{
		// insertion sort
		std::random_shuffle(a, a+N);
		misc::insertion_sort_n(a, N);
		EXPECT_TRUE(std::is_sorted(a, a+N));

		// shell sort
		std::random_shuffle(a, a+N);
		misc::shell_sort_n(a, N);
		EXPECT_TRUE(std::is_sorted(a, a+N));

		// merge sort
		std::random_shuffle(a, a+N);
		misc::merge_sort_n(a, N);
		EXPECT_TRUE(std::is_sorted(a, a+N));

		// heap sort
		std::random_shuffle(a, a+N);
		misc::heap_sort_n(a, N);
		EXPECT_TRUE(std::is_sorted(a, a+N));
		std::random_shuffle(a, a+N);
		misc::heap_sort_n_1(a, N);
		EXPECT_TRUE(std::is_sorted(a, a+N));

		// quick sort
		std::random_shuffle(a, a+N);
		misc::quicksort_n(a, N);
		EXPECT_TRUE(std::is_sorted(a, a+N));

		// binary search (sorted)
		EXPECT_TRUE(misc::binary_search_n(a, N, a[rand()%N]));
		EXPECT_FALSE(misc::binary_search_n(a, N, N));

		// order statistics
		std::random_shuffle(a, a+N);
		int nth = rand()%N;
		EXPECT_EQ(misc::nth_selection_n(a, N, nth), nth);
	}
	
}