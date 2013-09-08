namespace misc{

	MISC_FUNC_QUALIFIER Graph::Graph( int V )
	{
		root.resize(V);
	}

	MISC_FUNC_QUALIFIER void Graph::clear()
	{
		root.clear();
	}

	MISC_FUNC_QUALIFIER void Graph::resize( int V )
	{
		root.resize(V);
	}

	MISC_FUNC_QUALIFIER Graph::color_type Graph::getColor( id_type v )
	{
		return root[v].color;
	}

	MISC_FUNC_QUALIFIER void Graph::setColor( id_type v, color_type c )
	{
		root[v].color = c;
	}

	MISC_FUNC_QUALIFIER bool Graph::visited( id_type v )
	{
		return getColor(v) != white;
	}

	MISC_FUNC_QUALIFIER void Graph::clearColor()
	{
		std::for_each(root.begin(), root.end(), [](Vertex&v){
			v.color = white;
		});
	}
	
	MISC_FUNC_QUALIFIER void Graph::addEdge( id_type u, id_type v, weight_type w )
	{
		id_type ex = std::max(u,v)+1;
		if (ex > id_type(root.size())) {
			root.resize(ex);
		}
		root[u].adj.push_back(Edge(v,w));
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::foreachAdj( id_type v, Fun fn )
	{
		std::for_each(root[v].adj.begin(), root[v].adj.end(), [&](Edge&e){
			fn(e.u);
		});
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::foreachEdge( Fun fn )
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

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::BFS( Fun fn )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				BFS_visit(v, fn);
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::BFS_visit( id_type s, Fun fn )
	{
		setColor(s, gray);
		fn(s);
		std::queue<id_type> Q;
		Q.push(s);
		while (Q.size() != 0) {
			id_type v = Q.front();
			foreachAdj(v, [&](id_type u){
				if (getColor(u) == white) {
					setColor(u, gray);
					fn(u);
					Q.push(u);
				}
			});
			setColor(v, black);
			Q.pop();
		}
	}

	template <typename startFun, typename finishFun>
	MISC_FUNC_QUALIFIER void Graph::DFS( startFun sf, finishFun ff )
	{
		clearColor();
		for (id_type v=0; v<id_type(root.size()); v++)
			if (getColor(v) == white)
				DFS_visit(v, sf, ff);
	}

	template <typename startFun, typename finishFun>
	MISC_FUNC_QUALIFIER void Graph::DFS_visit( id_type v, startFun sf, finishFun ff )
	{
		setColor(v, gray);
		sf(v);
		foreachAdj(v, [&](id_type u){
			if (getColor(u) == white)
				DFS_visit(u, sf, ff);
		});
		setColor(v, black);
		ff(v);
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::topological_sort( Fun fn )
	{
		std::stack<id_type> S;
		DFS([](id_type){}, [&](id_type v){S.push(v);});
		for (; S.size() != 0; S.pop())
			fn(S.top());
	}

	MISC_FUNC_QUALIFIER void Graph::transpose( Graph& gt )
	{
		gt.clear();
		gt.resize(root.size());
		for (id_type v=0; v<id_type(root.size()); v++)
			foreachAdj(v, [&](id_type u){
				gt.addEdge(u, v);
			});
	}

	MISC_FUNC_QUALIFIER void Graph::SCC()
	{
		auto dummyfun = [](int){};
		auto printfun = [](int v){printf("%d\t", v);};

		Graph gt;
		transpose(gt);

		topological_sort([&](id_type v){
			if (!gt.visited(v)) {
				gt.DFS_visit(v, printfun, dummyfun);
				printf("\n");
			}
		});
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER Graph::weight_type Graph::Kruskal_MST(Fun fn)
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
				fn(v, u);
				ret += w;
				dsets.link(vp, up);
			}
		});

		return ret;
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER Graph::weight_type Graph::Prim_MST(Fun fn)
	{ // Need priority-queue (min-heap) supported decreasing.
	  // TODO: modify max_heapify in sorting.inl to support Structure
		return 0;
	}

} // namespace misc
