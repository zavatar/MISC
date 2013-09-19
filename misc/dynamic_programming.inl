namespace misc{

	unsigned int fibonacci_n( int n )
	{
		unsigned int f[2];
		f[0]=0; f[1]=1;
		if (n == 0) return f[0];
		else if (n == 1) return f[1];
		int b = 0;
		for (int i=1; i<n; i++, b=1-b)
			f[b] = f[b] + f[1-b];
		return f[1-b];
	}

	template <typename T, typename Fun>
	T rod_cutting( T *p, int n, Fun fn )
	{
		std::vector<T> r(n+1);
		std::vector<int> s(n+1);
		for (int i=0; i<=n; i++) {
			r[i] = p[i];
			s[i] = i;
			for (int j=1; j<i; j++) {
				if (r[i] < p[j]+r[i-j]) {
					r[i] = p[j]+r[i-j];
					s[i] = j;
				}
			}
		}
		// Reconstruct
		for (int i=n; i>0; i-=s[i])
			fn(s[i]);
		return r[n];
	}

	template <typename T, typename Fun>
	int LIS( T *x, int n, Fun fn )
	{
		std::vector<int> lis(n, 1);
		std::vector<int> s(n, -1);
		int idx = 0;
		for (int i=1; i<n; i++) {
			for (int j=0; j<i; j++) {
				if (lis[i] < lis[j]+1 && x[j] < x[i]) {
					lis[i] = lis[j]+1;
					s[i] = j;
				}
			}
			if (lis[i]>lis[i-1])
				idx = i;
		}
		// Reconstruct
		for (int i=idx; i>=0 ; i=s[i])
			fn(x[i]);
		return lis[idx];
	}

	template <typename T, typename Fun>
	int fastLIS( T *x, int n, Fun fn )
	{
		std::vector<int> m(2, 0);
		std::vector<int> p(n, -1);
		int L = 1;
		for (int i=1; i<n; i++) {
			if (x[i] < x[m[1]]) // smallest
				m[1] = i;
			else if (x[i] > x[m[L]]) { // biggest
				m.push_back(i);
				p[i] = m[L];
				L++;
			} else {
				// Binary Search biggest j, s.t. x[m[j]]<x[i]
				int l=1, r=L, j=0;
				while (l<=r) {
					int mid = l+(r-l)/2;
					if (x[i] < x[m[mid]])
						r = mid-1;
					else if (x[i] > x[m[mid]])
						l = mid+1;
					else {
						j = mid-1;
						break;
					}
				}
				if (l>r) j = r;
				m[j+1] = i;
				p[i] = m[j];
			}
		}
		// Reconstruct
		for (int k=m[L]; k>=0; k=p[k])
			fn(x[k]);
		return L;
	}

	template <typename T, typename Fun>
	int LCS( T *x, int m, T *y, int n, Fun fn )
	{
		std::vector<std::vector<int>> L(m+1, std::vector<int>(n+1));
		// 1:left/right, 2:left_up/right_down, 3:up/down
		std::vector<std::vector<char>> F(m+1, std::vector<char>(n+1));
		for (int i=0; i<=m; i++) {
			for (int j=0; j<=n; j++) {
				if (i==0 || j==0)
					L[i][j] = F[i][j] = 0;
				else if (x[i-1] == y[j-1]) {
					L[i][j] = L[i-1][j-1] + 1;
					F[i][j] = 2;
				} else if (L[i-1][j] > L[i][j-1]) {
					L[i][j] = L[i-1][j];
					F[i][j] = 3;
				} else {
					L[i][j] = L[i][j-1];
					F[i][j] = 1;
				}
			}
		}
		for (int i=m,j=n; i>0 && j>0; ) {
			char f = F[i][j];
			if (f == 1) j--;
			else if (f == 2) {
				fn(i-1, j-1); i--; j--;
			} else if (f == 3) i--;
			else break;
		}
		return L[m][n];
	}

	template <typename T, typename Fun>
	int edit_distance( T *x, int m, T *y, int n, Fun fn )
	{
		std::vector<std::vector<int>> E(m+1, std::vector<int>(n+1));
		// 1:left/right, 2:left_up/right_down, 3:up/down
		std::vector<std::vector<char>> F(m+1, std::vector<char>(n+1));
		const int D = 1;
		const int R = 1;
		const int I = 1;
		for (int i=0; i<=m; i++) {
			for (int j=0; j<=n; j++) {
				if (i==0) {
					E[0][j] = j;
					F[0][j] = 0;
				} else if (j==0) {
					E[i][0] = i;
					F[i][0] = 0;
				} else {
					int u = E[i-1][j] + D;
					int l = E[i][j-1] + I;
					int lu= E[i-1][j-1] + (x[i-1]==y[j-1]?0:R);
					if (u < lu) {
						if (u < l) { // u
							E[i][j] = u;
							F[i][j] = 3;
						} else { // l
							E[i][j] = l;
							F[i][j] = 1;
						}
					} else { // lu <= u
						if (l < lu) { // l
							E[i][j] = l;
							F[i][j] = 1;
						} else { // lu
							E[i][j] = lu;
							F[i][j] = 2;
						}
					}
				}
			}
		}
		for (int i=m,j=n; i>0 && j>0; ) {
			char f = F[i][j];
			if (f == 1) j--;
			else if (f == 2) {
				fn(i-1, j-1); i--; j--;
			} else if (f == 3) i--;
			else break;
		}
		return E[m][n];
	}

	template <typename T>
	int palindrome_partitioningOn3( T *x, int n )
	{
		std::vector<std::vector<int>> M(n,std::vector<int>(n, 0));
		for (int l=1; l<n; l++) {
			for (int i=0; i<n-l; i++) {
				int j=i+l;
				if (x[i] == x[j] && M[i+1][j-1] == 0)
					M[i][j] = 0;
				else {
					M[i][j] = n;
					for (int k=i; k<j; k++) {
						M[i][j] = std::min(M[i][k]+M[k+1][j]+1, M[i][j]);
					}
				}
			}
		}
		return M[0][n-1];
	}

	template <typename T>
	int palindrome_partitioningOn2( T *x, int n )
	{
		if (n<2) return 0;
		std::vector<int> M(n,0);
		std::vector<std::vector<bool>> P(n,std::vector<bool>(n,false));
		for(int i=1; i<n; i++) {
			if (x[0] == x[i] && (i<3 || P[1][i-1]))
				M[i] = 0;
			else {
				M[i] = std::min(i, M[i-1]+1);
				for (int k=i-1; k>0; k--) {
					if (x[k] == x[i] && (i-k<3 || P[k+1][i-1])) {
						P[k][i] = true;
						M[i] = std::min(M[i], M[k-1]+1);
					}
				}  
			}
		}
		return M[n-1];
	}

} // namespace misc
