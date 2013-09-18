#include <misc/misc.hpp>

#include "gtest/gtest.h"

#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>

template <typename Fun>
class bfs_visitor: public boost::default_bfs_visitor {
public:
	bfs_visitor(Fun functor): fn(functor) {}
	template < typename Vertex, typename Graph >
	void discover_vertex(Vertex u, const Graph & g) const
	{
		fn(u);
	}
private:
	Fun fn;
};

template <typename Fun>
class dfs_visitor: public boost::default_dfs_visitor {
public:
	dfs_visitor(Fun f1, Fun f2): fn(f1), ff(f2) {}
	template < typename Vertex, typename Graph >
	void discover_vertex(Vertex u, const Graph & g) const
	{
		fn(u);
	}
	template < typename Vertex, typename Graph >
	void finish_vertex(Vertex u, const Graph & g) const
	{
		fn(u);
	}
private:
	Fun fn, ff;
};

TEST(Graph_Test, Standard)
{
	// 0--1  2
	// |  |_/|
	// 3--4  5
	enum Vertex_type{ v0, v1, v2, v3, v4, v5, vN };
	typedef std::pair<Vertex_type, Vertex_type> Edge_type;
	std::vector<Edge_type> eVec;
	eVec.emplace_back(v0, v1);
	eVec.emplace_back(v2, v4);
	eVec.emplace_back(v2, v5);
	eVec.emplace_back(v0, v3);
	eVec.emplace_back(v1, v4);
	eVec.emplace_back(v4, v3);

	auto dummyfun = [](int){};
	auto printfun = [](int v){printf("%d\t", v);};

	misc::VVG bg(eVec.begin(), eVec.end(), vN);
	boost::graph_traits<misc::VVG>::vertex_iterator beginit, endit;
	beginit = boost::vertices(bg).first;
	endit = boost::vertices(bg).second;
	boost::breadth_first_search(bg, *beginit, boost::visitor(bfs_visitor<std::function<void(int)>>(printfun)));
	printf("\n");

	misc::Graph g(6);
	g.addEdge(v0,v1);
	g.addEdge(v2,v4);
	g.addEdge(v2,v5);
	g.addEdge(v0,v3);
	g.addEdge(v1,v4);
	g.addEdge(v4,v3);

	g.BFS(printfun);
	printf("\n");

	boost::depth_first_search(bg, boost::visitor(dfs_visitor<std::function<void(int)>>(printfun,printfun)));
	printf("\n");

	g.DFS(printfun, printfun);
	printf("\n");

	g.topological_sort(dummyfun);
	printf("\n");

	g.clear();
//////////////////////////////////////////////////////////////////////////
	// case from CLRS Figure 22.9
	int de[28] = {0,1,1,2,2,3,3,2,4,0,1,4,1,5,2,6,3,7,4,5,5,6,6,5,6,7,7,7};
	for (int i=0; i<28; i+=2)
		g.addEdge(de[i], de[i+1]);
	
	g.SCC();

	g.clear();
//////////////////////////////////////////////////////////////////////////
	// case from CLRS Figure 23.4
	int e[14*2] = {1,2,1,8,2,8,2,3,3,9,3,6,3,4,4,5,4,6,5,6,6,7,7,9,7,8,8,9};
	float w[14] = {4,8,11,8,2,4,7,9,14,10,2,6,1,7};
	for (int i=0; i<14; i++)
		g.addEdge(e[2*i], e[2*i+1], w[i]);

	auto printfun2 = [](int v, int u){printf("(%d,%d) ", v,u);};

	EXPECT_EQ(g.Kruskal_MST(printfun2), 37.f);
	//EXPECT_EQ(g.Prim_MST(printfun2), 37.f);

	g.clear();
}