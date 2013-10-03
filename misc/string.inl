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

	template <typename T, typename U>
	void Huffman( std::vector<std::pair<T, U>> &freq,
		std::vector<std::string> &codes )
	{
		struct node {
			node *l;
			union {
				node *r;
				int id;
			};
			node(node*_l,node*_r):l(_l),r(_r){}
			node(int i):l(nullptr),id(i){}
		};
		typedef std::pair<U,node*> heap_elm;
		std::priority_queue<heap_elm,std::vector<heap_elm>,std::greater<heap_elm>> MinHeap;

		for(size_t i=0; i<freq.size(); i++)
			MinHeap.emplace(freq[i].second, new node(i));
		
		node* root = nullptr;
		// build tree
		while(!MinHeap.empty()) {
			heap_elm p1 = MinHeap.top();
			MinHeap.pop();
			if (MinHeap.empty()) {
				root = p1.second; break;
			}
			heap_elm p2 = MinHeap.top();
			MinHeap.pop();
			MinHeap.emplace(p1.first+p2.first, new node(p1.second,p2.second));
		}

		// traverse tree
		codes.resize(freq.size());
		std::string code;
		std::function<void(node*)> fun = [&](node* r){
			if(r->l == nullptr) {
				codes[r->id] = code;
				return;
			}
			code.append("0");
			fun(r->l);
			code.back()='1';
			fun(r->r);
			code.pop_back();
		};
		fun(root);
	}

} // namespace misc
