namespace misc{

	MISC_FUNC_QUALIFIER void Graph::resetcp()
	{
		colors.assign(colors.size(), white);
		parents.assign(parents.size(), -1);
	}

	MISC_FUNC_QUALIFIER Graph::Graph( id_type V )
	{
		adjs.resize(V);
		colors.resize(V, white);
		parents.resize(V, -1);
	}

	MISC_FUNC_QUALIFIER void Graph::addEdge( id_type u, id_type v )
	{
		id_type ex = std::max(u,v)+1;
		if (ex > id_type(adjs.size())) {
			adjs.resize(ex);
			colors.resize(ex, white);
			parents.resize(ex, -1);
		}
		adjs[u].push_back(v);
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::BFS( Fun fn )
	{
		resetcp();
		for (id_type v=0; v<id_type(adjs.size()); v++)
			if (colors[v] == white)
				BFS_visit(v, fn);
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::BFS( id_type v, Fun fn )
	{
		resetcp();
		BFS_visit(v, fn);
	}

	template <typename Fun>
	MISC_FUNC_QUALIFIER void Graph::BFS_visit( id_type s, Fun fn )
	{
		colors[s] = gray;
		fn(s);
		std::queue<id_type> Q;
		Q.push(s);
		while (Q.size() != 0) {
			id_type v = Q.front();
			std::for_each(adjs[v].begin(), adjs[v].end(), [&](id_type u){
				if (colors[u] == white) {
					parents[u] = v;
					colors[u] = gray;
					fn(u);
					Q.push(u);
				}
			});
			colors[v] = black;
			Q.pop();
		}
	}

	template <typename startFun, typename finishFun>
	MISC_FUNC_QUALIFIER void Graph::DFS( startFun sf, finishFun ff )
	{
		resetcp();
		for (id_type v=0; v<id_type(adjs.size()); v++)
			if (colors[v] == white)
				DFS_visit(v, sf, ff);
	}

	template <typename startFun, typename finishFun>
	MISC_FUNC_QUALIFIER void Graph::DFS( id_type v, startFun sf, finishFun ff )
	{
		resetcp();
		DFS_visit(v, sf, ff);
	}

	template <typename startFun, typename finishFun>
	MISC_FUNC_QUALIFIER void Graph::DFS_visit( id_type v, startFun sf, finishFun ff )
	{
		colors[v] = gray;
		sf(v);
		std::for_each(adjs[v].begin(), adjs[v].end(), [&](id_type u){
			if (colors[u] == white) {
				parents[u] = v;
				DFS_visit(u, sf, ff);
			}
		});
		colors[v] = black;
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

} // namespace misc
