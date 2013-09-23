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

	struct undirected {
		static const bool value = true;
	};

	struct directed {
		static const bool value = false;
	};

	template <typename Key,
		template<class T,class U> class AdjE,
		typename Dir = undirected,
		typename weight_type = float,
		typename distance_type = float>
	class Graph {
		public:

			typedef int id_type;

			enum color_type {white, gray, green, red, black};

			struct Edge {
				id_type u;
				weight_type w;
				distance_type d;
				//Edge():w(1),d(1){}
				Edge(id_type _u,weight_type _w,distance_type _d)
					:u(_u),w(_w),d(_d){}
			};

			typedef AdjE<Edge,std::allocator<Edge>> Elist_type;

			struct Vertex {
				Key key;
				color_type color;
				Elist_type adj;
				Vertex():color(white){}
				Vertex(Key&k):key(k),color(white){}
			};

			
			typedef std::vector<Vertex> Vlist_type;
			typedef std::unordered_map<Key, id_type> keymap_type;

			Graph(){}
			Graph(int V);

			void clear();

			bool Visited(Key v);
			
			void addVertex(Key kv);

			template <bool isUpdate>
			void connect(Key ku, Key kv, weight_type w = 1, distance_type d = 1);

			void addEdge(Key ku, Key kv, weight_type w = 1, distance_type d = 1);

			void updateEdge(Key ku, Key kv, weight_type w = 1, distance_type d = 1);

			template <typename Fun>
			void BFS(Fun fn);

			template <typename startFun, typename finishFun>
			void DFS(startFun sf, finishFun ff);

			template <typename Fun>
			void BFS_visit(Key ks, Fun fn);

			template <typename startFun, typename finishFun>
			void DFS_visit(Key kv, startFun sf, finishFun ff);

			template <typename Fun>
			void foreachAdj(Key kv, Fun fn);

			// O(V+E) time
			template <typename Fun>
			void topological_sort(Fun fn);

			// strongly connected components
			void SCC();

			// O(ElgE) == O(ElgV) time
			template <typename Fun>
			weight_type Kruskal_MST(Fun fn);

			// O(VlgV + ElgV) = O(ElgV) time
			// if using Fibonacci Heap, O(E+VlgV) time
			template <typename Fun>
			weight_type Prim_MST(Fun fn);

			// O(V+E) time
			distance_type DAGShortestPath(Key ks, Key kt);

			// O((V+E)lgV) time
			// if using Fibonacci Heap, O(E+VlgV) time
			distance_type Dijkstra(Key ks, Key kt);
			void DijkstraAll(Key ks, std::vector<distance_type> &D);

			// O(VE) time
			distance_type Bellman_Ford(Key ks, Key kt);

		private:

			Vlist_type root;

			keymap_type keymap;

			color_type getColor(id_type v);

			void setColor(id_type v, color_type c);

			void clearColor();

			void transpose(Graph& gt);

			bool visited(id_type v);

			void resize(int V);

			void _updateEdge(id_type u, id_type v, weight_type w, distance_type d);

			template <typename Fun>
			void _foreachAdj(id_type v, Fun fn);

			template <typename Fun>
			void _foreachAdjE(id_type v, Fun fn);

			template <typename Fun>
			void _foreachEdge(Fun fn);

			template <typename Fun>
			void _BFS_visit(id_type s, Fun fn);

			template <typename startFun, typename finishFun>
			void _DFS_visit(id_type v, startFun sf, finishFun ff);
	};

#define GraphTemplate \
	template <typename Key,\
	template<class T,class U> class AdjE,\
		typename Dir /*= undirected*/,\
		typename weight_type /*= float*/,\
		typename distance_type /*= float*/>

#define GraphHead Graph<Key, AdjE, Dir, weight_type, distance_type>::


} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "graph.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_graph
