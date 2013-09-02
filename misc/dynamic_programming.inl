namespace misc{

	template <typename T>
	void rod_cutting_bottomup( T *r, int *s, T *p, int n )
	{
		for (int i=0; i<n; i++) {
			r[i] = p[i];
			s[i] = i;
			for (int j=0; j<i; j++) {
				if (r[i] < p[j]+r[i-j-1]) {
					r[i] = p[j]+r[i-j-1];
					s[i] = j;
				}
			}
		}
	}

	template <typename T, typename Fun>
	void rod_cutting_reconstruct( T *r, int *s, int n, Fun fn )
	{ // Reconstruct
		for (int i=n-1; i>=0;) {
			int l = s[i]+1;
			fn(l);
			i=i-l;
		}
	}

	template <typename T, typename Fun>
	T rod_cutting( T *p, int n, Fun fn )
	{ // Reconstruct
		std::unique_ptr<T[]> r(new T[n]);
		std::unique_ptr<int[]> s(new int[n]);
		rod_cutting_bottomup(r.get(), s.get(), p, n);
		rod_cutting_reconstruct(r.get(), s.get(), n, fn);
		return r[n-1];
	}

	template <typename T>
	T rod_cutting( T *p, int n )
	{ // Reconstruct
		std::unique_ptr<T[]> r(new T[n]);
		std::unique_ptr<int[]> s(new int[n]);
		rod_cutting_bottomup(r.get(), s.get(), p, n);
		return r[n-1];
	}

} // namespace misc
