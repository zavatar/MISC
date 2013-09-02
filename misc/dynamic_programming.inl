namespace misc{

	template <typename T>
	void rod_cutting_bottomup( T *r, int *s, T *p, int n )
	{
		// r[i] = max(p[j]+r[i-j]), j = [1,i]
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
	void rod_cutting_reconstruct( T *r, int *s, int n, Fun fn )
	{ // Reconstruct
		for (int i=n; i>0; i-=s[i])
			fn(s[i]);
	}

	template <typename T, typename Fun>
	T rod_cutting( T *p, int n, Fun fn )
	{ // Reconstruct
		std::unique_ptr<T[]> r(new T[n+1]);
		std::unique_ptr<int[]> s(new int[n+1]);
		rod_cutting_bottomup(r.get(), s.get(), p, n);
		rod_cutting_reconstruct(r.get(), s.get(), n, fn);
		return r[n];
	}

	template <typename T>
	T rod_cutting( T *p, int n )
	{ // Reconstruct
		std::unique_ptr<T[]> r(new T[n+1]);
		std::unique_ptr<int[]> s(new int[n+1]);
		rod_cutting_bottomup(r.get(), s.get(), p, n);
		return r[n];
	}

} // namespace misc
