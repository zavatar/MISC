#ifndef misc_string
#define misc_string

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// http://www.geeksforgeeks.org/tag/pattern-searching/
//**Data Compression Techniques
// 1. Huffman coding
// 2. LZ77
//
//**String Processing Algorithms
//  58093 String Processing Algorithms
//  http://www.cs.helsinki.fi/en/courses/58093/2012/s/k/1
// 1. Sets of strings (insert, delete, find, prefix query, LCP query)
//    Search trees, string sorting, binary search
//    1. trie, compact trie, ternary trie
//    2. string quick sort, LSD radix sort, MSD radix sort(very fast)
//    3. merge sort using the lcp comparison technique
//    4. binary search, LLCP+RLCP
// 2. Exact string matching
//    1. KMP, Shift-And, Horspool(very fast), BNDM(optimal)
//    2. multiple exact string matching: Rabin-Karp, Aho-Corasick
// 3. Approximate string matching(Edit distance/ Levenshtein distance)
//    1. DP(speed up using Ukkonen's Cut-off Heuristic), O(kn)
//    2.*Myers' Bitparallel Algorithm, Baeza-Yates-Perleberg Filtering Algorithm
// 4. Suffix tree and array (search data structures)
//    1. Suffix tree is a compact trie, constructed within O(n)
//    2. O(n) preprocessing of suffix tree indicate O(1) LCA/LCP of any two suffixes
//    3. Suffix array is a ordered array
//    4. LCP array, using O(n) preprocessed RMQ indicate O(1) of any two suffixes
//    5. BWT, Prefix doubling O(nlgn), SAIS O(n), DC3
//
//////////////////////////////////////////////////////////////////////////

	// the longest proper prefix
	template <typename T>
	void LPS(T* p, int* lps, int m);

	template <typename T, typename Fun>
	void KMPSearch(T* s, int n, T* p, int m, Fun fn);

	bool ismatch(const char* s, const char* p, int n);

	template <typename Fun>
	void RKSearch(const char* s, int n, const char* p, int m, Fun fn);

	// if freq is sorted, this can be done within O(n) time
	// http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding-set-2/
	template <typename T, typename U>
	void Huffman(std::vector<std::pair<T, U>> &freq,
		std::vector<std::string> &codes);

	void MSD_radix_sort(std::vector<std::string> &strs);

	bool binary_search_str(const std::vector<std::string> &strs, 
		const std::string &patstr, int &id);



} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "string.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_string
