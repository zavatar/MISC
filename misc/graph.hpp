#ifndef misc_graph
#define misc_graph

#include "boost/pending/disjoint_sets.hpp"

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// adjacency lists & adjacency matrices
// 1. BFS, Breadth-first tree, Shortest paths
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
// Bipartite: DFS or BFS
// http://en.wikipedia.org/wiki/Bipartite_graph
//
//////////////////////////////////////////////////////////////////////////

	class Graph {
		public:

			typedef int id_type;
			typedef float weight_type;

			Graph(){}
			Graph(int V);

			void clear();

			void resize(int V);

			bool visited(id_type v);

			void addEdge(id_type u, id_type v, weight_type w = 1);

			template <typename Fun>
			void foreachAdj(id_type v, Fun fn);

			template <typename Fun>
			void foreachEdge(Fun fn);

			template <typename Fun>
			void BFS(Fun fn);

			template <typename startFun, typename finishFun>
			void DFS(startFun sf, finishFun ff);

			template <typename Fun>
			void BFS_visit(id_type s, Fun fn);

			template <typename startFun, typename finishFun>
			void DFS_visit(id_type v, startFun sf, finishFun ff);

			template <typename Fun>
			void topological_sort(Fun fn);

			void SCC();

			template <typename Fun>
			weight_type Kruskal_MST(Fun fn);

			template <typename Fun>
			weight_type Prim_MST(Fun fn);

		private:

			enum color_type {white, gray, green, red, black};

			struct Edge {
				id_type u;
				weight_type w;
				Edge():w(1){}
				Edge(id_type _u,weight_type _w):u(_u),w(_w){}
			};

			struct Vertex {
				color_type color;
				std::list<Edge> adj;
				Vertex():color(white){}
			};

			std::vector<Vertex> root;

			color_type getColor(id_type v);

			void setColor(id_type v, color_type c);

			void clearColor();

			void transpose(Graph& gt);

	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "graph.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_graph
