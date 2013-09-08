#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(Graph_Test, Standard)
{
	// 0--1  2
	// |  |_/|
	// 3--4  5
	misc::Graph g;
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
	int e[28] = {0,1,1,2,2,3,3,2,4,0,1,4,1,5,2,6,3,7,4,5,5,6,6,5,6,7,7,7};
	for (int i=0; i<28; i+=2)
		g.addEdge(e[i], e[i+1]);
	
	g.SCC();

	g.clear();
}