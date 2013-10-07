//////////////////////////////////////////////////////////////////////////
// 140.Word Break II
//*http://www.cnblogs.com/superzrx/p/3354813.html
class Solution {
public:
	void DFS(string &s, int i, vector<int> &p, vector<vector<int>> &mem, vector<string> &ret) {
		for(auto&k : mem[i]) {
			p.push_back(k);
			if(k == 0) {
				string w;
				for(int k=p.size()-1; k>0; k--)
					w.append(s.substr(p[k],p[k-1]-p[k])+' ');
				w.append(s.substr(p[0]));
				ret.push_back(w);
			} else
				DFS(s, k, p, mem, ret);
			p.pop_back();
		}
	}
	vector<string> wordBreak(string s, unordered_set<string> &dict) {
		vector<string> ret;
		vector<vector<int>> mem;
		int n=s.size();
		int maxw = 0;
		for(auto&w : dict) maxw = max(maxw,int(w.size()));
		vector<bool> S(n+1,false);
		mem.resize(n+1);
		S[0] = true;
		for(int i=0; i<n; i++)
			if(S[i])
				for(int j=1; j<=min(maxw,n-i); j++)
					if(dict.find(s.substr(i,j)) != dict.end()) {
						S[i+j] = true;
						mem[i+j].push_back(i);
					}
		vector<int> path;
		DFS(s, n, path, mem, ret);
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 139.Word Break
//*DP
// O(n^2)
class Solution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		int n=s.size();
		if(n==0) return true;
		vector<vector<bool>> S(n,vector<bool>(n,false));
		for(int i=0; i<n; i++)
			S[i][i] = (dict.find(s.substr(i,1))!=dict.end());
		for(int l=2; l<=n; l++) {
			for(int i=0; i+l-1<n; i++) {
				int j=i+l-1;
				if(S[i][j] = (dict.find(s.substr(i,l))!=dict.end()))
					continue;
				for(int k=i; k<j; k++)
					if(S[i][j] = (S[i][k]&&S[k+1][j]))
						break;
			}
		}
		return S[0][n-1];
	}
};
// O(n*l)
class Solution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		int n=s.size();
		if(n==0) return true;
		int maxw = 0;
		for(auto&w : dict) maxw = max(maxw,int(w.size()));
		vector<bool> S(n+1,false);
		S[0] = true;
		for(int i=0; i<n; i++)
			if(S[i])
				for(int j=1; j<=min(maxw,n-i); j++)
					if(dict.find(s.substr(i,j)) != dict.end())
						S[i+j] = true;
		return S[n];
	}
};
//////////////////////////////////////////////////////////////////////////
// 138.Copy List with Random Pointer 
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head == NULL) return NULL;
        for(RandomListNode *h=head; h!=NULL; h=h->next->next) {
            RandomListNode *p = new RandomListNode(h->label);
            p->next = h->next;
            h->next = p;
        }
        for(RandomListNode *h=head; h!=NULL; h=h->next->next) {
            if(h->random == NULL)
                h->next->random = NULL;
            else
                h->next->random = h->random->next;
        }
        RandomListNode *copyhead = head->next;
        for(RandomListNode *h1=head, *h2=copyhead; ; h1=h1->next, h2=h2->next) {
            h1->next = h1->next->next;
            if(h1->next == NULL) break;
            h2->next = h2->next->next;
        }
        return copyhead;
    }
};
//////////////////////////////////////////////////////////////////////////
// 137.Single Number II
class Solution {
public:
	int singleNumber(int A[], int n) {
		vector<int> bits(32,0);
		for(int i=0; i<n; i++)
			for(int k=0; k<32; k++)
				bits[k]+=(A[i]>>k)&1;
		int ret=0;
		for(int k=0; k<32; k++)
			ret|=(bits[k]%3)<<k;
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 136.Single Number
class Solution {
public:
	int singleNumber(int A[], int n) {
		int ret=A[0];
		for(int i=1; i<n; i++)
			ret ^= A[i];
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 135.Candy
class Solution {
public:
	int candy(vector<int> &ratings) {
		int n=ratings.size();
		int sum=n;
		vector<int> res(n,0);
		for(int k=1,i=1; i<n; i++)
			if(ratings[i]>ratings[i-1])
				res[i]=max(k++, res[i]);
			else
				k=1;
		for(int k=1,i=n-2; i>=0; i--)
			if(ratings[i]>ratings[i+1])
				res[i]=max(k++, res[i]);
			else
				k=1;
		for(int i=0; i<n; i++)
			sum+=res[i];
		return sum;
	}
};
//////////////////////////////////////////////////////////////////////////
// 134.Gas Station
class Solution {
public:
	int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
		int n=gas.size();
		int sum=0;
		int total=0;
		int idx=-1;
		for(int i=0; i<n; i++) {
			total += gas[i]-cost[i];
			sum += gas[i]-cost[i];
			if(sum < 0) {
				idx = i;
				sum=0;
			}
		}
		return total<0?-1:idx+1;
	}
};
//////////////////////////////////////////////////////////////////////////
// 133.Clone Graph
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;
        unordered_map<UndirectedGraphNode*,UndirectedGraphNode*> hash;
        UndirectedGraphNode *ret = new UndirectedGraphNode(node->label);
        hash[node] = ret;
        queue<UndirectedGraphNode*> Q;
        Q.push(node);
        while(!Q.empty()) {
            UndirectedGraphNode*p = Q.front();
            Q.pop();
            for(auto &v : p->neighbors) {
                if(hash.find(v) == hash.end()) {
                    hash[v] = new UndirectedGraphNode(v->label);
                    Q.push(v);
                }
                hash[p]->neighbors.push_back(hash[v]);
            }
        }
        return ret;
    }
};
//////////////////////////////////////////////////////////////////////////
// 132.Palindrome Partitioning II
class Solution {
public:
	int minCut(string s) {
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
// P(i,j) = S(i)==S(j) && P(i+1,j-1)
// scan table P with i=n-1:0, j=i:n-1
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
		int n = s.size();
		vector<vector<bool>> P(n,vector<bool>(n,false));
		for(int i=n-1; i>=0; i--) {
			P[i][i] = true;
			for(int j=i+1; j<n; j++) {
				if (s[i]==s[j] && (j-i<3 || P[i+1][j-1]))
					P[i][j] = true;
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
        maximum = 0;
        travel(root, 0);
        return maximum;
    }
    int maximum;
};
// iteratively
class Solution {
public:
	int maxDepth(TreeNode *root) {
		int maximum = 0;
		stack<TreeNode*> s;
		TreeNode* r = root;
		int d = 0;
		while(true) {
			if (r != NULL) {
				s.push(r);
				if(r->left == NULL && r->right == NULL)
					maximum = max(maximum, int(s.size()));
				r = r->left;
			} else {
				while(!s.empty() && s.top()==NULL) s.pop();
				if(s.empty()) break;
				r = s.top();
				r = r->right;
				s.pop();
				s.push(NULL); // push dummy
			}
		}
		return maximum;
	}
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
//*recursively build left and right tree
// http://fisherlei.blogspot.com/2013/03/leetcode-unique-binary-search-trees-ii.html
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
	vector<TreeNode*> generate(int l, int r) {
		vector<TreeNode*> subTree;
		if(l>r) {
			subTree.push_back(NULL);
			return subTree;
		}
		for(int i=l; i<=r; i++) {
			vector<TreeNode*> left = generate(l, i-1);
			vector<TreeNode*> right = generate(i+1, r);
			for(int j=0; j<left.size(); j++)
			{
				for(int k=0; k<right.size(); k++)
				{
					TreeNode*node = new TreeNode(i);
					node->left = left[j];
					node->right = right[k];
					subTree.push_back(node);
				}
			}
		}
		return subTree;
	}
	vector<TreeNode *> generateTrees(int n) {
		if(n==0) return generate(1,0);
		return generate(1, n);
	}
};
//////////////////////////////////////////////////////////////////////////
// 94.Binary Tree Inorder Traversal
//*iteratively
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
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode* r = root;
        while(true) {
            if (r != NULL) {
                s.push(r);
                r = r->left;
            } else {
                if(s.empty()) break;
                r = s.top();
                s.pop();
                ret.push_back(r->val);
                r = r->right;
            }
        }
        return ret;
    }
};

//////////////////////////////////////////////////////////////////////////
// 93.Restore IP Addresses
// DFS
class Solution {
public:
	void DFS(string&s, int k, string path, vector<string>&ret, int d) {
		if (s.size()-k > (4-d)*3) return;
		if (s.size()-k < (4-d)) return;
		if (k==s.size() && d==4) {
			path.pop_back();
			ret.push_back(path);
			return;
		}
		int ch = 0;
		for(int i=k; i<k+3; i++) {
			ch = ch*10 + s[i] - '0';
			if (ch<=255) {
				path.push_back(s[i]);
				DFS(s, i+1, path+'.', ret, d+1);
			}
			if (ch == 0) break;
		}
	}
	vector<string> restoreIpAddresses(string s) {
		vector<string> ret;
		string path;
		DFS(s, 0, path, ret, 0);
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 92.Reverse Linked List II
// how to be bug free only once?
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        ListNode h(0);
        h.next = head;
        ListNode* p1 = &h;
        ListNode* p2 = head;
        for(int i=0; i<m-1; i++)
            p1 = p1->next;
        for(int i=0; i<n; i++)
            p2 = p2->next;
        ListNode* tp = p1;
        p1 = p1->next;
        for(int i=0; i<=n-m; i++) {
            ListNode* t = p1->next;
            p1->next = p2;
            p2 = p1;
            p1 = t;
        }
        tp->next = p2;
        return h.next;
    }
};
//////////////////////////////////////////////////////////////////////////
// 90.Subsets II
//*DFS
class Solution {
public:
	void DFS(vector<int> &S, int k) {
		if(k==n) {
			ret.push_back(subset);
			return;
		}
		int m=1;
		for(; k+m<n && S[k]==S[k+m]; m++);
		for(int i=0; i<=m; i++) {
			DFS(S,k+m);
			subset.push_back(S[k]);
		}
		for(int i=0; i<=m; i++)
			subset.pop_back();
	}
	vector<vector<int> > subsetsWithDup(vector<int> &S) {
		n = S.size();
		ret.clear();
		subset.clear();
		sort(S.begin(), S.end());
		DFS(S, 0);
		return ret;
	}
	int n;
	vector<vector<int> > ret;
	vector<int> subset;
};
//////////////////////////////////////////////////////////////////////////
// 91.Decode Ways
// DP, a lot of cases
class Solution {
public:
	int numDecodings(string s) {
		int n = s.size();
		if (n==0 || s[0]=='0') return 0;
		vector<int> D(n+1,0);
		D[0] = D[1] = 1;
		for(int i=1; i<n; i++) {
			if (s[i]!='0')
				D[i+1] = D[i];
			else if(s[i-1] > '2' || s[i-1] < '1')
				return 0;
			int ch = (s[i-1]-'0')*10+s[i]-'0';
			if (ch <= 26 && ch >= 10)
				D[i+1] += D[i-1];

		}
		return D[n];
	}
};
//////////////////////////////////////////////////////////////////////////
// 89.Gray Code
// 

//////////////////////////////////////////////////////////////////////////
// 88.Merge Sorted Array
// Trivial merge, in-place
class Solution {
public:
	void merge(int A[], int m, int B[], int n) {
		int k = m+n-1;
		m--; n--;
		while(k>=0 && m>=0 && n>=0) {
			if(A[m] > B[n])
				A[k--] = A[m--];
			else
				A[k--] = B[n--];
		}
		while(k>=0 && m>=0)
			A[k--] = A[m--];
		while(k>=0 && n>=0)
			A[k--] = B[n--];
	}
};
//////////////////////////////////////////////////////////////////////////
// 87.Scramble String
// 

//////////////////////////////////////////////////////////////////////////
// 86.Partition List
// Straight forward
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        ListNode h(0);
        h.next = head;
        ListNode*lp = &h;
        ListNode*pp = &h;
        for(ListNode*p = head; p!=NULL; p=p->next) {
            if(p->val < x) {
                pp->next = p->next;
                p->next = lp->next;
                lp->next = p;
				lp = p;
            }
            pp = p;
        }
        return h.next;
    }
};
//////////////////////////////////////////////////////////////////////////
// 85.Maximal Rectangle
// DP, Like 4.4 in dynamic_programming? No! here is Rectangle, not square

//////////////////////////////////////////////////////////////////////////
// 84.Largest Rectangle in Histogram
// http://www.geeksforgeeks.org/largest-rectangle-under-histogram/
// O(n)
class Solution {
public:
	int largestRectangleArea(vector<int> &h) {
		stack<int> p;
		int i = 0, m = 0;
		h.push_back(0);
		while(i < h.size()) {
			if(p.empty() || h[p.top()] <= h[i])
				p.push(i++);
			else {
				int t = p.top();
				p.pop();
				m = max(m, h[t] * (p.empty() ? i : i - p.top() - 1 ));
			}
		}
		return m;
	}
};
//////////////////////////////////////////////////////////////////////////
// 83.Remove Duplicates from Sorted List
// Sorted List is trival
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if(head==NULL) return head;
        ListNode* cur = head->next;
        ListNode* pre = head;
        while(cur!=NULL) {
            if(pre->val == cur->val) {
                pre->next = cur->next;
                delete cur;
            } else 
                pre = cur;
            cur = pre->next;
        }
        return head;
    }
};
//////////////////////////////////////////////////////////////////////////
// 82.Remove Duplicates from Sorted List II
// Sorted List is trival
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode h(0);
        h.next = head;
        ListNode* cur = head;
        ListNode* pre = &h;
        while(cur!=NULL && cur->next!=NULL) {
            if(cur->val == cur->next->val) {
                int val = cur->val;
                while(cur!=NULL && cur->val == val) {
                    pre->next = cur->next;
                    delete cur;
                    cur = pre->next;
                }
            } else {
                pre = cur;
                cur = pre->next;
            }
        }
        return h.next;
    }
};
//////////////////////////////////////////////////////////////////////////
// 81.Search in Rotated Sorted Array II
// refer to 33.

//////////////////////////////////////////////////////////////////////////
// 80.Remove Duplicates from Sorted Array II
// refer to 26.

//////////////////////////////////////////////////////////////////////////
// 79.Word Search
// DFS
class Solution {
public:
	bool DFS(vector<vector<char> > &board, int i, int j, string word, int k) {
		if(board[i][j]!=word[k]) return false;
		if(k==l-1) return true;
		char tmp = board[i][j];
		board[i][j] = '$';
		if(i-1>=0 && DFS(board,i-1,j,word,k+1)) return true;
		if(j-1>=0 && DFS(board,i,j-1,word,k+1)) return true;
		if(i+1< m && DFS(board,i+1,j,word,k+1)) return true;
		if(j+1< n && DFS(board,i,j+1,word,k+1)) return true;
		board[i][j] = tmp;
		return false;
	}
	bool exist(vector<vector<char> > &board, string word) {
		l=word.size();
		if(l==0) return true;
		m=board.size();
		if(m==0) return false;
		n=board[0].size();
		if(n==0) return false;
		for(int i=0; i<m; i++)
			for(int j=0; j<n; j++)
				if(DFS(board,i,j,word,0))
					return true;
		return false;
	}
	int m,n,l;
};
//////////////////////////////////////////////////////////////////////////
// 78.Subsets
// DFS
class Solution {
public:
	void DFS(vector<int> &S, int k) {
		if(k==n) {
			ret.push_back(subset);
			return;
		}
		DFS(S,k+1);
		subset.push_back(S[k]);
		DFS(S,k+1);
		subset.pop_back();
	}
	vector<vector<int> > subsets(vector<int> &S) {
		n = S.size();
		ret.clear();
		subset.clear();
		sort(S.begin(), S.end());
		DFS(S, 0);
		return ret;
	}
	int n;
	vector<vector<int> > ret;
	vector<int> subset;
};
//////////////////////////////////////////////////////////////////////////
// 77.Combinations
//*
class Solution {
public:
	void combine(int i, int n, int k, vector<int>&p) {
		for(; i<=n; i++) {
			p.push_back(i);
			if(k==1) {
				ret.push_back(p);
			} else {
				combine(i+1, n, k-1, p);
			}
			p.pop_back();
		}
	}
	vector<vector<int> > combine(int n, int k) {
		ret.clear();
		vector<int> path;
		combine(1, n, k, path);
		return ret;
	}
	vector<vector<int>> ret;
};
//////////////////////////////////////////////////////////////////////////
// 76.Minimum Window Substring
//*
class Solution {
public:
	string minWindow(string S, string T) {
		vector<int> cn(256,0);
		for(auto &c : T) cn[c]++;
		int n=S.size();
		int m=T.size();
		int count=0;
		int minimum=n;
		int begin=0;
		vector<int> wcn(256,0);
		for(int i=0,k=0; k<n; k++) {
			if(cn[S[k]] == 0) continue;
			if(wcn[S[k]] < cn[S[k]]) count++;
			wcn[S[k]]++;
			if (count == m) {
				for(; cn[S[i]]==0 || wcn[S[i]] > cn[S[i]]; i++)
					if(wcn[S[i]] > cn[S[i]])
						wcn[S[i]]--;
				if(minimum > k-i+1) {
					minimum = k-i+1;
					begin = i;
				}
			}
		}
		return count<m? "" : S.substr(begin, minimum);
	}
};
//////////////////////////////////////////////////////////////////////////
// 75.Sort Colors
class Solution {
public:
	void sortColors(int A[], int n) {
		int pl=0, pr=n-1;
		for(int i=0; i<=pr; ) {
			if(A[i]==0)
				swap(A[i++],A[pl++]);
			else if(A[i]==2)
				swap(A[i],A[pr--]);
			else
				i++;
		}
	}
};
//////////////////////////////////////////////////////////////////////////
// 74.Search a 2D Matrix 
class Solution {
public:
	bool bsearch(vector<vector<int> > &matrix, int l, int r, int t) {
		if(l>r) return false;
		int mid=(r+l)/2;
		int i = mid/n;
		int j = mid%n;
		if(matrix[i][j]==t) return true;
		else if(matrix[i][j] > t)
			return bsearch(matrix,l,mid-1,t);
		else
			return bsearch(matrix,mid+1,r,t);
	}
	bool searchMatrix(vector<vector<int> > &matrix, int target) {
		m=matrix.size();
		if(m==0) return false;
		n=matrix[0].size();
		if(n==0) return false;
		int k=m*n;
		return bsearch(matrix,0,k-1,target);
	}
	int m,n;
};
//////////////////////////////////////////////////////////////////////////
// 73.Set Matrix Zeroes 
class Solution {
public:
	void setZeroes(vector<vector<int> > &matrix) {
		int m=matrix.size();
		if(m==0) return;
		int n=matrix[0].size();
		if(n==0) return;
		bool m0=false, n0=false;
		for(int i=0; i<m; i++) if(matrix[i][0]==0) m0=true;
		for(int j=0; j<n; j++) if(matrix[0][j]==0) n0=true;
		for(int i=1; i<m; i++)
			for(int j=1; j<n; j++)
				if(matrix[i][j]==0)
					matrix[i][0]=matrix[0][j]=0;
		for(int i=1; i<m; i++)
			for(int j=1; j<n; j++)
				if(matrix[i][0]==0 || matrix[0][j]==0)
					matrix[i][j]=0;
		if(m0) for(int i=0; i<m; i++) matrix[i][0]=0;
		if(n0) for(int j=0; j<n; j++) matrix[0][j]=0;
	}
};
//////////////////////////////////////////////////////////////////////////
// 72.Edit Distance
// O(m*n) space
class Solution {
public:
	int minDistance(string word1, string word2) {
		int m=word1.size();
		int n=word2.size();
		vector<vector<int> > E(m+1,vector<int>(n+1,0));
		for(int i=0; i<=m; i++) E[i][0]=i;
		for(int j=0; j<=n; j++) E[0][j]=j;
		for(int i=1; i<=m; i++)
			for(int j=1; j<=n; j++)
				E[i][j] = min(min(E[i][j-1],E[i-1][j])+1,E[i-1][j-1]+(word1[i-1]==word2[j-1]?0:1));
		return E[m][n];
	}
};
// O(min(m,n)) space
class Solution {
public:
	int minDistance(string word1, string word2) {
		int m=word1.size();
		int n=word2.size();
		if(n>m) {
			swap(m,n); swap(word1,word2);
		}
		vector<int> E(n+1,0);
		for(int j=0; j<=n; j++) E[j]=j;
		for(int i=1; i<=m; i++) {
			int lt=i-1; E[0]=i;
			for(int j=1; j<=n; j++) {
				int tmp = min(min(E[j],E[j-1])+1,lt+(word1[i-1]==word2[j-1]?0:1));
				lt=E[j]; E[j]=tmp;
			}
		}
		return E[n];
	}
};
//////////////////////////////////////////////////////////////////////////
// 71.Simplify Path
//*
class Solution {
public:
	string simplifyPath(string path) {
		int n=path.size();
		vector<string> S;
		string name;
		for(int i=0; i<n; ) {
			int m=0;
			for(; i<n; i++) {
				if(path[i]=='.')
					m++;
				else if(path[i]=='/') {
					if(m>=2 && !S.empty()) S.pop_back();
					m=0;
				} else
					break;
			}
			if(i==n) {
				if(m>=2 && !S.empty()) S.pop_back();
				break;
			}
			while(m--) name.push_back('.');
			for(; i<n && path[i]!='.' && path[i]!='/'; i++) name.push_back(path[i]);
			S.push_back(name);
			name.clear();
		}
		for(auto &s:S)
			name.append('/'+s);
		return S.empty()? "/":name;
	}
};
//////////////////////////////////////////////////////////////////////////
// 70.Climbing Stairs 
class Solution {
public:
	int climbStairs(int n) {
		if(n<=2) return n;
		int w_1 = 2;
		int w_2 = 1;
		int ret = 0;
		for(int i=3; i<=n; i++) {
			ret = w_1+w_2;
			w_2 = w_1;
			w_1 = ret;
		}
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 69.Sqrt(x)
class Solution {
public:
	int sqrt(int x) {
		if(x<2) return x;
		long long l=0;
		long long r=x;
		while(l<=r) {
			long long m = (l+r)/2;
			if(m*m>x)
				r=m-1;
			else if(m*m<x)
				l=m+1;
			else
				return m;
		}
		return r;
	}
};
//////////////////////////////////////////////////////////////////////////
// 68.Text Justification 
class Solution {
public:
	vector<string> fullJustify(vector<string> &words, int L) {
		int n = words.size();
		vector<string> ret;
		if(n==0) return ret;
		vector<string> S;
		string line;
		int k=0;
		while(1) {
			int count = words[k].size();
			S.push_back(words[k]);
			for(k++; k<n && count+1+words[k].size()<=L; k++) {
				S.push_back(words[k]);
				count+=(1+words[k].size());
			}
			if(k==n) { // last line
				for(auto &s:S) line.append(s+' ');
				line.resize(L,' ');
				ret.push_back(line);
				break;
			}
			int nitv = S.size()-1;
			int nspace = L-count+nitv;
			int u,v;
			if(nitv == 0) {
				u = 0; v = 0;
			} else {
				u = nspace/nitv; v = nspace%nitv;
			}
			int i=0;
			for(; i<v; i++) line.append(S[i]).append(u+1,' ');
			for(; i<nitv; i++) line.append(S[i]).append(u,' ');
			line.append(S[i]);
			if(nitv == 0) line.resize(L,' ');
			ret.push_back(line);
			S.clear();
			line.clear();
		}
		return ret;
	}
};
//////////////////////////////////////////////////////////////////////////
// 67.Plus One
class Solution {
public:
	vector<int> plusOne(vector<int> &digits) {
		// Note: The Solution object is instantiated only once and is reused by each test case.
		int n=digits.size();
		for(int i=n-1; i>=0; i--) {
			digits[i]++;
			if(digits[i]<10) return digits;
			else digits[i]=0;
		}
		digits.insert(digits.begin(),1);
		return digits;
	}
};
//////////////////////////////////////////////////////////////////////////
// 66.Valid Number 
//*http://discuss.leetcode.com/questions/241/valid-number
class Solution {
public:
	bool isNumber(const char *s) {
		enum InputType {
			INVALID,    // 0
			SPACE,      // 1
			SIGN,       // 2
			DIGIT,      // 3
			DOT,        // 4
			EXPONENT,   // 5
			NUM_INPUTS  // 6
		};
		int transitionTable[][NUM_INPUTS] = {
			-1,  0,  3,  1,  2, -1,     // next states for state 0
			-1,  8, -1,  1,  4,  5,     // next states for state 1
			-1, -1, -1,  4, -1, -1,     // next states for state 2
			-1, -1, -1,  1,  2, -1,     // next states for state 3
			-1,  8, -1,  4, -1,  5,     // next states for state 4
			-1, -1,  6,  7, -1, -1,     // next states for state 5
			-1, -1, -1,  7, -1, -1,     // next states for state 6
			-1,  8, -1,  7, -1, -1,     // next states for state 7
			-1,  8, -1, -1, -1, -1,     // next states for state 8
		};
		int state = 0;
		while (*s != '\0') {
			InputType inputType = INVALID;
			if (isspace(*s))
				inputType = SPACE;
			else if (*s == '+' || *s == '-')
				inputType = SIGN;
			else if (isdigit(*s))
				inputType = DIGIT;
			else if (*s == '.')
				inputType = DOT;    
			else if (*s == 'e' || *s == 'E')
				inputType = EXPONENT;

			// Get next state from current state and input symbol
			state = transitionTable[state][inputType];

			// Invalid input
			if (state == -1) return false;
			else ++s;
		}
		// If the current state belongs to one of the accepting (final) states,
		// then the number is valid
		return state == 1 || state == 4 || state == 7 || state == 8;
	}
};
//////////////////////////////////////////////////////////////////////////
// 65.Add Binary 
class Solution {
public:
	string addBinary(string a, string b) {
		int n = a.size();
		int m = b.size();
		if(m>n) {swap(m,n); swap(a,b);}
		char s=0;
		for(int i=1; i<=m; i++) {
			char ai = a[n-i]-'0';
			char bi = b[m-i]-'0';
			char t = (ai^bi^s)+'0';
			s = (s==0?(ai&bi):(ai|bi));
			a[n-i] = t;
		}
		for(int i=m+1; i<=n; i++) {
			if(s==1 && a[n-i]=='1')
				a[n-i] = '0';
			else {
				a[n-i] += s;
				s=0;
				break;
			}
		}
		if(s==1)
			a.insert(a.begin(),'1');
		return a;
	}
}; 
//////////////////////////////////////////////////////////////////////////
// 64.Merge Two Sorted Lists

//////////////////////////////////////////////////////////////////////////
// 63.Minimum Path Sum
class Solution {
public:
	int minPathSum(vector<vector<int> > &grid) {
		// Note: The Solution object is instantiated only once and is reused by each test case.
		int m = grid.size();
		if(m==0) return 0;
		int n = grid[0].size();
		for(int i=1; i<m; i++) grid[i][0]+=grid[i-1][0];
		for(int j=1; j<n; j++) grid[0][j]+=grid[0][j-1];
		for(int i=1; i<m; i++)
			for(int j=1; j<n; j++)
				grid[i][j] += min(grid[i-1][j],grid[i][j-1]);
		return grid[m-1][n-1];
	}
};
//////////////////////////////////////////////////////////////////////////
// Permutations 
//*
class Solution {
public:
	void permute(int k,vector<int> &num) {
		if (k<num.size()) {
			for(int i=k; i<num.size(); i++) {
				swap(num[i], num[k]);
				permute(k+1, num);
				swap(num[i], num[k]);
			}
		} else {
			ret.push_back(num);
		}
	}
	vector<vector<int> > permute(vector<int> &num) {
		ret.clear();
		permute(0, num);
		return ret;
	}
	vector<vector<int> > ret;
};