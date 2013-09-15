namespace misc{

	template <typename T>
	void LPS( T* p, int* lps, int m )
	{
		lps[0] = 0;
		int l = 0;
		for (int i=1; i<m;) {
			if (p[i] == p[l])
				lps[i++] = ++l;
			else if (l == 0)
				lps[i++] = 0;
			else
				l = lps[l-1];
		}
	}

	template <typename T, typename Fun>
	void KMPSearch( T* s, int n, T* p, int m, Fun fn )
	{
		std::vector<int> lps(m);
		LPS(p, &lps[0], m);
		int j=0;
		for (int i=0; i<n;) {
			if (s[i] == p[j]) {
				i++; j++;
				if (j == m) {
					fn(i-m);
					j = lps[j-1];
				}
			} else
				j==0?(i++):(j=lps[j-1]);
		}
	}

	MISC_FUNC_QUALIFIER bool ismatch( const char* s, const char* p, int n )
	{
		for(int i=0; i<n; i++)
			if(s[i] != p[i])
				return false;
		return true;
	}

	template <typename Fun>
	void RKSearch( const char* s, int n, const char* p, int m, Fun fn )
	{
		rabin_karp pat(p, m);
		rabin_karp txt(s, m);
		for (int i=0; i<n-m; i++) {
			if(pat.hash() == txt.hash() && ismatch(s+i, p, m))
				fn(i);
			txt.rehash(s[i+m]);
		}
		if(pat.hash() == txt.hash() && ismatch(s+n-m, p, m))
			fn(n-m);
	}


} // namespace misc
