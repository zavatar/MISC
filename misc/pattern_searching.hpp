#ifndef misc_pattern_searching
#define misc_pattern_searching

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// http://www.geeksforgeeks.org/tag/pattern-searching/
// 1. KMP
// 2. Rabin-Karp
// 3. Trie, Suffix tree
// 4. Suffix array, Prefix doubling, Inducing sort, LCP array
//
//////////////////////////////////////////////////////////////////////////

	// the longest proper prefix
	template <typename T>
	void LPS(T* p, int* lps, int m);

	template <typename T, typename Fun>
	void KMPSearch(T* s, int n, T* p, int m, Fun fn);

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "pattern_searching.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_pattern_searching
