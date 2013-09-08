#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(Graph_Test, Standard)
{
	// 0--1  2
	// |  |_/|
	// 3--4  5
	misc::Graph g(6);
	g.addEdge(0,1);
	g.addEdge(2,4);
	g.addEdge(2,5);
	g.addEdge(0,3);
	g.addEdge(1,4);
	g.addEdge(4,3);

	auto dummyfun = [](int){};
	auto printfun = [](int v){printf("%d\t", v);};

	g.DFS(dummyfun, dummyfun);

	g.BFS(dummyfun);

	g.topological_sort(dummyfun);

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