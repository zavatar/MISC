#ifndef misc_dynamic_programming
#define misc_dynamic_programming

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// Dynamic Programming
//  1. Fibonacci Numbers
//  2. Rod Cutting
//  3. Matrix-chain Multiplication
//  4. Longest Common Subsequence (LCS)
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

	// O(n) (Could be O(lgn), using Matrix Form)
	inline unsigned int fibonacci_n(int n);

	template <typename T> // O(n^2)
	void rod_cutting_bottomup(T *r, int *s, T *p, int n);

	template <typename T, typename Fun> // O(n)
	void rod_cutting_reconstruct(T *r, int *s, int n, Fun fn);

	template <typename T, typename Fun> // O(n^2)+O(n)
	T rod_cutting(T *p, int n, Fun fn);

	template <typename T> // O(n^2)
	T rod_cutting(T *p, int n);


} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "dynamic_programming.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_dynamic_programming
