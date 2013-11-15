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
	typename GraphHead id_type& GraphHead Parent( id_type& v )
	{
		return root[v].parent;
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
	void GraphHead disconnect( _Key ku, _Key kv )
	{
		id_type u = Id(ku);
		id_type v = Id(kv);

		root[u].adj.erase(v);
		if (_Dir::value)
			root[v].adj.erase(u);
	}

	GraphTemplate
	bool GraphHead hasEdge( _Key ku, _Key kv )
	{
		id_type u = Id(ku);
		id_type v = Id(kv);
		return root[u].adj.find(v) != root[u].adj.end();
	}

	GraphTemplate
	const typename GraphHead Edge& GraphHead getEdge( _Key ku, _Key kv )
	{
		return root[Id(ku)].adj[Id(kv)];
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
	void GraphHead foreachPath( _Key kv, Fun fn )
	{
		_foreachPath(Id(kv), fn);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _foreachPath( id_type v, Fun fn )
	{
		for(id_type u=v, p=Parent(v); p!=-1; p=Parent(p)) {
			fn(p, u, root[p].adj[u]);
			u = p;
		}
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
		Parent(s) = -1;
		fn(Key(s));
		std::queue<id_type> Q;
		Q.push(s);
		while (Q.size() != 0) {
			id_type v = Q.front();
			_foreachAdj(v, [&](id_type u){
				if (!visited(u)) {
					Color(u) = gray;
					Parent(u) = v;
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
			if(!visited(v)) {
				Parent(v) = -1;
				_DFS_visit(v, sf, ff);
			}
		});
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead DFS_visit( _Key kv, startFun sf, finishFun ff )
	{
		id_type v = Id(kv);
		Parent(v) = -1;
		_DFS_visit(v, sf, ff);
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead _DFS_visit( id_type v, startFun sf, finishFun ff )
	{
		Color(v) = gray;
		sf(Key(v));
		_foreachAdj(v, [&](id_type u){
			if (!visited(u)) {
				Parent(u) = v;
				_DFS_visit(u, sf, ff);
			}
		});
		Color(v) = black;
		ff(Key(v));
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead topological_sort( Fun fn )
	{
		std::stack<_Key> S;
		DFS([](_Key){}, [&](const _Key& v){S.push(v);});
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
	int GraphHead SCC()
	{
		auto dummyfun = [](_Key){};
		auto printfun = [](_Key v){std::cout<<v<<'\t';};

		Graph gt;
		transpose(gt);

		int counts = 0;
		topological_sort([&](const _Key&k){
			if (!gt.Visited(k)) {
				counts++;
				gt.DFS_visit(k, printfun, dummyfun);
				printf("\n");
			}
		});

		return counts;
	}

	GraphTemplate
	template <typename Fun>
	_Weight GraphHead Kruskal_MST(Fun fn)
	{
		DisjointSets<id_type, keyInt0> dsets;
		_foreachVertex([&](id_type v){
			dsets.makeSet(v);
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
			id_type vp = dsets.findSet(v);
			id_type up = dsets.findSet(u);
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
		topological_sort([&](const _Key&k){
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

	GraphTemplate
	void GraphHead Floyd_Warshall( std::vector<std::vector<_Dist>> &D )
	{
		D.clear();
		std::vector<std::vector<_Dist>> Dk[2];
		int V = root.size();
		Dk[0].resize(V, std::vector<_Dist>(V, std::numeric_limits<_Dist>::max()));
		Dk[1].resize(V, std::vector<_Dist>(V, std::numeric_limits<_Dist>::max()));
		_foreachEdge([&](id_type v, id_type u, const Edge&e){
			Dk[0][v][u] = e.d;
		});
		for(int v=0; v<V; v++)
			Dk[0][v][v] = 0;
		int cur = 0;
		int pre = 1;
		for(int k=0; k<V; k++) {
			cur = 1-cur;
			pre = 1-pre;
			for(int i=0; i<V; i++)
				for(int j=0; j<V; j++) {
					int s = std::numeric_limits<_Dist>::max();
					if (Dk[pre][i][k] != s && Dk[pre][k][j] != s)
						s = Dk[pre][i][k]+Dk[pre][k][j];
					Dk[cur][i][j] = std::min(Dk[pre][i][j], s);
				}
		}
		// move assignment
		D = static_cast<std::vector<std::vector<_Dist>>&&>(Dk[cur]);
	}

	GraphTemplate
	_Weight GraphHead Edmonds_Karp( _Key ks, _Key kt )
	{
		id_type s = Id(ks);
		id_type t = Id(kt);

		// Construct residual graph
		static_assert(std::is_same<_Dir, directed>::value, "_Dir != directed");
		typedef Graph<int, _Dir, keyInt0, _Weight, _Dist> rGraph_type;
		rGraph_type rg;
		_foreachEdge([&](id_type v, id_type u, const Edge &e){
			rg.addEdge(v, u, e.w, e.d);
			// How to support antiparallel edges?
		});

		_Weight max_flow = 0;
		while(true) {
			// find augment path using BFS
			rg.clearColor();
			rg.BFS_visit(s, [](_Key){});
			if (!rg.Visited(t)) break;

			// max flow on the augment path
			_Weight path_flow = std::numeric_limits<_Weight>::max();
			rg.foreachPath(t, [&](id_type v, id_type u, const typename rGraph_type::Edge&e){
				path_flow = std::min(path_flow, e.w);
			});

			// update residual capacities
			rg.foreachPath(t, [&](id_type v, id_type u, const typename rGraph_type::Edge&e){
				if ((e.w-path_flow) <= 0)
					rg.disconnect(v, u);
				else
					rg.connect(v, u, e.w-path_flow, e.d);
				if (rg.hasEdge(u, v))
					rg.connect(u, v, getEdge(u,v).w+path_flow, getEdge(u,v).d);
				else
					rg.connect(u, v, path_flow);
			});
			max_flow += path_flow;
		}
		return max_flow;
	}

//////////////////////////////////////////////////////////////////////////

	DisjointSetsTemplate
	template <class InputIterator>
	DisjointSetsHead DisjointSets( InputIterator first, InputIterator last )
	{
		count = last-first;
		parent.resize(count);
		rank.resize(count);
		for (int i=0; i<count; i++) {
			parent[i] = addkey(*(first+i));
			rank[i] = 0;
		}
	}

	DisjointSetsTemplate
	void DisjointSetsHead makeSet( _Key kv )
	{
		parent.push_back(addkey(kv));
		rank.push_back(0);
		count++;
	}

	DisjointSetsTemplate
	_Key DisjointSetsHead findSet( _Key kv )
	{
		return Key(_findSet(Id(kv)));
	}

	DisjointSetsTemplate
	bool DisjointSetsHead isConnected(_Key ku, _Key kv)
	{
		return _findSet(Id(ku)) == _findSet(Id(kv));
	}

	DisjointSetsTemplate
	void DisjointSetsHead link(_Key ku, _Key kv)
	{
		id_type i = _findSet(Id(ku));
		id_type j = _findSet(Id(kv));
		if (i == j) return;

		// union by rank
		if (rank[i] < rank[j]) parent[i] = j;
		else if (rank[i] > rank[j]) parent[j] = i;
		else {
			parent[j] = i;
			rank[i]++;
		}
		count--;
	}

	DisjointSetsTemplate
	typename DisjointSetsHead id_type DisjointSetsHead _findSet( id_type kv )
	{
		while (kv != parent[kv]) {
			parent[kv] = parent[parent[kv]]; // path compression
			kv = parent[kv];
		}
		return kv;
	}

} // namespace misc
