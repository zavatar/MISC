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
		keymap.clear();
	}

	GraphTemplate
	void GraphHead resize( int V )
	{
		root.resize(V);
	}

	GraphTemplate
	typename GraphHead color_type GraphHead getColor( id_type v )
	{
		return root[v].color;
	}

	GraphTemplate
	void GraphHead setColor( id_type v, color_type c )
	{
		root[v].color = c;
	}

	GraphTemplate
	bool GraphHead Visited( Key v )
	{
		return getColor(keymap[v]) != white;
	}

	GraphTemplate
	bool GraphHead visited( id_type v )
	{
		return getColor(v) != white;
	}

	GraphTemplate
	void GraphHead clearColor()
	{
		std::for_each(root.begin(), root.end(), [](Vertex&v){
			v.color = white;
		});
	}

	GraphTemplate
	void GraphHead addVertex( Key kv )
	{
		if (keymap.find(kv) == keymap.end()) {
			id_type v = keymap.size();
			if (v == root.size())
				root.emplace_back(kv);
			else
				root[v].key = kv;
			keymap[kv] = v;
		}
	}

	GraphTemplate
	template <bool isUpdate>
	void GraphHead connect( Key ku, Key kv, weight_type w, distance_type d )
	{
		id_type u = keymap[ku];
		id_type v = keymap[kv];

		if (isUpdate) _updateEdge(u,v,w,d);
		else root[u].adj.emplace_back(v,w,d);
		if (Dir::value)
			if (isUpdate) _updateEdge(v,u,w,d);
			else root[v].adj.emplace_back(u,w,d);
	}

	GraphTemplate
	void GraphHead addEdge( Key ku, Key kv, weight_type w, distance_type d )
	{
		addVertex(ku);
		addVertex(kv);
		connect<false>(ku, kv, w, d);
	}

	GraphTemplate
	void GraphHead updateEdge( Key ku, Key kv, weight_type w, distance_type d )
	{
		addVertex(ku);
		addVertex(kv);
		connect<true>(ku, kv, w, d);
	}

	GraphTemplate
	void GraphHead _updateEdge( id_type u, id_type v, weight_type w, distance_type d )
	{
		Elist_type::iterator it = root[u].adj.begin();
		Elist_type::iterator end = root[u].adj.end();
		for (; it!=end; it++) {
			if (it->u == v) {
				it->w = w; it->d = d; break;
			}
		}
		if (it==end)
			root[u].adj.emplace_back(v,w,d);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead foreachAdj( Key kv, Fun fn )
	{
		_foreachAdj(keymap[kv], fn);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _foreachAdj( id_type v, Fun fn )
	{
		std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
			fn(e.u);
		});
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _foreachAdjE( id_type v, Fun fn )
	{
		std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
			fn(e);
		});
	}

	GraphTemplate
	template <typename Fun>	
	void GraphHead _foreachEdge( Fun fn )
	{
		for (id_type v=0; v<id_type(root.size()); v++)
			std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
				fn(v, e);
			});
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead BFS( Fun fn )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				_BFS_visit(v, fn);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead BFS_visit( Key ks, Fun fn )
	{
		id_type s = keymap[ks];
		_BFS_visit(s, fn);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead _BFS_visit( id_type s, Fun fn )
	{
		setColor(s, gray);
		fn(root[s].key);
		std::queue<id_type> Q;
		Q.push(s);
		while (Q.size() != 0) {
			id_type v = Q.front();
			_foreachAdj(v, [&](id_type u){
				if (getColor(u) == white) {
					setColor(u, gray);
					fn(root[u].key);
					Q.push(u);
				}
			});
			setColor(v, black);
			Q.pop();
		}
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead DFS( startFun sf, finishFun ff )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				_DFS_visit(v, sf, ff);
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead DFS_visit( Key kv, startFun sf, finishFun ff )
	{
		id_type v = keymap[kv];
		_DFS_visit(v, sf, ff);
	}

	GraphTemplate
	template <typename startFun, typename finishFun>
	void GraphHead _DFS_visit( id_type v, startFun sf, finishFun ff )
	{
		setColor(v, gray);
		sf(root[v].key);
		_foreachAdj(v, [&](id_type u){
			if (getColor(u) == white)
				_DFS_visit(u, sf, ff);
		});
		setColor(v, black);
		ff(root[v].key);
	}

	GraphTemplate
	template <typename Fun>
	void GraphHead topological_sort( Fun fn )
	{
		std::stack<Key> S;
		DFS([](Key){}, [&](Key& v){S.push(v);});
		for (; S.size() != 0; S.pop())
			fn(S.top());
	}

	GraphTemplate
	void GraphHead transpose( Graph& gt )
	{
		gt.clear();
		gt.resize(root.size());
		for (id_type v=0; v<id_type(root.size()); v++)
			_foreachAdj(v, [&](id_type u){
				gt.addEdge(root[u].key, root[v].key);
			});
	}

	GraphTemplate
	void GraphHead SCC()
	{
		auto dummyfun = [](Key){};
		auto printfun = [](Key v){std::cout<<v<<'\t';};

		Graph gt;
		transpose(gt);

		topological_sort([&](Key&k){
			if (!gt.Visited(k)) {
				gt.DFS_visit(k, printfun, dummyfun);
				printf("\n");
			}
		});
	}

	GraphTemplate
	template <typename Fun>
	weight_type GraphHead Kruskal_MST(Fun fn)
	{
		int V = root.size();
		std::vector<int> rank(V);
		std::vector<id_type> parent(V);

		boost::disjoint_sets<int*, id_type*> dsets(&rank[0], &parent[0]);
		for (id_type v=0; v<id_type(root.size()); v++)
			dsets.make_set(v);

		typedef std::pair<id_type, Edge> edge_type;
		std::vector<edge_type> edges;
		_foreachEdge([&](id_type v, Edge &e){
			edges.emplace_back(v, e);
		});
		std::sort(edges.begin(), edges.end(),
			[](const edge_type&l, const edge_type&r){
				return l.second.w < r.second.w;
		});

		weight_type ret = 0;
		std::for_each(edges.begin(), edges.end(), [&](edge_type&t){
			id_type v = t.first;
			id_type u = t.second.u;
			id_type vp = dsets.find_set(v);
			id_type up = dsets.find_set(u);
			if (vp != up) {
				fn(root[v].key, root[u].key);
				ret += t.second.w;
				dsets.link(vp, up);
			}
		});

		return ret;
	}

	GraphTemplate 
	template <typename Fun>
	weight_type GraphHead Prim_MST(Fun fn)
	{ // Need priority-queue (min-heap) supported decreasing
	  // TODO: modify max_heapify in sorting.inl to support it
	  // Or using set

		return 0;
	}

	GraphTemplate
	distance_type GraphHead DAGShortestPath(Key ks, Key kt)
	{
		std::vector<distance_type> D(root.size(),std::numeric_limits<distance_type>::max());
		id_type s = keymap[ks];
		id_type t = keymap[kt];
		D[s] = 0;
		topological_sort([&](Key&k){
			id_type v = keymap[k];
			_foreachAdjE(v, [&](Edge&e){
				if (D[e.u] > D[v]+e.d) {
					D[e.u] = D[v]+e.d;
				}
			});
		});
		return D[t];
	}

	GraphTemplate
	void GraphHead DijkstraAll( Key ks, std::vector<distance_type> &D )
	{
		D.clear();
		D.resize(root.size(),std::numeric_limits<distance_type>::max());
		std::set<std::pair<distance_type, id_type>> Q;
		id_type s = keymap[ks];
		D[s] = 0;
		Q.emplace(D[s], s);
		while(!Q.empty()) {
			auto md = Q.begin();
			distance_type d = md->first;
			id_type v = md->second;
			Q.erase(md);
			_foreachAdjE(v, [&](Edge&e){
				if (D[e.u] > D[v]+e.d) {
					if (D[e.u] < std::numeric_limits<distance_type>::max())
						Q.erase(Q.find(std::make_pair(D[e.u],e.u)));
					D[e.u] = D[v]+e.d;
					Q.emplace(D[e.u], e.u);
				}
			});
		}
	}

	GraphTemplate
	distance_type GraphHead Dijkstra(Key ks, Key kt)
	{// replace priority-queue with map
		std::vector<distance_type> D;
		DijkstraAll(ks, D);
		if (D[keymap[kt]] < std::numeric_limits<distance_type>::max())
			return D[keymap[kt]];
		else
			return -1;
	}

	GraphTemplate
	distance_type GraphHead Bellman_Ford(Key ks, Key kt)
	{// replace priority-queue with map
		std::vector<distance_type> D(root.size(),std::numeric_limits<distance_type>::max());
		std::set<std::pair<distance_type, id_type>> Q;
		id_type s = keymap[ks];
		D[s] = 0;
		for (id_type i=0; i<id_type(root.size()); i++)
			_foreachEdge([&](id_type v, Edge &e){
				if (D[e.u] > D[v]+e.d) {
					D[e.u] = D[v]+e.d;
				}
			});
		_foreachEdge([&](id_type v, Edge &e){
			if (D[e.u] > D[v]+e.d) {
				throw "has a negative-weight cycle";
			}
		});
		return D[keymap[kt]];
	}

} // namespace misc
