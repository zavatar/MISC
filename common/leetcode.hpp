//////////////////////////////////////////////////////////////////////////
//132.Palindrome Partitioning II
class Solution {
public:
	int minCut(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = s.length();
		if (n<2) return 0;
		vector<int> M(n,0);
		vector<vector<bool>> P(n,vector<bool>(n,false));
		for(int i=1; i<n; i++) {
			if (s[0] == s[i] && (i<3 || P[1][i-1]))
				M[i] = 0;
			else {
				M[i] = min(i, M[i-1]+1);
				for (int k=i-1; k>0; k--) {
					if (s[k] == s[i] && (i-k<3 || P[k+1][i-1])) {
						P[k][i] = true;
						M[i] = min(M[i], M[k-1]+1);
					}
				}  
			}
		}
		return M[n-1];
	}
};
//////////////////////////////////////////////////////////////////////////
// 131.Palindrome Partitioning
class Solution {
public:

	void DFS(string&s, int i, vector<vector<bool>>&P,
		vector<vector<string>>&R, vector<string>&S){
			int n = s.size();
			if (i==n) {
				R.push_back(S);
				return;
			}
			for (int j = i; j<n; j++) {
				if(P[i][j]) {
					S.push_back(s.substr(i,j-i+1));
					DFS(s,j+1,P,R,S);
					S.pop_back();
				}
			}
	}

	vector<vector<string>> partition(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = s.size();
		vector<vector<bool>> P(n,vector<bool>(n,false));
		for(int i=n-1; i>=0; i--) {
			P[i][i] = true;
			for(int k=i-1; k<n; k++) {
				if (s[i]==s[k] && (k-i<3 || P[i+1][k-1]))
					P[i][k] = true;
			}
		}
		vector<vector<string>> results;
		vector<string> ts;
		DFS(s,0, P, results, ts);
		return results;
	}
};
//////////////////////////////////////////////////////////////////////////
// 130.Surrounded Regions
class Solution {
public:

	void flip(vector<vector<char>> &b, int i, int j) {
		if (i<0 || i>=n || j<0 || j>=m)
			return;
		if (b[i][j] == 'O') {
			b[i][j]='A';
			flip(b, i-1, j);
			flip(b, i+1, j);
			flip(b, i, j-1);
			flip(b, i, j+1);
		}
	}

	void solve(vector<vector<char>> &board) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		n = board.size();
		if (n==0) return;
		m = board[0].size();
		if (m==0) return;
		for(int i=0; i<n; i++) {
			flip(board, i, 0);
			flip(board, i, m-1);
		}
		for(int i=0; i<m; i++) {
			flip(board, 0, i);
			flip(board, n-1, i);
		}
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				if(board[i][j] == 'O')
					board[i][j] = 'X';
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				if(board[i][j] == 'A')
					board[i][j] = 'O';

	}
	int m,n;
};
//////////////////////////////////////////////////////////////////////////
// 129.Sum Root to Leaf Numbers
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sum = 0;
        if (root == NULL) return 0;
        int X = 0;
        travel(root, X);
        return sum;
    }
    
    void travel(TreeNode* node, int X) {
        if (node == NULL) return;
        X = 10*X + node->val;
        travel(node->left, X);
        travel(node->right, X);
        if (node->left == NULL && node->right == NULL)
            sum += X;
    }
    
    int sum;
};
//////////////////////////////////////////////////////////////////////////
// 128.Longest Consecutive Sequence
class Solution {
public:
	int longestConsecutive(vector<int> &num) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		unordered_map<int,int> m;
		int n = num.size();
		vector<bool> visited(n, false);
		for (int i=0; i<n; i++)
			m[num[i]] = i;
		int ml = 0;
		for (int i=0; i<n; i++) {
			if (visited[i]) continue;
			visited[i] = true;
			int j = num[i];
			int l = 1;
			for(int k=j+1; m.find(k)!=m.end() && !visited[m[k]]; k++,l++)
				visited[m[k]] = true;
			for(int k=j-1; m.find(k)!=m.end() && !visited[m[k]]; k--,l++)
				visited[m[k]] = true;
			ml = max(ml, l);
		}
		return ml;
	}
};
//////////////////////////////////////////////////////////////////////////
// 126.Word Ladder
class Solution {
public:
	int ladderLength(string start, string end, unordered_set<string> &dict) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		dict.erase(start);
		dict.insert(end);
		
		queue<pair<string, int> > q;
		for (q.emplace(start, 1); !q.empty(); q.pop()) {
			string w = q.front().first;
			int l = q.front().second;
			if (w == end)
				return l;
			for (int i=0; i<w.size(); i++) {
				char tc = w[i];
				for (char c='a'; c<='z'; c++) {
					w[i] = c;
					if (dict.find(w) != dict.end()) {
						q.emplace(w, l+1);
						dict.erase(w);
					}
				}
				w[i] = tc;
			}
		}
		return 0;
	}
};
//////////////////////////////////////////////////////////////////////////
// 127.Word Ladder II
// http://blog.csdn.net/niaokedaoren/article/details/8884938
class Solution {
public:
	void DFS_path(unordered_map<string, vector<string> > &trs, 
		vector<string> &path, const string &w) {
			if (trs[w].size() == 0) {
				path.push_back(w);
				vector<string> curPath = path;
				reverse(curPath.begin(), curPath.end());
				pathes.push_back(curPath);
				path.pop_back();
				return;
			}

			path.push_back(w);
			for_each(trs[w].begin(), trs[w].end(), [&](const string&w){
				DFS_path(trs, path, w);
			});
			path.pop_back();
	}

	vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		pathes.clear();
		dict.insert(start);
		dict.insert(end);
		vector<string> prev;
		unordered_map<string, vector<string> > trs;
		for_each(dict.begin(), dict.end(), [&](const string&w){
			trs[w] = vector<string>();
		});

		vector<unordered_set<string> > lay(2);
		int cur = 0;
		int pre = 1;
		lay[cur].insert(start);
		while (true) {
			cur = !cur;
			pre = !pre;
			for_each(lay[pre].begin(), lay[pre].end(), [&](const string&w){
				dict.erase(w);
			});
			lay[cur].clear();
			for_each(lay[pre].begin(), lay[pre].end(), [&](const string&w){
				for (int i=0; i<w.size(); i++) {
					string wt(w);
					for (char c='a'; c<='z'; c++) {
						wt[i] = c;
						if (dict.find(wt) != dict.end()) { 
							trs[wt].push_back(w);
							lay[cur].insert(wt);
						}
					}
				}
			});
			if (lay[cur].size() == 0)
				return pathes;
			if (lay[cur].count(end))
				break;
		}
		vector<string> path;
		DFS_path(trs, path, end);
		return pathes;
	}

	vector<vector<string> > pathes;
};
//////////////////////////////////////////////////////////////////////////
// 125.Valid Palindrome
class Solution {
public:
	bool isAlphanumeric(const char&c) {
		return (c>='a'&&c<='z') || (c>='A'&&c<='Z') || (c>='0'&&c<='9');
	}
	bool isPalindrome(string s) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = s.size();
		string st;
		st.reserve(n);
		for (int i=0; i<n; i++)
			if (isAlphanumeric(s[i]))
				st.push_back(s[i]);
		n = st.size();
		if (n == 0) return true;
		for(int i=0,j=n-1; i<j; i++,j--)
			if(tolower(st[i])!=tolower(st[j]))
				return false;
		return true;
	}
};
//////////////////////////////////////////////////////////////////////////
// 124.Binary Tree Maximum Path Sum
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

    int travel(TreeNode *r) {
        if(r == NULL) return 0;
        int lmax = travel(r->left);
        int rmax = travel(r->right);
        maxval = max(maxval,r->val);
        maxsum = max(maxsum, lmax+rmax+r->val);
        return max(max(lmax,rmax)+r->val,0);
    }

    int maxPathSum(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        maxval = numeric_limits<int>::min();
        maxsum = 0;
        travel(root);
        if (maxval <= 0) return maxval;
        else return maxsum;
    }
    int maxval, maxsum;
};
//////////////////////////////////////////////////////////////////////////
// 121.Best Time to Buy and Sell Stock
class Solution {
public:
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int maxval = 0;
		int n = prices.size();
		if (n <= 1) return 0;
		int curmin = prices[0];
		for (int i=1; i<n; i++) {
			curmin = min(curmin, prices[i]);
			maxval = max(maxval, prices[i]-curmin);
		}
		return maxval;
	}
};
//////////////////////////////////////////////////////////////////////////
// 122.Best Time to Buy and Sell Stock II
// O(n^2), Large data timeout
class Solution {
public:
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = prices.size();
		if (n <= 1) return 0;
		vector<int> C(n+1,0);
		for (int i=n-1; i>=0; i--) {
			int maxval = 0;
			int curmin = prices[i];
			for (int k=i+1; k<n; k++) {
				curmin = min(curmin, prices[k]);
				maxval = max(maxval, prices[k]-curmin);
				C[i] = max(maxval + C[k+1], C[i]);
			}
		}
		return C[0];
	}
};
// O(n)
class Solution {
public:
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = prices.size();
		if (n <= 1) return 0;
		int maxval = 0;
		int curmin = prices[0];
		int curmax = prices[0];
		for (int i=1; 1; ) {
			curmin = curmax;
			for (; i<n && prices[i]<=curmin; i++)
				curmin = prices[i];
			if (i>=n) break;
			curmax = curmin;
			for (; i<n && prices[i]>=curmax; i++)
				curmax = prices[i];
			maxval += curmax-curmin;
		}
		return maxval;
	}
};
//////////////////////////////////////////////////////////////////////////
// 123.Best Time to Buy and Sell Stock III
class Solution {
public:
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int maxval = 0;
		int n = prices.size();
		if (n <= 1) return 0;
		int curmin = prices[0];
		vector<int> l2r(n,0);
		for (int i=1; i<n; i++) {
			curmin = min(curmin, prices[i]);
			maxval = max(maxval, prices[i]-curmin);
			l2r[i] = maxval;
		}
		maxval = 0;
		int curmax = prices[n-1];
		vector<int> r2l(n,0);
		for (int i=n-2; i>=0; i--) {
			curmax = max(curmax, prices[i]);
			maxval = max(maxval, curmax-prices[i]);
			r2l[i] = maxval;
		}
		maxval = 0;
		for (int i=0; i<n; i++)
			maxval = max(maxval, l2r[i]+r2l[i]);
		return maxval;
	}
};
//////////////////////////////////////////////////////////////////////////
// 120.Triangle
class Solution {
public:
	int minimumTotal(vector<vector<int> > &triangle) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int n = triangle.size();
		if (n == 0) return 0;
		if (n == 1) return triangle[0][0];
		vector<int> e[2];
		e[0].resize(n,0);
		e[1].resize(n,0);
		e[0][0]=triangle[0][0];
		int cur = 0;
		int pre = 1;
		for (int i=1; i<n; i++) {
			cur = 1-cur;
			pre = 1-pre;
			e[cur][0] = e[pre][0]+triangle[i][0];
			for (int j=1; j<i; j++) {
				e[cur][j] = min(e[pre][j-1],e[pre][j])+triangle[i][j];
			}
			e[cur][i] = e[pre][i-1]+triangle[i][i];
		}
		int maxval = e[cur][0];
		for(int i=0; i<n; i++)
			maxval = min(maxval, e[cur][i]);
		return maxval;
	}
};
//////////////////////////////////////////////////////////////////////////
// 118.Pascal's Triangle
class Solution {
public:
	vector<vector<int> > generate(int numRows) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<vector<int>> ret;
		if (numRows == 0) return ret;
		vector<int> r[2];
		r[0].resize(1,1);
		r[1].resize(1,1);
		int cur = 0;
		int pre = 1;
		ret.push_back(r[cur]);
		for (int i=1; i<numRows; i++) {
			cur = 1-cur;
			pre = 1-pre;
			for (int j=1; j<i; j++)
				r[cur][j] = r[pre][j-1] + r[pre][j];
			r[cur].push_back(1);
			r[pre].push_back(1);
			ret.push_back(r[cur]);
		}
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 119.Pascal's Triangle II
class Solution {
public:
	vector<int> getRow(int rowIndex) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		vector<int> r[2];
		r[0].resize(1,1);
		r[1].resize(1,1);
		int cur = 0;
		int pre = 1;
		for (int i=1; i<=rowIndex; i++) {
			cur = 1-cur;
			pre = 1-pre;
			for (int j=1; j<i; j++)
				r[cur][j] = r[pre][j-1] + r[pre][j];
			r[cur].push_back(1);
			r[pre].push_back(1);
		}
		return r[cur];
	}
};
//////////////////////////////////////////////////////////////////////////
// 116.Populating Next Right Pointers in Each Node
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) return;
        TreeLinkNode *x = root;
        while(x != NULL) {
            if (x->left != NULL)
                x->left->next = x->right;
            if (x->right != NULL) {
                x->right->next = NULL;
                if (x->next != NULL)
                    x->right->next = x->next->left;
            }
            x = x->next;
        }
        connect(root->left);
    }
};
//////////////////////////////////////////////////////////////////////////
// 117.Populating Next Right Pointers in Each Node II
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) return;
        TreeLinkNode *x = root;
        TreeLinkNode *pre = NULL;
        TreeLinkNode *nxt = NULL;
        while(x != NULL) {
            if (pre != NULL) {
                if (x->left != NULL) {
                    pre->next = x->left;
                    pre = x->left;
                }
                if (x->right != NULL) {
                    pre->next = x->right;
                    pre = x->right;
                }
            } else {
                if (x->left != NULL) {
                    nxt = pre = x->left;
                    if (x->right != NULL) {
                        pre->next = x->right;
                        pre = x->right;
                    }
                } else {
                    if (x->right != NULL) {
                        nxt = pre = x->right;
                    }
                }
            }
            x = x->next;
        }
        connect(nxt);
    }
};
//////////////////////////////////////////////////////////////////////////
// 115.Distinct Subsequences
//*like LCS, DP

//////////////////////////////////////////////////////////////////////////
// 114.Flatten Binary Tree to Linked List
// postorder traversal

//////////////////////////////////////////////////////////////////////////
// 113.Path Sum II
// inorder traversal, backtrack

//////////////////////////////////////////////////////////////////////////
// 112.Path Sum
// inorder traversal

//////////////////////////////////////////////////////////////////////////
// 111.Minimum Depth of Binary Tree
// BFS

//////////////////////////////////////////////////////////////////////////
// 110.Balanced Binary Tree
// postorder traversal

//////////////////////////////////////////////////////////////////////////
// 109.Convert Sorted List to Binary Search Tree
//*using bottom-up approach

//////////////////////////////////////////////////////////////////////////
// 108.Convert Sorted Array to Binary Search Tree
// direct index

//////////////////////////////////////////////////////////////////////////
// 107.Binary Tree Level Order Traversal II
// preorder traversal, push node to correct level vector.

//////////////////////////////////////////////////////////////////////////
// 106.Construct Binary Tree from Inorder and Postorder Traversal
//*find the root, then recursively build the tree

//////////////////////////////////////////////////////////////////////////
// 105.Construct Binary Tree from Preorder and Inorder Traversal
//*find the root, then recursively build the tree

//////////////////////////////////////////////////////////////////////////
// 104.Maximum Depth of Binary Tree
// DFS

//////////////////////////////////////////////////////////////////////////
// 103.Binary Tree Zigzag Level Order Traversal
// Like 107.

//////////////////////////////////////////////////////////////////////////
// 102.Binary Tree Level Order Traversal
// Like 107.

//////////////////////////////////////////////////////////////////////////
// 101.Symmetric Tree
// inorder traversal

//////////////////////////////////////////////////////////////////////////
// 100.Same Tree
// preorder same and postorder same?

//////////////////////////////////////////////////////////////////////////
// 99.Recover Binary Search Tree
// ?

//////////////////////////////////////////////////////////////////////////
// 98.Validate Binary Search Tree
// inorder traversal

//////////////////////////////////////////////////////////////////////////
// 97.Interleaving String
//*DP

//////////////////////////////////////////////////////////////////////////
// 96.Unique Binary Search Trees
class Solution {
public:
	int numTrees(int n) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (n<=0) return 0;
		vector<int> N(n+1, 0);
		N[0]=1;
		for (int i=1; i<=n; i++)
			for (int j=1; j<=i; j++)
				N[i] += N[j-1]*N[i-j];
		return N[n];
	}
};

//////////////////////////////////////////////////////////////////////////
// 95.Unique Binary Search Trees II
// recursively build left and right tree

//////////////////////////////////////////////////////////////////////////
// 94.Binary Tree Inorder Traversal
// iteratively?

//////////////////////////////////////////////////////////////////////////
// 93.Restore IP Addresses
// IP rule?

//////////////////////////////////////////////////////////////////////////
// 92.Reverse Linked List II
// double pointers

//////////////////////////////////////////////////////////////////////////
// 90.Subsets II
// ?

//////////////////////////////////////////////////////////////////////////
// 91.Decode Ways
// DP

//////////////////////////////////////////////////////////////////////////
// 89.Gray Code
// 

//////////////////////////////////////////////////////////////////////////
// 88.
// 
