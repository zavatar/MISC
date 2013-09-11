//Palindrome Partitioning II
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
// Palindrome Partitioning
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
// Surrounded Regions
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
// Sum Root to Leaf Numbers
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
// Longest Consecutive Sequence
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
// Word Ladder
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
// Word Ladder II
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

};