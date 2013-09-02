#ifndef misc_dynamic_programming
#define misc_dynamic_programming

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// Dynamic Programming
//  1. Fibonacci Numbers
//  2. Rod Cutting
//  3. Matrix-chain Multiplication
//  4. Longest Common Subsequence (LCS) <--> Longest Increasing Subsequence (LIS)
//  5. Optimal BST
//  6. Text Justification
//  7. All Shortest Path
//  8. Black Jack
//  9. String Subproblems
// 10. Parenthesization
// 11. Edit Distance
// 12. Knapsack
// 13. Seam Carving
// 14. Piano/Guitar Fingering
// 15. Tetris Training
// 16. Super Mario Bros
//
// Greedy Programming
//  1. Minimum Spanning Trees
//  2. Dijkstra Shortest Path (BFS)
//  3. Bellman-Ford Shortest Path (supporting negative weight)
//
//////////////////////////////////////////////////////////////////////////

	// 1. Fibonacci Numbers
	// O(n) (Could be O(lgn), using Matrix Form)
	inline unsigned int fibonacci_n(int n);

	// 2. Rod Cutting, r[i] = max(p[j]+r[i-j]), j = [1,i]
	template <typename T> // O(n^2)
	void rod_cutting_bottomup(T *r, int *s, T *p, int n);

	template <typename T, typename Fun> // O(n^2)+O(n)
	T rod_cutting(T *p, int n, Fun fn);

	template <typename T> // O(n^2)
	T rod_cutting(T *p, int n);

	// 4. Longest Common Subsequence (LCS)
	// DP, O(mn) time, O(mn)
	// http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/
	// LCS(Xm,Yn) = LCS(Xm-1,Yn-1) + 1, X[m-1]==Y[n-1]
	//			  = max(LCS(Xm-1,Yn), LCS(Xm,Yn-1)), X[m-1]!=Y[n-1]
	template <typename T>
	int LCS(T *x, int m, T *y, int n);

	// 4.<--> Longest Increasing Subsequence (LIS)
	// DP, O(n^2) time
	// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
	// Find all LIS ending with i (lis[i]), i = [0,n-1], then return the biggest
	// lis[i] = 1+max(lis[j]), x[j]<x[i]
	template <typename T, typename Fun>
	int LIS(T *x, int n, Fun fn);

	// O(nlgn) time, O(n) space
	// http://en.wikipedia.org/wiki/Longest_increasing_subsequence
	// http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
	// X[i]: String
	// M[j]: The index in X of the last element of IS with length j and smallest tail.
	// P[i]: The index in X of the pre element of IS end with X[i].
	// Binary Search: note X[M[0]]-X[M[1]]...X[M[L]] is nondecreasing,
	//				  find biggest j, s.t. X[M[j]] < X[i]
	template <typename T>
	int fastLIS(T *x, int n);

	template <typename T, typename Fun>
	int fastLIS(T *x, int n, Fun fn);

	template <typename T>
	int fastLIS(std::vector<int> &m, std::vector<int> &p, T *x, int n);

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "dynamic_programming.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_dynamic_programming
