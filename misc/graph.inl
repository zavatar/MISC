namespace misc{

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	Graph<Key,AdjE,Dir>::Graph( int V )
	{
		root.resize(V);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::clear()
	{
		root.clear();
		keymap.clear();
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::resize( int V )
	{
		root.resize(V);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	typename Graph<Key,AdjE,Dir>::color_type Graph<Key,AdjE,Dir>::getColor( id_type v )
	{
		return root[v].color;
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::setColor( id_type v, color_type c )
	{
		root[v].color = c;
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	bool Graph<Key,AdjE,Dir>::Visited( Key v )
	{
		return getColor(keymap[v]) != white;
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	bool Graph<Key,AdjE,Dir>::visited( id_type v )
	{
		return getColor(v) != white;
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::clearColor()
	{
		std::for_each(root.begin(), root.end(), [](Vertex&v){
			v.color = white;
		});
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	typename Graph<Key,AdjE,Dir>::id_type Graph<Key,AdjE,Dir>::insert( Key& k )
	{
		id_type v;
		if (keymap.find(k) == keymap.end()) {
			v = keymap.size();
			if (v == root.size())
				root.emplace_back(k);
			else
				root[v].key = k;
			keymap[k] = v;
		} else
			v = keymap[k];
		return v;
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::addEdge( Key ku, Key kv, weight_type w, distance_type d )
	{
		id_type u,v;
		u = insert(ku);
		v = insert(kv);
		root[u].adj.emplace_back(v,w,d);
		if (Dir::value)
			root[v].adj.emplace_back(u,w,d);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	void Graph<Key,AdjE,Dir>::foreachAdj( id_type v, Fun fn )
	{
		std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
			fn(e.u);
		});
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	void Graph<Key,AdjE,Dir>::foreachAdjE( id_type v, Fun fn )
	{
		std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
			fn(e);
		});
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>	
	void Graph<Key,AdjE,Dir>::foreachEdge( Fun fn )
	{
		for (id_type v=0; v<id_type(root.size()); v++)
			std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
				fn(v, e);
			});
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	void Graph<Key,AdjE,Dir>::BFS( Fun fn )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				_BFS_visit(v, fn);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	void Graph<Key,AdjE,Dir>::BFS_visit( Key ks, Fun fn )
	{
		id_type s = keymap[ks];
		_BFS_visit(s, fn);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	void Graph<Key,AdjE,Dir>::_BFS_visit( id_type s, Fun fn )
	{
		setColor(s, gray);
		fn(root[s].key);
		std::queue<id_type> Q;
		Q.push(s);
		while (Q.size() != 0) {
			id_type v = Q.front();
			foreachAdj(v, [&](id_type u){
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

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename startFun, typename finishFun>
	void Graph<Key,AdjE,Dir>::DFS( startFun sf, finishFun ff )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				_DFS_visit(v, sf, ff);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename startFun, typename finishFun>
	void Graph<Key,AdjE,Dir>::DFS_visit( Key kv, startFun sf, finishFun ff )
	{
		id_type v = keymap[kv];
		_DFS_visit(v, sf, ff);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename startFun, typename finishFun>
	void Graph<Key,AdjE,Dir>::_DFS_visit( id_type v, startFun sf, finishFun ff )
	{
		setColor(v, gray);
		sf(root[v].key);
		foreachAdj(v, [&](id_type u){
			if (getColor(u) == white)
				_DFS_visit(u, sf, ff);
		});
		setColor(v, black);
		ff(root[v].key);
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	void Graph<Key,AdjE,Dir>::topological_sort( Fun fn )
	{
		std::stack<Key> S;
		DFS([](Key){}, [&](Key& v){S.push(v);});
		for (; S.size() != 0; S.pop())
			fn(S.top());
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::transpose( Graph& gt )
	{
		gt.clear();
		gt.resize(root.size());
		for (id_type v=0; v<id_type(root.size()); v++)
			foreachAdj(v, [&](id_type u){
				gt.addEdge(root[u].key, root[v].key);
			});
	}

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	void Graph<Key,AdjE,Dir>::SCC()
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

	template <typename Key,template<class T,class U> class AdjE,typename Dir>
	template <typename Fun>
	typename Graph<Key,AdjE,Dir>::weight_type Graph<Key,AdjE,Dir>::Kruskal_MST(Fun fn)
	{
		int V = root.size();
		std::vector<int> rank(V);
		std::vector<id_type> parent(V);

		boost::disjoint_sets<int*, id_type*> dsets(&rank[0], &parent[0]);
		for (id_type v=0; v<id_type(root.size()); v++)
			dsets.make_set(v);

		typedef std::pair<id_type, Edge> edge_type;
		std::vector<edge_type> edges;
		foreachEdge([&](id_type v, Edge &e){
			edges.emplace_back(v, e);
		});
		std::sort(edges.begin(), edges.end(),
			[](edge_type&l, edge_type&r){
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

	template <typename Key,template<class T,class U> class AdjE,typename Dir> 
	template <typename Fun>
	typename Graph<Key,AdjE,Dir>::weight_type Graph<Key,AdjE,Dir>::Prim_MST(Fun fn)
	{ // Need priority-queue (min-heap) supported decreasing
	  // TODO: modify max_heapify in sorting.inl to support it
	  // Or using set

		return 0;
	}

	template <typename Key,
		template<class T,class U> class AdjE,
		typename Dir>
		typename Graph<Key,AdjE,Dir>::distance_type Graph<Key,AdjE,Dir>::DAGShortestPath(Key ks, Key kt)
	{
		std::vector<distance_type> D(root.size(),std::numeric_limits<distance_type>::max());
		id_type s = keymap[ks];
		id_type t = keymap[kt];
		D[s] = 0;
		topological_sort([&](Key&k){
			id_type v = keymap[k];
			foreachAdjE(v, [&](Edge&e){
				if (D[e.u] > D[v]+e.d) {
					D[e.u] = D[v]+e.d;
				}
			});
		});
		return D[t];
	}

	template <typename Key,
		template<class T,class U> class AdjE,
		typename Dir>
		typename Graph<Key,AdjE,Dir>::distance_type Graph<Key,AdjE,Dir>::Dijkstra(Key ks, Key kt)
	{// replace priority-queue with map
		std::vector<distance_type> D(root.size(),std::numeric_limits<distance_type>::max());
		std::set<std::pair<distance_type, id_type>> Q;
		id_type s = keymap[ks];
		D[s] = 0;
		Q.emplace(D[s], s);
		while(!Q.empty()) {
			auto md = Q.begin();
			distance_type d = md->first;
			id_type v = md->second;
			Q.erase(md);
			foreachAdjE(v, [&](Edge&e){
				if (D[e.u] > D[v]+e.d) {
					if (D[e.u] < std::numeric_limits<distance_type>::max())
						Q.erase(Q.find(std::make_pair(D[e.u],e.u)));
					D[e.u] = D[v]+e.d;
					Q.emplace(D[e.u], e.u);
				}
			});
		}
		return D[keymap[kt]];
	}

	template <typename Key,
		template<class T,class U> class AdjE,
		typename Dir>
		typename Graph<Key,AdjE,Dir>::distance_type Graph<Key,AdjE,Dir>::Bellman_Ford(Key ks, Key kt)
	{// replace priority-queue with map
		std::vector<distance_type> D(root.size(),std::numeric_limits<distance_type>::max());
		std::set<std::pair<distance_type, id_type>> Q;
		id_type s = keymap[ks];
		D[s] = 0;
		for (id_type i=0; i<id_type(root.size()); i++)
			foreachEdge([&](id_type v, Edge &e){
				if (D[e.u] > D[v]+e.d) {
					D[e.u] = D[v]+e.d;
				}
			});
		foreachEdge([&](id_type v, Edge &e){
			if (D[e.u] > D[v]+e.d) {
				throw "has a negative-weight cycle";
			}
		});
		return D[keymap[kt]];
	}

} // namespace misc
