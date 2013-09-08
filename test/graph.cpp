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

	g.topological_sort(printfun);
}