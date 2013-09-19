#ifndef misc_dynamic_programming
#define misc_dynamic_programming

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// Dynamic Programming
//  1 Fibonacci Numbers, O(n) or O(lgn)
//
//  2 Subarray/Substring Problems, O(n)
//  2.1 Maximum Subarray
//  2.2 Longest Non-Repeating Character Substring
//  2.3 Longest Palindromic Substring
//       return max{Lt(i)}, i（[0,n)
//  2.4 nth Ugly Number (2,3,5)
//       select min(p2*2, p3*3, p5*5)
// *2.5 Longest Common Substring
//       Lt(i,j) = Lt(i-1,j-1)+1, X[i]==Y[j]
//              = 0, X[i]!=Y[j]
//       return max{Lt(i,j)}
//    OR Suffix Tree O(n+m)
//
//  3 left to right scan, based on left range, O(n^2)
//  3.1 Rod Cutting / Word Break 
//       r[i] = max{p[i-j]+r[j]}, j（[0,i)
//  3.2 Longest Increasing Subsequence (LIS)
//       Lt(i) = 1+max{Lt(j)}, j（[0,i) & x[j]<x[i]
//	     return max{Lt(i)}, i（[0,n)
//  3.3 Maximum Sum Increasing Subsequence
//       St(i) = x[i]+max{St(j)}, j（[0,i) & x[j]<x[i]
//	     return max{St(i)}, i（[0,n)
//  3.4 Longest Bitonic Subsequence
//       compute LIS(seq) and LIS(rev)
//	     return max{Ltseq(i) + Ltrev(i)}, i（[0,n)
//  3.5 Variations of LIS
//       Building Bridges; *Box Stacking; 
//  3.6 Text Justification/ Word Wrap
//	     E(i) = min{E(j)+(L-l(j,i)^2}, j（[maxj(L>=l(j,i),0),i)
//  3.7 Minimum Number of Jumps to reach end
//       J(i) = 1+min{J(j)}, j（[0,i) & x[j]+j>=i
//
//  4
//  4.1 Longest Common Subsequence (LCS)
//       L(i,j) = L(i-1,j-1)+1, X[i]==Y[j]
//              = max(L(i-1,j), L(i,j-1)), X[i]!=Y[j]
//  4.2 Edit Distance
//	     E(i,j) = min(E(i-1,j)+D, E(i,j-1)+I, E(i-1,j-1)+X[i]==Y[j]?0:R)
//  4.3 Min Cost Path
//       E(i,j) = min(E(i-1,j), E(i,j-1), E(i-1,j-1)) + C(i,j)
//  4.4 Maximum size square sub-matrix with all 1s
//       S(i,j) = min(S(i-1,j), S(i,j-1), S(i-1,j-1)), M[i][j]==1
//              = 0, M[i][j]==0
// *4.5 Longest Palindromic Subsequence
//       L(i,j) = L(i+1,j-1)+2, X[i]==X[j]
//              = max(L(i+1,j), L(i,j-1)), X[i]!=X[j]
//    OR LCS(seq, rev)
//  4.6 Minimum insertions to form a palindrome
//       I(i,j) = I(i+1,j-1),  X[i]==X[j]
//              = min(I(i+1,j), I(i,j-1))+1, X[i]!=X[j]
//  4.7 Find if a string is interleaved of two other strings
//       Like http://leetcode.com/onlinejudge#question_97
//       B(i,j) = S1(i)==S3(i+j+1) && B(i-1,j) || S2(j)==S3(i+j+1) && B(i,j-1)
//
//  5 select from set
//  5.1 Coin Change (# ways / min# coins), Coin Set S{a,b,...} |S|=m
//       C(N,m) = C(N,m-1) + C(N-S[m],m); # ways
//       C(N,m) = min(C(N,m-1), C(N-S[m],m)+1); min# coins
//  5.2 Partition Problem, partition set to two equal sum sets, Sum/2
//	5.3 Subset Sum
//       B(Sum,m) = B(Sum,m-1) || B(Sum-x[m],m-1)
//  5.4 Dice Throw, m faces, n dices, Sum
//       C(Sum,i) = ΣC(Sum-j,i-1), j（[1,m];
//  5.5 0-1 Knapsack
//       K(w,i) = max(K(w,i-1), K(w-W[i],i-1)+V[i])
//  
//  6 Strategy
//  6.1 Egg Dropping, k floors, n eggs
//       T(n,k) = 1+min{max(T(n-1,j-1), T(n,k-j))}, j（[1,k]
//  6.2 Optimal Strategy for a Game
//       F(i,j) = max(V[i]+min(F(i+2,j),F(i+1,j-1)), V[j]+min(F(i+1,j-1),F(i,j-2)))
//
//  7.
//  7.1 Matrix-chain Multiplication
//       M(i,j) = min{M(i,k)+M(k+1,j)+E(i,k,j)}, k（[i,j)
//  7.2 Palindrome Partitioning
//      O^3:
//       M(i,j) = min{M(i,k)+M(k+1,j)+1}, k（[i,j), x(i,j) is Palindrome
//              = 0, x(i,j) is not Palindrome
//      O^2: similar with rod cutting problem
//       M(i++) = min(M(k-1)+1), k（[i,-,0], x(k,i) is Palindrome
//		 reversed scan: M(i--) = min(M(k+1)+1), k（[i,n), x(i,k) is Palindrome
//
//  8.  Optimal BST
//	     O(i,j) = (Σw(k),k（[i,j]) + (min{O(i,r-1)+O(r+1,j)}, r（[i,j])
//
//  9.  All Shortest Path (Floyd Warshall/ Bellman Ford)
//  10. Black Jack
//  11. Seam Carving / Assembly Line Scheduling
//  12. Maximum sum rectangle in a 2D matrix
//  13. Longest Arithmetic Progression
//
// Greedy Programming
//  1. Kruskal's Minimum Spanning Trees
//  2. Prim's Minimum Spanning Tree (MST)
//  3. Huffman Coding
//  4. Efficient Huffman Coding for Sorted Input
//  5. Dijkstra Shortest Path (BFS)
//  6. Activity Selection (Maximum length Chain of Pairs)
//
//////////////////////////////////////////////////////////////////////////

	// 1. Fibonacci Numbers
	// O(n) (Could be O(lgn), using Matrix Form)
	// http://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
	inline unsigned int fibonacci_n(int n);

	// 3.1 Rod Cutting / Word Break 
	template <typename T, typename Fun>
	T rod_cutting(T *p, int n, Fun fn);

	// 3.2 Longest Increasing Subsequence (LIS)
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
	template <typename T, typename Fun>
	int fastLIS(T *x, int n, Fun fn);

	// 4.1 Longest Common Subsequence (LCS)
	template <typename T, typename Fun>
	int LCS(T *x, int m, T *y, int n, Fun fn);

	// 4.2 Edit Distance
	template <typename T, typename Fun>
	int edit_distance(T *x, int m, T *y, int n, Fun fn);

	// 7.2 Palindrome Partitioning
	// http://www.geeksforgeeks.org/dynamic-programming-set-17-palindrome-partitioning/
	// http://leetcode.com/onlinejudge#question_132
	template <typename T>
	int palindrome_partitioningOn3(T *x, int n);
	template <typename T>
	int palindrome_partitioningOn2(T *x, int n);

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "dynamic_programming.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_dynamic_programming
