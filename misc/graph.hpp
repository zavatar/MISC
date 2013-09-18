#ifndef misc_graph
#define misc_graph

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/pending/disjoint_sets.hpp>

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

// vector, list, set, hash; direct, undirect, bidirect; 
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> VVG;

	template <typename Key,
		template<class T,class U> class AdjE>
	class Graph {
		public:

			typedef int id_type;
			typedef float weight_type;

			enum color_type {white, gray, green, red, black};

			struct Edge {
				id_type u;
				weight_type w;
				Edge():w(1){}
				Edge(id_type _u,weight_type _w):u(_u),w(_w){}
			};

			struct Vertex {
				Key key;
				color_type color;
				AdjE<Edge,std::allocator<Edge>> adj;
				Vertex():color(white){}
				Vertex(Key&k):key(k),color(white){}
			};

			
			typedef std::vector<Vertex> Vlist_type;
			typedef std::unordered_map<Key, id_type> keymap_type;

			Graph(){}
			Graph(int V);

			void clear();

			bool Visited(Key v);
			
			void addEdge(Key ku, Key kv, weight_type w = 1);

			template <typename Fun>
			void BFS(Fun fn);

			template <typename startFun, typename finishFun>
			void DFS(startFun sf, finishFun ff);

			template <typename Fun>
			void BFS_visit(Key ks, Fun fn);

			template <typename startFun, typename finishFun>
			void DFS_visit(Key kv, startFun sf, finishFun ff);

			template <typename Fun>
			void topological_sort(Fun fn);

			// strongly connected components
			void SCC();

			template <typename Fun>
			weight_type Kruskal_MST(Fun fn);

			template <typename Fun>
			weight_type Prim_MST(Fun fn);

		private:

			Vlist_type root;

			keymap_type keymap;

			color_type getColor(id_type v);

			void setColor(id_type v, color_type c);

			void clearColor();

			void transpose(Graph& gt);

			bool visited(id_type v);

			void resize(int V);

			id_type insert(Key& k);

			template <typename Fun>
			void foreachAdj(id_type v, Fun fn);

			template <typename Fun>
			void foreachEdge(Fun fn);

			template <typename Fun>
			void _BFS_visit(id_type s, Fun fn);

			template <typename startFun, typename finishFun>
			void _DFS_visit(id_type v, startFun sf, finishFun ff);
	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "graph.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_graph
