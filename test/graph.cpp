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
		ff(u);
	}
private:
	Fun fn, ff;
};

TEST(Graph_Test, Standard)
{
	{
		// 0--1  2
		// |  |_/|
		// 3--4  5
		enum { v0, v1, v2, v3, v4, v5, vN };
		typedef std::pair<int, int> Edge_type;
		std::vector<Edge_type> eVec;
		eVec.emplace_back(v0, v1);
		eVec.emplace_back(v2, v4);
		eVec.emplace_back(v2, v5);
		eVec.emplace_back(v0, v3);
		eVec.emplace_back(v1, v4);
		eVec.emplace_back(v4, v3);

		int _bfs[6] = {v0,v1,v3,v4,v2,v5};
		std::vector<int> bfsexp(_bfs, _bfs+6);
		int _dfs[6] = {v0,v1,v4,v2,v5,v3};
		std::vector<int> dfsexp(_dfs, _dfs+6);
		std::vector<int> buff;

		auto dummyfun = [](int){};
		auto printfun = [&](int v){buff.push_back(v);};

		misc::VVG bg(eVec.begin(), eVec.end(), vN);
		boost::graph_traits<misc::VVG>::vertex_iterator beginit, endit;
		beginit = boost::vertices(bg).first;
		endit = boost::vertices(bg).second;
		boost::breadth_first_search(bg, *beginit, boost::visitor(bfs_visitor<std::function<void(int)>>(printfun)));
		EXPECT_TRUE(bfsexp == buff);
		buff.clear();

		misc::Graph<int, std::list, misc::undirected> g(6);
		g.addEdge(v0,v1);
		g.addEdge(v2,v4);
		g.addEdge(v2,v5);
		g.addEdge(v0,v3);
		g.addEdge(v1,v4);
		g.addEdge(v4,v3);

		g.BFS(printfun);
		EXPECT_TRUE(bfsexp == buff);
		buff.clear();

		boost::depth_first_search(bg, boost::visitor(dfs_visitor<std::function<void(int)>>(printfun,dummyfun)));
		EXPECT_TRUE(dfsexp == buff);
		buff.clear();

		g.DFS(printfun, dummyfun);
		EXPECT_TRUE(dfsexp == buff);
		buff.clear();

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// a--b  c
		// |  |_/|
		// d--e  f
		misc::Graph<std::string, std::list, misc::undirected> g;
		g.addEdge("a","b");
		g.addEdge("c","e");
		g.addEdge("c","f");
		g.addEdge("a","d");
		g.addEdge("b","e");
		g.addEdge("e","d");

		std::string _bfs[6] = {"a","b","d","e","c","f"};
		std::vector<std::string> bfsexp(_bfs, _bfs+6);
		std::string _dfs[6] = {"a","b","e","c","f","d"};
		std::vector<std::string> dfsexp(_dfs, _dfs+6);

		std::vector<std::string> buff;

		auto dummyfun = [](std::string){};
		auto printfun = [&](std::string& v){buff.push_back(v);};

		g.BFS(printfun);
		EXPECT_TRUE(bfsexp == buff);
		buff.clear();

		g.DFS(printfun, dummyfun);
		EXPECT_TRUE(dfsexp == buff);
		buff.clear();

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 22.9
		misc::Graph<char, std::list, misc::directed> g;
		char de[28] = {'0','1','1','2','2','3','3','2','4','0','1','4','1','5',
			'2','6','3','7','4','5','5','6','6','5','6','7','7','7'};
		for (int i=0; i<28; i+=2)
			g.addEdge(de[i], de[i+1]);

		g.SCC();

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 23.4
		misc::Graph<char, std::list, misc::undirected> g;
		char e[14*2] = {'1','2','1','8','2','8','2','3','3','9','3','6','3','4',
			'4','5','4','6','5','6','6','7','7','9','7','8','8','9'};
		float w[14] = {4,8,11,8,2,4,7,9,14,10,2,6,1,7};
		for (int i=0; i<14; i++)
			g.addEdge(e[2*i], e[2*i+1], w[i]);

		auto printfun = [](char v, char u){std::cout<<"("<<v<<","<<u<<") ";};

		EXPECT_EQ(g.Kruskal_MST(printfun), 37.f);
		//EXPECT_EQ(g.Prim_MST(printfun), 37.f);
		printf("\n");

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 24.5, DAG
		//       |-----6-----|------1------|
		// r--5--s--2--t--7--x-(-1)-y-(-2)-z
		// |-----3-----|-----4------|
		//             |---------2---------|
		// has negative distance
		misc::Graph<char, std::vector, misc::directed> g;
		char de[2*10] = {'t','x','t','y','t','z', 'x','y','x','z', 'y','z', 
			'r','s','r','t','s','t','s','x',};
		float d[10] = {7,4,2, -1,1, -2, 5,3, 2,6};
		for (int i=0; i<10; i++)
			g.addEdge(de[2*i], de[2*i+1], 1, d[i]);

		char _tp[6] = {'r','s','t','x','y','z'};
		std::vector<char> tpexp(_tp, _tp+6);
		std::vector<char> buff;

		auto printfun = [&](char& v){buff.push_back(v);};

		g.topological_sort(printfun);
		EXPECT_TRUE(tpexp == buff);
		buff.clear();

		EXPECT_EQ(g.DAGShortestPath('s', 'z'), 3);

		g.clear();

		// case from CLRS Figure 24.6, nonnegative
		//    t   x
		// s
		//    y   z
		// has cycle
		char de1[2*10] = {'s','t','s','y','t','y','y','t', 't','x','y','z','y','x',
			'x','z','z','x', 'z','s'};
		float d1[10] = {10,5,2,3, 1,2,9, 4,6, 7};
		for (int i=0; i<10; i++)
			g.addEdge(de1[2*i], de1[2*i+1], 1, d1[i]);

		EXPECT_EQ(g.Dijkstra('s','x'), 9);

		g.clear();

		// case from CLRS Figure 24.4, Bellman-Ford
		// has cycle and negative distance
		char de2[2*10] = {'s','t','s','y','t','y', 't','x','x','t','t','z','y','z','y','x',
			'z','x','z','s'};
		float d2[10] = {6,7,8, 5,-2,-4,9,-3, 7,2};
		for (int i=0; i<10; i++)
			g.addEdge(de2[2*i], de2[2*i+1], 1, d2[i]);

		EXPECT_EQ(g.Bellman_Ford('s','z'), -2);

		g.clear();
	}
}