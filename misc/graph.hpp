#ifndef misc_graph
#define misc_graph

#include <boost/config.hpp>
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

	struct undirected {
		static const bool value = true;
	};

	struct directed {
		static const bool value = false;
	};

	template <typename Key, typename id_type>
	class keyInt0 {};

	template <>
	class keyInt0<int, int> {
		public:
			int keymap(int&k) { return k; }
			int addkey(int&k) { return k; }
			void clearkey(){}
	};

	template <typename Key, typename id_type>
	class keyMap {
		public:
			typedef std::unordered_map<Key, id_type> map_type;

			id_type keymap(Key&k) { return map[k]; }

			id_type addkey(Key&k) { 
				if (map.find(k) == map.end())
					map[k]= map.size();
				return map[k];
			}

			void clearkey() { map.clear(); }

		private:

			map_type map;
	};

	// using default template template parameters
	template <typename Key,
		typename Dir = undirected,
		template<typename T,typename U> class KeyPolicy = keyMap,
		typename weight_type = float,
		typename distance_type = float,
		template<typename T> class Alloc = pool_alloc,
		template<typename T,typename U> class AdjE = std::vector>
	class Graph : public KeyPolicy<Key, int> {
		public:

			// http://stackoverflow.com/questions/5286922/g-template-parameter-error
			using KeyPolicy<Key, int>::keymap;
			using KeyPolicy<Key, int>::addkey;
			using KeyPolicy<Key, int>::clearkey;

			typedef int id_type;

			enum color_type {white, gray, green, red, black, invisible};

			struct Edge {
				id_type u;
				weight_type w;
				distance_type d;
				Edge(id_type _u,weight_type _w,distance_type _d)
					:u(_u),w(_w),d(_d){}
			};

			typedef AdjE<Edge,Alloc<Edge>> Elist_type;

			struct Vertex {
				Key key;
				color_type color;
				Elist_type adj;
				Vertex():color(invisible){}
				Vertex(Key&k):key(k),color(invisible){}
			};

			typedef std::vector<Vertex> Vlist_type;

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

			color_type& Color(id_type& v);

			void clearColor();

			void transpose(Graph& gt);

			bool visited(id_type v);

			bool visible(id_type v);

			void resize(int V);

			void _updateEdge(id_type u, id_type v, weight_type w, distance_type d);

			template <typename Fun>
			void _foreachVertex(Fun fn);

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
		typename Dir /*= undirected*/,\
		template<typename T,typename U> class KeyPolicy /*= keyMap*/,\
		typename weight_type /*= float*/,\
		typename distance_type /*= float*/,\
		template<typename T> class Alloc /*= std::allocator*/,\
		template<typename T,typename U> class AdjE /*= std::vector*/>\


#define GraphHead Graph<Key, Dir, KeyPolicy, weight_type, distance_type, Alloc, AdjE>::


} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "graph.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_graph
