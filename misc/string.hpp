#ifndef misc_string
#define misc_string

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// http://www.geeksforgeeks.org/tag/pattern-searching/
// 1. KMP
// 2. Rabin-Karp
// 3. Trie, Suffix tree
// 4. Suffix array, Prefix doubling, Inducing sort, LCP array
// 5. Huffman coding
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

	template <typename T, typename U>
	void Huffman(std::vector<std::pair<T, U>> &freq,
		std::vector<std::string> &codes);

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "string.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_string
