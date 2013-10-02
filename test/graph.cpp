#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(Graph_Test, Standard)
{
	{
		// 0--1  2
		// |  |_/|
		// 3--4  5
		enum { vN=6, v0, v1, v2, v3, v4, v5 };
		typedef std::pair<int, int> Edge_type;
		std::vector<Edge_type> eVec;
		eVec.emplace_back(v0, v1);
		eVec.emplace_back(v2, v4);
		eVec.emplace_back(v2, v5);
		eVec.emplace_back(v0, v3);
		eVec.emplace_back(v1, v4);
		eVec.emplace_back(v4, v3);

		int _bfs1[6] = {v0,v1,v3,v4,v2,v5};
		int _bfs2[6] = {v0,v3,v1,v4,v2,v5};
		std::vector<int> bfsexp1(_bfs1, _bfs1+6);
		std::vector<int> bfsexp2(_bfs2, _bfs2+6);
		int _dfs1[6] = {v0,v1,v4,v2,v5,v3};
		int _dfs2[6] = {v0,v1,v4,v3,v2,v5};
		int _dfs3[6] = {v0,v3,v4,v2,v5,v1};
		int _dfs4[6] = {v0,v3,v4,v1,v2,v5};
		std::vector<int> dfsexp1(_dfs1, _dfs1+6);
		std::vector<int> dfsexp2(_dfs2, _dfs2+6);
		std::vector<int> dfsexp3(_dfs3, _dfs3+6);
		std::vector<int> dfsexp4(_dfs4, _dfs4+6);
		std::vector<int> buff;

		auto dummyfun = [](int){};
		auto printfun = [&](int v){buff.push_back(v);};

		misc::Graph<int,misc::undirected,misc::keyInt0> g(6);
		g.addEdge(v0,v1);
		g.addEdge(v2,v4);
		g.addEdge(v2,v5);
		g.addEdge(v0,v3);
		g.addEdge(v1,v4);
		g.addEdge(v4,v3);

		g.BFS(printfun);
		EXPECT_TRUE(bfsexp1 == buff || bfsexp2 == buff);
		buff.clear();

		g.DFS(printfun, dummyfun);
		EXPECT_TRUE(dfsexp1 == buff || dfsexp2 == buff ||
			dfsexp3 == buff || dfsexp4 == buff);
		buff.clear();

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 22.9
		misc::Graph<char, misc::directed> g;
		char de[28] = {'0','1','1','2','2','3','3','2','4','0','1','4','1','5',
			'2','6','3','7','4','5','5','6','6','5','6','7','7','7'};
		for (int i=0; i<28; i+=2)
			g.addEdge(de[i], de[i+1]);

		EXPECT_EQ(g.SCC(), 4);

		g.clear();
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 23.4
		misc::Graph<char, misc::undirected> g;
		char e[14*2] = {'a','b','a','h','b','h','b','c','c','i','c','f','c','d',
			'd','e','d','f','e','f','f','g','g','i','g','h','h','i'};
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
		misc::Graph<char, misc::directed> g;
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
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 25.4
		misc::Graph<char, misc::directed, misc::keyMap, float, int> g;
		char de[2*9] = {'1','2','1','3','1','5', '2','4','2','5', '3','2',
		'4','1','4','3', '5','4'};
		int d[9] = {3,8,-4, 1,7, 4, 2,-5, 6};
		for (int i=0; i<9; i++)
			g.addEdge(de[2*i], de[2*i+1], 1, d[i]);

		int expd[5][5] = {
			{ 0, 1,-3, 2,-4},
			{ 3, 0,-4, 1,-1},
			{ 7, 4, 0, 5, 3},
			{ 2,-1,-5, 0,-2},
			{ 8, 5, 1, 6, 0}
		};
		std::vector<std::vector<int>> D;
		g.Floyd_Warshall(D);
		for(char i='1'; i<='5'; i++)
			for(char j='1'; j<='5'; j++)
				EXPECT_EQ(D[g.Id(i)][g.Id(j)], expd[i-'1'][j-'1']);
	}
//////////////////////////////////////////////////////////////////////////
	{
		// case from CLRS Figure 26.6
		misc::Graph<char, misc::directed, misc::keyMap, int> g;
		char de[2*9] = {'s','1','s','2','2','1', '1','3','2','4', '3','2',
			'4','3','4','t','3','t'};
		int w[9] = {16,13,4, 12,14, 9, 7,4,20};
		for (int i=0; i<9; i++)
			g.addEdge(de[2*i], de[2*i+1], w[i]);

		EXPECT_EQ(g.Edmonds_Karp('s', 't'), 23);
	}
}