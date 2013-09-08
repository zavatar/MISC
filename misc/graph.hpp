#ifndef misc_graph
#define misc_graph

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// adjacency lists & adjacency matrices
// 1. BFS, Breadth-first tree
// 2. DFS, topologically sorting (DAG, directed acyclic graph)
//         strongly connected components (SCC)
// 3. MST, Prim & Kruskal
// 4. Single-Source Shortest Paths, Bellman-Ford(negative), DAG, Dijkstra,
//                                  Difference Constraints
// 5. All-Pairs Shortest Paths, Floyd-Warshall, Johnson(Sparse)
// 6. Maximum Flow, Ford-Fulkerson, Edmonds-Karp, Push-relabel
//                  max-flow min-cut theorem (graphcut),
//                  Maximum bipartite matching
//
//////////////////////////////////////////////////////////////////////////

	class Graph {
		public:

			typedef int id_type;

			Graph(){}
			Graph(int V);

			void clear();

			void resize(int V);

			bool visited(id_type v);

			void addEdge(id_type u, id_type v);

			template <typename Fun>
			void BFS(Fun fn);

			template <typename Fun>
			void BFS(id_type v, Fun fn);

			template <typename startFun, typename finishFun>
			void DFS(startFun sf, finishFun ff);

			template <typename startFun, typename finishFun>
			void DFS(id_type v, startFun sf, finishFun ff);

			template <typename Fun>
			void BFS_visit(id_type s, Fun fn);

			template <typename startFun, typename finishFun>
			void DFS_visit(id_type v, startFun sf, finishFun ff);

			template <typename Fun>
			void topological_sort(Fun fn);

			void SCC();

		private:

			enum color_type {white, gray, green, red, black};

			std::vector<std::list<id_type>> adjs;

			std::vector<color_type> colors;

			std::vector<id_type> parents;

			void resetcp();

			void transpose(Graph& gt);

	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "graph.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_graph
