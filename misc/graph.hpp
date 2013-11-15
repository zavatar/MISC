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
// http://www.boost.org/doc/libs/1_54_0/libs/disjoint_sets/disjoint_sets.html
// Disjoint Sets: Find, Union, Make_Set
//  1. Linked lists, O(n) Find or Union
//  2. Forests, (union by rank and path compression), O(amortized const) Find and Union
//
//////////////////////////////////////////////////////////////////////////

	struct undirected {
		static const bool value = true;
	};

	struct directed {
		static const bool value = false;
	};

	template <typename _Key, typename id_type>
	class keyInt0 {};

	template <>
	class keyInt0<int, int> {
		public:
			int Key(int v) { return v; }
			int Id(const int&k) { return k; }
		protected:
			int addkey(int&k) { return k; }
			void clearkey(){}
	};

	template <typename _Key, typename id_type>
	class keyMap {
		public:
			_Key Key(id_type v) { return keys[v]; }
			id_type Id(const _Key&k) { return maps[k]; }
		protected:
			id_type addkey(const _Key&k) { 
				if (maps.find(k) == maps.end()) {
					keys.push_back(k);
					maps[k]= maps.size();
				}
				return maps[k];
			}
			void clearkey() { keys.clear(); maps.clear(); }
		private:
			std::unordered_map<_Key, id_type> maps;
			std::vector<_Key> keys;
	};

	// using default template template parameters
	template <typename _Key,
		typename _Dir = undirected,
		template<typename,typename> class _KeyPolicy = keyMap,
		typename _Weight = float,
		typename _Dist = float,
		template<typename> class _Alloc = pool_alloc>
	class Graph : public _KeyPolicy<_Key, int> {
		public:

			// http://stackoverflow.com/questions/5286922/g-template-parameter-error
			using _KeyPolicy<_Key, int>::Id;
			using _KeyPolicy<_Key, int>::addkey;
			using _KeyPolicy<_Key, int>::clearkey;

			typedef int id_type;

			enum color_type {white, gray, green, red, black, invisible};

			struct Edge {
				_Weight w;
				_Dist d;
				Edge(){}
				Edge(_Weight _w,_Dist _d):w(_w),d(_d){}
			};

			typedef std::unordered_map<id_type,Edge,std::hash<id_type>,
				std::equal_to<id_type>,_Alloc<std::pair<const id_type,Edge>>> Elist_type;

			struct Vertex {
				color_type color;
				id_type parent;
				Elist_type adj;
				Vertex():color(invisible){}
			};

			typedef std::vector<Vertex> Vlist_type;

			Graph(){}
			Graph(int V);

			void clear();

			void clearColor();

			bool Visited(_Key v);
			
			void addVertex(_Key kv);

			void connect(_Key ku, _Key kv, _Weight w = 1, _Dist d = 1);

			void addEdge(_Key ku, _Key kv, _Weight w = 1, _Dist d = 1);

			void disconnect(_Key ku, _Key kv);

			bool hasEdge(_Key ku, _Key kv);

			const Edge& getEdge(_Key ku, _Key kv);

			template <typename Fun>
			void BFS(Fun fn);

			template <typename startFun, typename finishFun>
			void DFS(startFun sf, finishFun ff);

			template <typename Fun>
			void BFS_visit(_Key ks, Fun fn);

			template <typename startFun, typename finishFun>
			void DFS_visit(_Key kv, startFun sf, finishFun ff);

			template <typename Fun>
			void foreachPath(_Key kv, Fun fn);

			template <typename Fun>
			void foreachAdj(_Key kv, Fun fn);

			// O(V+E) time
			template <typename Fun>
			void topological_sort(Fun fn);

			// strongly connected components
			int SCC();

			// O(ElgE) == O(ElgV) time
			template <typename Fun>
			_Weight Kruskal_MST(Fun fn);

			// O(VlgV + ElgV) = O(ElgV) time
			// if using Fibonacci Heap, O(E+VlgV) time
			template <typename Fun>
			_Weight Prim_MST(Fun fn);

			// O(V+E) time
			_Dist DAGShortestPath(_Key ks, _Key kt);

			// O((V+E)lgV) time
			// if using Fibonacci Heap, O(E+VlgV) time
			_Dist Dijkstra(_Key ks, _Key kt);
			void DijkstraAll(_Key ks, std::vector<_Dist> &D);

			// O(VE) time
			_Dist Bellman_Ford(_Key ks, _Key kt);

			// O(V^3) time
			// no negative-weight cycle
			void Floyd_Warshall(std::vector<std::vector<_Dist>> &D);

			// O(VE^2) = O(VE)*[BFS O(E)]
			_Weight Edmonds_Karp(_Key ks, _Key kt);

		private:

			Vlist_type root;

			color_type& Color(id_type& v);

			id_type& Parent(id_type& v);

			void transpose(Graph& gt);

			bool visited(id_type v);

			bool visible(id_type v);

			void resize(int V);

			template <typename Fun>
			void _foreachVertex(Fun fn);

			template <typename Fun>
			void _foreachPath(id_type v, Fun fn);

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
	template <typename _Key,\
		typename _Dir /*= undirected*/,\
		template<typename,typename> class _KeyPolicy /*= keyMap*/,\
		typename _Weight /*= float*/,\
		typename _Dist /*= float*/,\
		template<typename> class _Alloc /*= std::allocator*/>


#define GraphHead Graph<_Key, _Dir, _KeyPolicy, _Weight, _Dist, _Alloc>::

//////////////////////////////////////////////////////////////////////////

	template <typename _Key,
		template<typename,typename> class _KeyPolicy = keyMap>
	class DisjointSets : public _KeyPolicy<_Key, int> {
		public:

			// http://stackoverflow.com/questions/5286922/g-template-parameter-error
			using _KeyPolicy<_Key, int>::Id;
			using _KeyPolicy<_Key, int>::addkey;
			using _KeyPolicy<_Key, int>::clearkey;

			typedef int id_type;

			DisjointSets(){}

			template <class InputIterator>
			DisjointSets(InputIterator first, InputIterator last);

			void makeSet(_Key kv);

			_Key findSet(_Key kv);

			bool isConnected(_Key ku, _Key kv);

			// union
			void link(_Key ku, _Key kv);

			int getCount() { return count; }

		private:

			// forests structure
			std::vector<id_type> parent;
			std::vector<int> rank;
			int count;

			id_type _findSet(id_type v);
	};

#define DisjointSetsTemplate \
	template <typename _Key,\
		template<typename,typename> class _KeyPolicy /*= keyMap*/>


#define DisjointSetsHead DisjointSets<_Key, _KeyPolicy>::

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "graph.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_graph
