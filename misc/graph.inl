namespace misc{

	template <typename Key,template<class T,class U> class AdjE>
	Graph<Key,AdjE>::Graph( int V )
	{
		root.resize(V);
	}

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::clear()
	{
		root.clear();
		keymap.clear();
	}

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::resize( int V )
	{
		root.resize(V);
	}

	template <typename Key,template<class T,class U> class AdjE>
	typename Graph<Key,AdjE>::color_type Graph<Key,AdjE>::getColor( id_type v )
	{
		return root[v].color;
	}

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::setColor( id_type v, color_type c )
	{
		root[v].color = c;
	}

	template <typename Key,template<class T,class U> class AdjE>
	bool Graph<Key,AdjE>::Visited( Key v )
	{
		return getColor(keymap[v]) != white;
	}

	template <typename Key,template<class T,class U> class AdjE>
	bool Graph<Key,AdjE>::visited( id_type v )
	{
		return getColor(v) != white;
	}

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::clearColor()
	{
		std::for_each(root.begin(), root.end(), [](Vertex&v){
			v.color = white;
		});
	}

	template <typename Key,template<class T,class U> class AdjE>
	typename Graph<Key,AdjE>::id_type Graph<Key, AdjE>::insert( Key& k )
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

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::addEdge( Key ku, Key kv, weight_type w )
	{
		id_type u,v;
		u = insert(ku);
		v = insert(kv);
		root[u].adj.emplace_back(v,w);
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>
	void Graph<Key,AdjE>::foreachAdj( id_type v, Fun fn )
	{
		std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
			fn(e.u);
		});
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>	
	void Graph<Key,AdjE>::foreachEdge( Fun fn )
	{
		typedef std::tuple<weight_type, id_type, id_type> edge_type;
		std::vector<edge_type> edges;
		for (id_type v=0; v<id_type(root.size()); v++)
			std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
				edges.push_back(std::make_tuple(e.w, v, e.u));
			});
		std::sort(edges.begin(), edges.end());
		std::for_each(edges.begin(), edges.end(), [&](edge_type&t){
			fn(std::get<0>(t), std::get<1>(t), std::get<2>(t));
		});
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>
	void Graph<Key,AdjE>::BFS( Fun fn )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				_BFS_visit(v, fn);
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>
	void Graph<Key,AdjE>::BFS_visit( Key ks, Fun fn )
	{
		id_type s = keymap[ks];
		_BFS_visit(s, fn);
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>
	void Graph<Key,AdjE>::_BFS_visit( id_type s, Fun fn )
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

	template <typename Key,template<class T,class U> class AdjE>
	template <typename startFun, typename finishFun>
	void Graph<Key,AdjE>::DFS( startFun sf, finishFun ff )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				_DFS_visit(v, sf, ff);
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename startFun, typename finishFun>
	void Graph<Key,AdjE>::DFS_visit( Key kv, startFun sf, finishFun ff )
	{
		id_type v = keymap[kv];
		_DFS_visit(v, sf, ff);
	}

	template <typename Key,template<class T,class U> class AdjE>
	template <typename startFun, typename finishFun>
	void Graph<Key,AdjE>::_DFS_visit( id_type v, startFun sf, finishFun ff )
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

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>
	void Graph<Key,AdjE>::topological_sort( Fun fn )
	{
		std::stack<Key> S;
		DFS([](Key){}, [&](Key& v){S.push(v);});
		for (; S.size() != 0; S.pop())
			fn(S.top());
	}

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::transpose( Graph& gt )
	{
		gt.clear();
		gt.resize(root.size());
		for (id_type v=0; v<id_type(root.size()); v++)
			foreachAdj(v, [&](id_type u){
				gt.addEdge(root[u].key, root[v].key);
			});
	}

	template <typename Key,template<class T,class U> class AdjE>
	void Graph<Key,AdjE>::SCC()
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

	template <typename Key,template<class T,class U> class AdjE>
	template <typename Fun>
	typename Graph<Key,AdjE>::weight_type Graph<Key,AdjE>::Kruskal_MST(Fun fn)
	{
		int V = root.size();
		std::vector<int> rank(V);
		std::vector<id_type> parent(V);

		boost::disjoint_sets<int*, id_type*> dsets(&rank[0], &parent[0]);
		for (id_type v=0; v<id_type(root.size()); v++)
			dsets.make_set(v);

		weight_type ret = 0;
		foreachEdge([&](weight_type w, id_type v, id_type u){
			id_type vp = dsets.find_set(v);
			id_type up = dsets.find_set(u);
			if (vp != up) {
				fn(root[v].key, root[u].key);
				ret += w;
				dsets.link(vp, up);
			}
		});

		return ret;
	}

	template <typename Key,template<class T,class U> class AdjE> 
	template <typename Fun>
	typename Graph<Key,AdjE>::weight_type Graph<Key,AdjE>::Prim_MST(Fun fn)
	{ // Need priority-queue (min-heap) supported decreasing
	  // TODO: modify max_heapify in sorting.inl to support it
	  // Or using set

		return 0;
	}

} // namespace misc
