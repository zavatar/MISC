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
// C(i,j) = C(i-1,j)+C(i-1,j-1), Si==Tj
//        = C(i-1,j), Si!=Tj
// Note: 1.ns+1,nt+1, 2.C(i-1,0)=1 startup point, 3.reduce to one-dimension:
// C(j) += C(j-1), Si==Tj, reverse scan j--.
class Solution { // 80ms
public:
	int numDistinct(string S, string T) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int ns = S.size();
		int nt = T.size();
		if (ns<nt) return 0;
		vector<vector<int>> C(ns+1, vector<int>(nt+1,0));
		for(int i=1; i<=ns; i++) {
			C[i-1][0] = 1;
			for(int j=1; j<=nt; j++) {
				if (S[i-1] == T[j-1])
					C[i][j] = C[i-1][j] + C[i-1][j-1];
				else
					C[i][j] = C[i-1][j];
			}
		}
		return C[ns][nt];
	}
};
class Solution { // 28ms
public:
	int numDistinct(string S, string T) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int ns = S.size();
		int nt = T.size();
		if (ns<nt) return 0;
		vector<int> C(nt+1,0);
		C[0] = 1;
		for(int i=1; i<=ns; i++)
			for(int j=nt; j>=1; j--)
				if (S[i-1] == T[j-1])
					C[j] += C[j-1];
		return C[nt];
	}
};
//////////////////////////////////////////////////////////////////////////
// 114.Flatten Binary Tree to Linked List
// postorder traversal
// http://discuss.leetcode.com/questions/280/flatten-binary-tree-to-linked-list
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

    void travel(TreeNode *root, TreeNode *&t) {
        if(root == NULL) return;
		// Note, right first
        travel(root->right,t);
        travel(root->left,t);
        root->right = t;
        t = root;
        root->left = NULL;
    }

    void flatten(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(root == NULL) return;
        TreeNode* t = NULL;
        travel(root,t);
    }
};
//////////////////////////////////////////////////////////////////////////
// 113.Path Sum II
// preorder traversal, backtrack
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
    void travel(TreeNode *r, int s, int sum, vector<int>&path, vector<vector<int>>&ret) {
        if(r==NULL) return;
        s+=r->val;
        path.push_back(r->val);
        if(r->left == NULL && r->right == NULL && s == sum)
            ret.push_back(path);
        travel(r->left,s,sum,path,ret);
        travel(r->right,s,sum,path,ret);
        path.pop_back();
        
    }
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> ret;
        vector<int> path;
        travel(root, 0, sum, path, ret);
        return ret;
    }
};
//////////////////////////////////////////////////////////////////////////
// 112.Path Sum
// preorder traversal
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
    bool travel(TreeNode *r, int s, int sum) {
        if(r==NULL) return false;
        s+=r->val;
        if(r->left == NULL && r->right == NULL)
            if (s == sum) return true;
            else return false;
        return travel(r->left,s,sum) || travel(r->right,s,sum);
        
    }
    bool hasPathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return travel(root, 0, sum);
    }
};
//////////////////////////////////////////////////////////////////////////
// 111.Minimum Depth of Binary Tree
// BFS
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
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(root==NULL) return 0;
        queue<pair<TreeNode*,int>> q;
        q.emplace(root,1);
        while(!q.empty()) {
            TreeNode* x = q.front().first;
            int depth = q.front().second;
            if(x->left == NULL && x->right == NULL)
                return depth;
            if(x->left!=NULL)
                q.emplace(x->left,depth+1);
            if(x->right!=NULL)
                q.emplace(x->right,depth+1);
            q.pop();
        }
    }
};
//////////////////////////////////////////////////////////////////////////
// 110.Balanced Binary Tree
// postorder traversal
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
    bool travel(TreeNode*r, int&h) {
        if(r==NULL) {
            h=0;
            return true;
        }
        int lh, rh;
        if (!travel(r->left,lh))
            return false;
        if (!travel(r->right,rh))
            return false;
        if(abs(lh-rh) > 1)
            return false;
        else {
            h = max(lh,rh)+1;
            return true;
        }
    }
    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int h;
        return travel(root,h);
    }
};

//////////////////////////////////////////////////////////////////////////
// 109.Convert Sorted List to Binary Search Tree
//*using bottom-up approach, O(n)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode *travel(ListNode*&head,int i,int j) {
        if(i>j) return NULL;
        int m = (j+i)/2;
        TreeNode *r = new TreeNode(-1);
        r->left = travel(head,i,m-1);
        r->val = head->val;
        head = head->next;
        r->right = travel(head,m+1,j);
        return r;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = 0;
        ListNode*p = head;
        for(; p!=NULL; n++) p = p->next;
        return travel(head,0,n-1);
    }
};
// O(nlgn)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode *travel(ListNode *head,int n) {
        if(n<=0) return NULL;
        int m = n/2;
        ListNode*p = head;
        for(int i=0; i<m; i++) p = p->next;
        TreeNode *r = new TreeNode(p->val);
        r->left = travel(head,m);
        r->right = travel(p->next,n-m-1);
        return r;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = 0;
        ListNode*p = head;
        for(; p!=NULL; n++) p = p->next;
        return travel(head,n);
    }
};
//////////////////////////////////////////////////////////////////////////
// 108.Convert Sorted Array to Binary Search Tree
// direct index
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
    TreeNode *travel(vector<int>&num,int i, int j) {
        if(i>j) return NULL;
        int m = (j+i)/2;
        TreeNode *r = new TreeNode(num[m]);
        r->left = travel(num,i,m-1);
        r->right = travel(num,m+1,j);
        return r;
    }
    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = num.size();
        return travel(num,0,n-1);
    }
};
//////////////////////////////////////////////////////////////////////////
// 107.Binary Tree Level Order Traversal II
// preorder traversal, push node to correct level vector.
// or postorder, just make sure push left before right.
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
    void travel(TreeNode*r, int d, vector<vector<int>>&ret) {
        if(r == NULL) return;
        if(d >= ret.size()) ret.push_back(vector<int>(1,r->val));
        else ret[d].push_back(r->val);
        travel(r->left,d+1,ret);
        travel(r->right,d+1,ret);
    }
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> ret;
        travel(root, 0, ret);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
//////////////////////////////////////////////////////////////////////////
// 106.Construct Binary Tree from Inorder and Postorder Traversal
//*find the root, then recursively build the tree
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
    TreeNode *travel(vector<int> &inorder, int i, int j, vector<int> &postorder) {
        if(i>j) return NULL;
        TreeNode *r = new TreeNode(postorder.back());
        postorder.pop_back();
        int m = i;
        for(int k=i; k<=j; k++)
            if(inorder[k] == r->val)
            { m = k; break; }
        r->right = travel(inorder, m+1, j, postorder);
        r->left = travel(inorder, i, m-1, postorder);
        return r;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return travel(inorder, 0, inorder.size()-1, postorder);
    }
};
//////////////////////////////////////////////////////////////////////////
// 105.Construct Binary Tree from Preorder and Inorder Traversal
//*find the root, then recursively build the tree
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
    TreeNode *travel(vector<int> &inorder, int i, int j, vector<int> &preorder, int&ii) {
        if(i>j) return NULL;
        TreeNode *r = new TreeNode(preorder[ii]);
        ii++;
        int m = i;
        for(int k=i; k<=j; k++)
            if(inorder[k] == r->val)
            { m = k; break; }
        r->left = travel(inorder, i, m-1, preorder, ii);
        r->right = travel(inorder, m+1, j, preorder, ii);
        return r;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int k=0;
        return travel(inorder, 0, inorder.size()-1, preorder, k);
    }
};
//////////////////////////////////////////////////////////////////////////
// 104.Maximum Depth of Binary Tree
// DFS, preorder traversal
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
    void travel(TreeNode *r, int d) {
        if(r==NULL) return;
        if(r->left == NULL && r->right == NULL)
            maximum = max(maximum, d+1);
        travel(r->left, d+1);
        travel(r->right, d+1);
    }
    int maxDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        maximum = 0;
        travel(root, 0);
        return maximum;
    }
    int maximum;
};
//////////////////////////////////////////////////////////////////////////
// 103.Binary Tree Zigzag Level Order Traversal
// Like 107. Could use Stack.
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> ret;
        stack<TreeNode*> q[2];
        int cur = 0;
        int pre = 1;
        q[cur].push(root);
        while(!q[cur].empty()) {
            cur = 1-cur;
            pre = 1-pre;
            vector<int> v;
            while(!q[pre].empty()) {
                TreeNode* x = q[pre].top();
                q[pre].pop();
                if (x==NULL) continue;
                v.push_back(x->val);
                if(cur==1) {
                    q[cur].push(x->left);
                    q[cur].push(x->right);
                }else{
                    q[cur].push(x->right);
                    q[cur].push(x->left);
                }
            }
            if (!v.empty())
                ret.push_back(v);
        }
        return ret;
    }
};
//////////////////////////////////////////////////////////////////////////
// 102.Binary Tree Level Order Traversal
// Like 107.
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
    void travel(TreeNode*r, int d, vector<vector<int>>&ret) {
        if(r == NULL) return;
        if(d >= ret.size()) ret.push_back(vector<int>(1,r->val));
        else ret[d].push_back(r->val);
        travel(r->left,d+1,ret);
        travel(r->right,d+1,ret);
    }
    vector<vector<int> > levelOrder(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> ret;
        travel(root, 0, ret);
        return ret;
    }
};
//////////////////////////////////////////////////////////////////////////
// 101.Symmetric Tree
// order and rorder traversal
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
    void preorderTravel(TreeNode*r, vector<int>&v) {
        if(r==NULL) return;
        v.push_back(r->val);
        preorderTravel(r->left, v);
        preorderTravel(r->right, v);
    }
    void rpreorderTravel(TreeNode*r, vector<int>&v) {
        if(r==NULL) return;
        v.push_back(r->val);
        rpreorderTravel(r->right, v);
        rpreorderTravel(r->left, v);
    }
    void inorderTravel(TreeNode*r, vector<int>&v) {
        if(r==NULL) return;
        inorderTravel(r->left, v);
        v.push_back(r->val);
        inorderTravel(r->right, v);
    }
    void rinorderTravel(TreeNode*r, vector<int>&v) {
        if(r==NULL) return;
        rinorderTravel(r->right, v);
        v.push_back(r->val);
        rinorderTravel(r->left, v);
    }
    bool isSymmetric(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> order;
        vector<int> rorder;
        preorderTravel(root,order);
        rpreorderTravel(root,rorder);
        if (order != rorder)
            return false;
        else {
            order.clear();
            rorder.clear();
            inorderTravel(root,order);
            rinorderTravel(root,rorder);
            return order == rorder;
        }
    }
};
//////////////////////////////////////////////////////////////////////////
// 100.Same Tree
// preorder same and postorder same? no!!!, since there are same value
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
    bool travel2(TreeNode *p, TreeNode *q) {
        if(p==NULL && q==NULL) return true;
        if(p==NULL && q!=NULL) return false;
        if(p!=NULL && q==NULL) return false;
        if(p->val != q->val) return false;
        return travel2(p->left, q->left) && travel2(p->right, q->right);
    }
    bool isSameTree(TreeNode *p, TreeNode *q) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return travel2(p, q);
    }
};
//////////////////////////////////////////////////////////////////////////
// 99.Recover Binary Search Tree
//*http://fisherlei.blogspot.com/2012/12/leetcode-recover-binary-search-tree.html
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
    void travel(TreeNode*r) {
        if(r==NULL) return;
        travel(r->left);
        if(mistake[cur]!=NULL && mistake[cur]->val > r->val) {
            if(cur==0) cur++;
            mistake[2] = r;
        }
        mistake[cur] = r;
        travel(r->right);
    }
    void recoverTree(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        cur = 0;
        mistake.clear();
        mistake.push_back(NULL);
        mistake.push_back(NULL);
        mistake.push_back(NULL);
        travel(root);
        swap(mistake[0]->val, mistake[2]->val);
    }
    vector<TreeNode*> mistake;
    int cur;
};
//////////////////////////////////////////////////////////////////////////
// 98.Validate Binary Search Tree
// inorder traversal
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
    bool travel(TreeNode*r) {
        if(r==NULL) return true;
        if (!travel(r->left)) return false;
        if(pre!=NULL && pre->val >= r->val) return false; // Equal???
        pre = r;
        if(!travel(r->right)) return false;
        return true;
    }
    bool isValidBST(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        pre = NULL;
        return travel(root);
    }
    TreeNode*pre;
};
//////////////////////////////////////////////////////////////////////////
// 97.Interleaving String
//*DP. B(i,j) = S1(i)==S3(i+j+1) && B(i-1,j) || S2(j)==S3(i+j+1) && B(i,j-1)
// Note: i,j start from 0
// http://fisherlei.blogspot.com/2012/12/leetcode-interleaving-string.html
class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function    
		int n1 = s1.size();
		int n2 = s2.size();
		int n3 = s3.size();
		if(n1+n2 != n3) return false;
		vector<bool> B[2];
		int cur = 0;
		int pre = 1;
		B[cur].resize(n2+1, false);
		B[pre].resize(n2+1, false);
		B[pre][0] = true;
		for(int j=1; j<=n2; j++)
			B[pre][j] = B[pre][j-1] && s2[j-1]==s3[j-1];
		for(int i=1; i<=n1; i++) {
			B[cur][0] = B[pre][0] && s1[i-1]==s3[i-1];
			for(int j=1; j<=n2; j++)
				B[cur][j] = (s1[i-1]==s3[i+j-1] && B[pre][j]) || (s2[j-1]==s3[i+j-1] && B[cur][j-1]);
			cur = 1-cur;
			pre = 1-pre;
		}
		return B[pre][n2];
	}
};

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
// 88.Merge Sorted Array
// Trivial merge sort

//////////////////////////////////////////////////////////////////////////
// 87.Scramble String
// 

//////////////////////////////////////////////////////////////////////////
// 86.Partition List
// Straight forward

//////////////////////////////////////////////////////////////////////////
// 85.Maximal Rectangle
// DP, Like 4.4 in dynamic_programming

//////////////////////////////////////////////////////////////////////////
// 84.Largest Rectangle in Histogram
// H(i,j) = min{hi, hj, H(i-1,j-1)}
// return max{H(i,j)*(j-i+1)}

//////////////////////////////////////////////////////////////////////////
// 83.Remove Duplicates from Sorted List
// Sorted List is trival

//////////////////////////////////////////////////////////////////////////
// 82.Remove Duplicates from Sorted List II
// Sorted List is trival

//////////////////////////////////////////////////////////////////////////
// 81.Search in Rotated Sorted Array II
// refer to 33.

//////////////////////////////////////////////////////////////////////////
// 80.Remove Duplicates from Sorted Array II
// refer to 26.


