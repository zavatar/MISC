namespace misc{

	template <typename T>
	void insertion_sort_n(T *a, int n)
	{
		for (int i=1; i<n; i++) {
			T t = a[i];
			int j = i;
			for (; j>0 && a[j-1]>t; j--) // Maybe Binary-Search, But still O(n) moves.
				a[j] = a[j-1];
			a[j] = t;
		}
	}

	template <typename T>
	void shell_sort_n(T *a, int n)
	{
		// Generate Knuth's sequence.
		// http://stackoverflow.com/questions/2539545/fastest-gap-sequence-for-shell-sort
		std::vector<int> s;
		for (int k=1; k<n; k=3*k+1)
			s.push_back(k);
		std::reverse(s.begin(), s.end());

		std::for_each(s.begin(), s.end(), [&a, n](int h){
			// Do an insertion sort for each gap size.
			for (int i=h; i<n; i++) {
				T t = a[i];
				int j = i;
				for (; j>=h && a[j-h]>t; j-=h)
					a[j] = a[j-h];
				a[j] = t;
			}
		});
	}

	template <typename T>
	void __merge_sort(T *l, T *r)
	{
		if (l < r)
		{
			T *m = l+(r-l)/2;
			__merge_sort(l, m);
			__merge_sort(m+1, r);
			std::inplace_merge(l, m+1, r+1);
		}
	}

	template <typename T>
	void merge_sort_n(T *a, int n)
	{
		__merge_sort(a, a+n-1);
	}

	template <typename T>
	void heap_sort_n(T *a, int n)
	{
		T *e = a+n;
		std::make_heap(a, e); //O(3*n)
		std::sort_heap(a, e); //O(nlgn)
	}

	inline int heap_parent(int k) { return (k-1)/2; }
	inline int heap_left(int p) { return 2*p+1; }
	inline int heap_right(int p) { return 2*p+2; }

	template <typename T>
	void increase_maxheap(T *a, int k, T val, int top = 0)
	{
		assert(val >= a[k]);
		for (a[k] = val; k>top && a[heap_parent(k)] < a[k]; k = heap_parent(k))
			std::swap(a[k], a[heap_parent(k)]);
	}

	template <typename T>
	void push_maxheap(T *a, int n, T val)
	{
		a[n] = val;
		increase_maxheap(a, n, val);
	}

	// non-recursive version
	template <typename T>
	void max_heapify(T *a, int n, int k)
	{
		int top = k;
		T val = a[k];
		while (1) {
			int l = heap_left(k);
			int r = heap_right(k);
			int maxi;
			if (l >= n) break;
			else if (r >= n || a[l] > a[r]) maxi = l;
			else maxi = r;
			a[k] = a[maxi];
			k = maxi;
		}
		a[k] = 0;
		increase_maxheap(a, k, val, top);
	}

	// recursive version
	template <typename T>
	void max_heapify_r(T *a, int n, int k)
	{
		int l = heap_left(k);
		int r = heap_right(k);
		int maxi;
		if (l < n && a[l] > a[k])
			maxi = l;
		else maxi = k;
		if (r < n && a[r] > a[maxi])
			maxi = r;
		if (maxi != k) {
			std::swap(a[k], a[maxi]);
			max_heapify_r(a, n, maxi);
		}
	}

	template <typename T>
	void build_maxheap(T *a, int n)
	{
		for (int i=n/2-1; i >= 0; i--)
			max_heapify(a, n, i); // max_heapify_r(a, n, i);
	}

	template <typename T>
	void sort_maxheap(T *a, int n)
	{
		int n0 = n;
		for (int i=n-1; i>0; i--) {
			std::swap(a[0], a[i]);
			max_heapify(a, --n0, 0); // max_heapify_r(a, --n0, 0);
		}
	}

	template <typename T>
	void heap_sort_n_1(T *a, int n)
	{
		build_maxheap(a, n); //O(3*n)
		sort_maxheap(a, n); //O(nlgn)
	}

	template <typename T>
	void __quicksort(T *l, T *r)
	{
		if (l < r) {
			T p = *r;
			T *m = std::partition(l, r, [p](T &v){ return v<p; });
			std::swap(*m, *r);
			__quicksort(l, m-1);
			__quicksort(m+1, r);
		}
	}

	template <typename T>
	void quicksort_n(T *a, int n)
	{
		__quicksort(a, a+n-1);
	}

	template <typename T>
	bool binary_search(T *l, T *r, T val)
	{
		while (l <= r) {
			T *m = l+(r-l)/2;
			if (*m == val) return true;
			else if (*m < val) l = m+1; // turn right
			else r = m-1; // turn left
		}
		return false;
	}

	template <typename T>
	bool binary_search_n(T *a, int n, T val)
	{
		return binary_search(a, a+n-1, val);
	}

	template <typename T>
	void __nth_element(T *l, T *r, int nth)
	{
		T *first = l;
		while (l <= r) {
			T p = *r;
			T *m = std::partition(l, r, [p](T &v){ return v<p; });
			std::swap(*m, *r);
			if (m-first == nth) return;
			else if (m-first < nth) l = m+1; // turn right
			else r = m-1; // turn left
		}
	}

	template <typename T>
	int __bfprt_partition(T *l, T *r)
	{
		const int G = 5; const int M = 2;
		T *p = l;
		int k = 0;
		for (; p+G <= r; p+=G) {
			insertion_sort_n(p, G);
			std::swap(l[k++], p[M]);
		}
		insertion_sort_n(p, r-p+1);
		std::swap(l[k++], p[(r-p)/2]);
		return k-1;
	}

	template <typename T>
	void __nth_element_bfprt(T *l, T *r, int nth)
	{
		if (r-l >= 16) {
			int p = __bfprt_partition(l, r);
			__nth_element_bfprt(l, l+p, p/2);
			std::swap(l[p/2], *r);
			T *m = std::partition(l, r, [r](T &v){ return v<*r; });
			std::swap(*m, *r);
			if (m-l < nth)
				__nth_element_bfprt(m+1, r, nth-(m-l+1));
			else if (m-l > nth)
				__nth_element_bfprt(l, m-1, nth);
		} else
			insertion_sort_n(l, r-l+1);
		//__nth_element(l, r, nth);
	}

	template <typename T>
	void nth_element_n(T *a, int n, int nth)
	{
		//__nth_element(a, a+n-1, nth);
		__nth_element_bfprt(a, a+n-1, nth);
	}

	template <typename T>
	T nth_selection_n(T *a, int n, int nth)
	{
		//std::nth_element(a, a+nth, a+n);
		nth_element_n(a, n, nth);
		return a[nth];
	}

} // namespace misc
