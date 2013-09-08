#ifndef misc_sorting
#define misc_sorting

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// Sort:
// STL(algorithm): sort, stable_sort, partial_sort, partial_sort_copy,
//                 is_sorted, is_sorted_until, nth_element.
// Merge:
// STL(algorithm): merge, inplace_merge, includes, set_union, 
//                 set_intersection, set_difference, set_symmetric_difference
// Heap:
// STL(algorithm): is_heap, is_heap_until(c11), make_heap, push_heap,
//                 pop_heap, sort_heap.
// priority_queue:
// STL(queue): top, push, pop, INCREASE(CLRS).
//
// HeapSort --> ¢Ù make heap O(n)	--> n/2 * heapify
//		   ---> ¢Ú sort heap O(nlgn)	-->  n  * heapify
// (push, pop, INCREASE) === (INCREASE, heapify, INCREASE) == (INCREASE)O(lgn)
// non-recursive heapify --> ¢Ù lgn * goto the larger child
//						---> ¢Ú INCREASE(One Key Operation)
// Partitions:
// STL(algorithm): is_partitioned, partition, stable_partition, 
//                 partition_copy, partition_point
// Binary Search:
// STL(algorithm): binary_search, equal_range, lower_bound/upper_bound.
//
// Fibonacci Heap: 
// OP   | List |Sorted| BBST      | heap |FiHeap
// push | O(1) | O(n) |O(lgn)	  |O(lgn)| O(1)
// max  | O(n) | O(1) |O(lgn)	  | O(1) | O(1)
// pop  | O(n) | O(1) |O(lgn)	  |O(lgn)|O(lgn)
// inc  | O(1) | O(n) |O(lgn)	  |O(lgn)| O(1)
// merge| O(1) |O(m+n)|O(mlg(n+m))|O(n+m)| O(1)
//
// http://www.boost.org/doc/libs/1_54_0/libs/disjoint_sets/disjoint_sets.html
// Disjoint Sets: Find, Union, Make_Set
//  1. Linked lists, O(n) Find or Union
//  2. Forests, (union by rank and path compression), O(amortized const) Find and Union
//
//////////////////////////////////////////////////////////////////////////

	template <typename T>
	void insertion_sort_n(T *a, int n);

	// http://en.wikipedia.org/wiki/Shell_sort
	template <typename T>
	void shell_sort_n(T *a, int n);

	// Mergesort
	template <typename T>
	void merge_sort_n(T *a, int n);

	// Heapsort
	template <typename T>
	void heap_sort_n(T *a, int n);
	template <typename T>
	void heap_sort_n_1(T *a, int n);

	// Quicksort
	template <typename T>
	void quicksort_n(T *a, int n);

	// Introsort in STL (median-of-3 quicksort & heapsort)

	// Timsort using in Python
	// http://en.wikipedia.org/wiki/Timsort

	// Bitonic sorter in network (parallel algorithm)
	// http://en.wikipedia.org/wiki/Bitonic_sorter

	// Binary Search
	template <typename T>
	bool binary_search_n(T *a, int n, T val);

	// Medians and Order Statistics
	template <typename T>
	T nth_selection_n(T *a, int n, int nth);

	// Counting sort

	// Radix sort

	// Induce sort (suffix array) [Prefix Doubling]


} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "sorting.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_sorting
