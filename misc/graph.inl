namespace misc{

	GraphTemplate
	GraphHead Graph( int V )
	{
		root.resize(V);
	}

	GraphTemplate
	void GraphHead clear()
	{
		root.clear();
		clearkey();
	}

	GraphTemplate
	void GraphHead resize( int V )
	{
		root.resize(V);
	}

	GraphTemplate
	typename GraphHead color_type& GraphHead Color( id_type& v )
	{
		return root[v].color;
	}

	GraphTemplate
	_Key& GraphHead Key( id_type& v )
	{
		return root[v].key;
	}

	GraphTemplate
	bool GraphHead Visited( _Key v )
	{
		return visited(Id(v));
	}

	GraphTemplate
	bool GraphHead visited( id_type v )
	{
		return Color(v) != white;
	}

	GraphTemplate
	bool GraphHead visible( id_type v )
	{
		return Color(v) != invisible;
	}

	GraphTemplate
	void GraphHead clearColor()
	{
		_foreachVertex([&](id_type v){
			Color(v) = white;
		});		
	}

	GraphTemplate
	void GraphHead addVertex( _Key kv )
	{
		id_type v = addkey(kv);
		root.resize(std::max(v+1, id_type(root.size())));
		Key(v) = kv;
		Color(v) = white;
	}

	GraphTemplate
	void GraphHead connect( _Key ku, _Key kv, _Weight w, _Dist d )
	{
		id_type u = Id(ku);
		id_type v = Id(kv);

		root[u].adj[v] = Edge(w,d);
		if (_Dir::value)
			root[v].adj[u] = Edge(w,d);
	}

	GraphTemplate
	void GraphHead addEdge( _Key ku, _Key kv, _Weight w, _Dist d )
	{
		addVertex(ku);
		addVertex(kv);
		connect(ku, kv, w, d);
	}

	GraphTemplate
	void GraphHead updateEdge( _Key ku, _Key kv, _Weight w, _Dist d )
	{
		addVertex(ku);
		addVertex(kv);
		connect(ku, kv, w, d);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _foreachVertex( Fun fn )
	{
		for (id_type v=0; v<id_type(root.size()); v++)
			if (visible(v))
				fn(v);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead foreachAdj( _Key kv, Fun fn )
	{
		_foreachAdj(Id(kv), fn);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _foreachAdj( id_type v, Fun fn )
	{
		for (const auto &e : root[v].adj)
			fn(e.first);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _foreachAdjE( id_type v, Fun fn )
	{
		for (const auto &e : root[v].adj)
			fn(e.first, e.second);
	}

	GraphTemplate
	template <typename Fun>	
	void GraphHead _foreachEdge( Fun fn )
	{
		_foreachVertex([&](id_type v){
			_foreachAdjE(v, [&](id_type u, const Edge&e){
				fn(v, u, e);
			});
		});
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead BFS( Fun fn )
	{
		clearColor();
		_foreachVertex([&](id_type v){
			if(!visited(v))
				_BFS_visit(v, fn);
		});
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead BFS_visit( _Key ks, Fun fn )
	{
		id_type s = Id(ks);
		_BFS_visit(s, fn);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _BFS_visit( id_type s, Fun fn )
	{
		Color(s) = gray;
		fn(Key(s));
		std::queue<id_type> Q;
		Q.push(s);
		while (Q.size() != 0) {
			id_type v = Q.front();
			_foreachAdj(v, [&](id_type u){
				if (!visited(u)) {
					Color(u) = gray;
					fn(Key(u));
					Q.push(u);
				}
			});
			Color(v) = black;
			Q.pop();
		}
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead DFS( startFun sf, finishFun ff )
	{
		clearColor();
		_foreachVertex([&](id_type v){
			if(!visited(v))
				_DFS_visit(v, sf, ff);
		});
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead DFS_visit( _Key kv, startFun sf, finishFun ff )
	{
		id_type v = Id(kv);
		_DFS_visit(v, sf, ff);
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead _DFS_visit( id_type v, startFun sf, finishFun ff )
	{
		Color(v) = gray;
		sf(Key(v));
		_foreachAdj(v, [&](id_type u){
			if (!visited(u))
				_DFS_visit(u, sf, ff);
		});
		Color(v) = black;
		ff(Key(v));
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead topological_sort( Fun fn )
	{
		std::stack<_Key> S;
		DFS([](_Key){}, [&](_Key& v){S.push(v);});
		for (; S.size() != 0; S.pop())
			fn(S.top());
	}

	GraphTemplate
	void GraphHead transpose( Graph& gt )
	{
		gt.clear();
		gt.resize(root.size());
		_foreachEdge([&](id_type v, id_type u, const Edge &e){
			gt.addEdge(Key(u), Key(v));
		});
	}

	GraphTemplate
	void GraphHead SCC()
	{
		auto dummyfun = [](_Key){};
		auto printfun = [](_Key v){std::cout<<v<<'\t';};

		Graph gt;
		transpose(gt);

		topological_sort([&](_Key&k){
			if (!gt.Visited(k)) {
				gt.DFS_visit(k, printfun, dummyfun);
				printf("\n");
			}
		});
	}

	GraphTemplate
	template <typename Fun>
	_Weight GraphHead Kruskal_MST(Fun fn)
	{
		int V = root.size();
		std::vector<int> rank(V);
		std::vector<id_type> parent(V);

		boost::disjoint_sets<int*, id_type*> dsets(&rank[0], &parent[0]);
		_foreachVertex([&](id_type v){
			dsets.make_set(v);
		});

		typedef std::tuple<id_type, id_type, Edge> edge_type;
		std::vector<edge_type> edges;
		_foreachEdge([&](id_type v, id_type u, const Edge &e){
			edges.emplace_back(v, u, e);
		});
		std::sort(edges.begin(), edges.end(),
			[](const edge_type&l, const edge_type&r){
				return std::get<2>(l).w < std::get<2>(r).w;
		});

		_Weight ret = 0;
		for (const auto &t : edges) {
			id_type v = std::get<0>(t);
			id_type u = std::get<1>(t);
			id_type vp = dsets.find_set(v);
			id_type up = dsets.find_set(u);
			if (vp != up) {
				fn(Key(v), Key(u));
				ret += std::get<2>(t).w;
				dsets.link(vp, up);
			}
		}

		return ret;
	}

	GraphTemplate 
	template <typename Fun>
	_Weight GraphHead Prim_MST(Fun fn)
	{ // Need priority-queue (min-heap) supported decreasing
	  // TODO: modify max_heapify in sorting.inl to support it
	  // Or using set

		return 0;
	}

	GraphTemplate
	_Dist GraphHead DAGShortestPath(_Key ks, _Key kt)
	{
		std::vector<_Dist> D(root.size(),std::numeric_limits<_Dist>::max());
		id_type s = Id(ks);
		id_type t = Id(kt);
		D[s] = 0;
		topological_sort([&](_Key&k){
			id_type v = Id(k);
			_foreachAdjE(v, [&](id_type u, const Edge&e){
				if (D[u] > D[v]+e.d) {
					D[u] = D[v]+e.d;
				}
			});
		});
		return D[t];
	}

	GraphTemplate
	void GraphHead DijkstraAll( _Key ks, std::vector<_Dist> &D )
	{// replace priority-queue with map
		typedef std::pair<_Dist, id_type> set_key_type;
		D.clear();
		D.resize(root.size(),std::numeric_limits<_Dist>::max());
		std::set<set_key_type, std::less<set_key_type>, _Alloc<set_key_type>> Q;
		id_type s = Id(ks);
		D[s] = 0;
		Q.emplace(D[s], s);
		while(!Q.empty()) {
			auto md = Q.begin();
			_Dist d = md->first;
			id_type v = md->second;
			Q.erase(md);
			_foreachAdjE(v, [&](id_type u, const Edge&e){
				if (D[u] > D[v]+e.d) {
					if (D[u] < std::numeric_limits<_Dist>::max())
						Q.erase(Q.find(std::make_pair(D[u],u)));
					D[u] = D[v]+e.d;
					Q.emplace(D[u], u);
				}
			});
		}
	}

	GraphTemplate
	_Dist GraphHead Dijkstra(_Key ks, _Key kt)
	{
		std::vector<_Dist> D;
		DijkstraAll(ks, D);
		if (D[Id(kt)] < std::numeric_limits<_Dist>::max())
			return D[Id(kt)];
		else
			return -1;
	}

	GraphTemplate
	_Dist GraphHead Bellman_Ford(_Key ks, _Key kt)
	{// replace priority-queue with map
		typedef std::pair<_Dist, id_type> set_key_type;
		std::vector<_Dist> D(root.size(),std::numeric_limits<_Dist>::max());
		std::set<set_key_type, std::less<set_key_type>, _Alloc<set_key_type>> Q;
		id_type s = Id(ks);
		D[s] = 0;
		_foreachVertex([&](id_type v){
			_foreachEdge([&](id_type v, id_type u, const Edge &e){
				if (D[u] > D[v]+e.d) {
					D[u] = D[v]+e.d;
				}
			});
		});
		_foreachEdge([&](id_type v, id_type u, const Edge &e){
			if (D[u] > D[v]+e.d) {
				throw "has a negative-weight cycle";
			}
		});
		return D[Id(kt)];
	}

} // namespace misc
