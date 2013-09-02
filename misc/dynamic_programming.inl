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

	template <typename T>
	void rod_cutting_bottomup( T *r, int *s, T *p, int n )
	{ // r[i] = max(p[j]+r[i-j]), j = [1,i]
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
	}

	template <typename T, typename Fun>
	T rod_cutting( T *p, int n, Fun fn )
	{
		std::unique_ptr<T[]> r(new T[n+1]);
		std::unique_ptr<int[]> s(new int[n+1]);
		rod_cutting_bottomup(r.get(), s.get(), p, n);
		// Reconstruct
		for (int i=n; i>0; i-=s[i])
			fn(s[i]);
		return r[n];
	}

	template <typename T>
	T rod_cutting( T *p, int n )
	{
		std::unique_ptr<T[]> r(new T[n+1]);
		std::unique_ptr<int[]> s(new int[n+1]);
		rod_cutting_bottomup(r.get(), s.get(), p, n);
		return r[n];
	}

	template <typename T>
	int LCS( T *x, int m, T *y, int n )
	{
		return 0;
	}

	template <typename T, typename Fun>
	int LIS( T *x, int n, Fun fn )
	{ // lis[i] = 1+max(lis[j]), x[j]<x[i]
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

	template <typename T>
	int fastLIS( T *x, int n )
	{
		if (n<1) return n;
		std::vector<int> m;
		std::vector<int> p;
		return fastLIS(m, p, x, n);
	}

	template <typename T, typename Fun>
	int fastLIS( T *x, int n, Fun fn )
	{
		std::vector<int> m;
		std::vector<int> p;
		int L = fastLIS(m, p, x, n);
		// Reconstruct
		for (int k=m[L]; k>=0; k=p[k])
			fn(x[k]);
		return L;
	}

	template <typename T>
	int fastLIS( std::vector<int> &m, std::vector<int> &p, T *x, int n )
	{
		m.resize(2, 0);
		p.resize(n, -1);
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
		return L;
	}

} // namespace misc
