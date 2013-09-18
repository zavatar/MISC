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

		Vertex_type _bfs[6] = {v0,v1,v3,v4,v2,v5};
		std::vector<int> bfsexp(_bfs, _bfs+6);
		Vertex_type _dfs[6] = {v0,v1,v4,v3,v2,v5};
		std::vector<int> dfsexp(_dfs, _dfs+6);
		Vertex_type _top[6] = {v2,v5,v0,v1,v4,v3};
		std::vector<int> topexp(_top, _top+6);
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

		misc::Graph<Vertex_type, std::list> g(6);
		g.addEdge(v0,v1);
		g.addEdge(v2,v4);
		g.addEdge(v2,v5);
		g.addEdge(v0,v3);
		g.addEdge(v1,v4);
		g.addEdge(v4,v3);

		g.BFS(printfun);
		EXPECT_TRUE(bfsexp == buff);
		buff.clear();

		boost::depth_first_search(bg, boost::visitor(dfs_visitor<std::function<void(int)>>(dummyfun,dummyfun)));

		g.DFS(printfun, dummyfun);
		EXPECT_TRUE(dfsexp == buff);
		buff.clear();

		g.topological_sort(printfun);
		EXPECT_TRUE(topexp == buff);
		buff.clear();

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 22.9
		misc::Graph<char, std::list> g(6);
		char de[28] = {'0','1','1','2','2','3','3','2','4','0','1','4','1','5',
			'2','6','3','7','4','5','5','6','6','5','6','7','7','7'};
		for (int i=0; i<28; i+=2)
			g.addEdge(de[i], de[i+1]);

		g.SCC();

		g.clear();

		// case from CLRS Figure 23.4
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
		// a--b  c
		// |  |_/|
		// d--e  f
		misc::Graph<std::string, std::list> g;
		g.addEdge("a","b");
		g.addEdge("c","e");
		g.addEdge("c","f");
		g.addEdge("a","d");
		g.addEdge("b","e");
		g.addEdge("e","d");

		std::string _bfs[6] = {"a","b","d","e","c","f"};
		std::vector<std::string> bfsexp(_bfs, _bfs+6);
		std::string _dfs[6] = {"a","b","e","d","c","f"};
		std::vector<std::string> dfsexp(_dfs, _dfs+6);
		std::string _top[6] = {"c","f","a","b","e","d"};
		std::vector<std::string> topexp(_top, _top+6);

		std::vector<std::string> buff;
		std::vector<std::string> buff1;

		auto dummyfun = [](std::string){};
		auto printfun = [&](std::string& v){buff.push_back(v);};
		auto printfun1 = [&](std::string& v){buff1.push_back(v);};

		g.BFS(printfun);
		EXPECT_TRUE(bfsexp == buff);
		buff.clear();

		g.DFS(printfun, printfun1);
		EXPECT_TRUE(dfsexp == buff);
		buff.clear();
		std::reverse(buff1.begin(), buff1.end());
		EXPECT_TRUE(topexp == buff1);
		buff1.clear();

		g.topological_sort(printfun);
		EXPECT_TRUE(topexp == buff);
		buff.clear();

		g.clear();
	}
}