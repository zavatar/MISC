#ifndef misc_balanced_tree
#define misc_balanced_tree

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// Search Tree: SEARCH, MINIMUM, MAXIMUM, PREDECESSOR, SUCCESSOR, INSERT, DELETE.
//				Using a ST both as a dictionary and as a priority queue.
//
// Binary Search Trees: BST
//
// Balanced BST:	AVL
//					B_trees/2-3-4 trees
//					Red_Black trees (RBT)
//					Skip Lists
//					Treaps
//					*Splay tree
//					*Scapegoat tree
//					*Size Balanced tree (SBT)
//
// Augmenting BT:	Interval Tree
//					Segment Tree
//					Range Tree
//
// Binary space partitioning (BSP) trees: Quadtree, Octree, k-d tree.
//
//////////////////////////////////////////////////////////////////////////

	template <typename T>
	struct bst_node {
		T key;
		bst_node *p;
		bst_node *l;
		bst_node *r;
	};

	template <typename T>
	struct avl_node {
		T key;
		avl_node *p;
		avl_node *l;
		avl_node *r;
		int h;
	};

	// Could extract an abstract interface class BT.
	// BT(key,l,r) ---> interfaces(insert,delete) && pre/in/post order walk
	//     |
	//    \|/
	// BST(+parent) ---> search,minimum,maximum,predecessor,successor,insert,delete
	//     |       \______________________
	//    \|/                             \|
	// AVL(+height) ---> insert,delete; RBT(+color) ---> insert,delete;
	template <typename T>
	class dynamic_set {
		public:
			typedef typename T::value_type value_type;

			value_type getMin(){ return obj.getMin(); }

			value_type getMax(){ return obj.getMax(); }

			value_type getPredecessor(value_type val){ return obj.getPredecessor(val); }

			value_type getSuccessor(value_type val){ return obj.getSuccessor(val); }

			void insert(value_type val){ obj.insert(val); }

			bool del(value_type val){ return obj.del(val); }

			bool find(value_type val){ return obj.find(val); }

			// virtual template interface ?
			// http://stackoverflow.com/questions/2354210/can-a-member-function-template-be-virtual
			//  type erasure
			// http://www.cplusplus.com/articles/oz18T05o/
			template <typename Fun>
			void traversal(Fun fn) { obj.traversal(fn); }

			T* getObj(){ return &obj; }

		private:
			T obj;
	};

	template <typename T, typename node_type = bst_node<T>>
	class BST {
		public:
			typedef T value_type;
			typedef BST<T, node_type> base_type;
			typedef node_type* node_pointer;
			#   if(MISC_ISVC)
			typedef typename pool_alloc<node_type>::type alloc_type;
			#   elif(MISC_ISGCC)
			typedef pool_alloc<node_type> alloc_type;
			#   endif

			BST(){ root = NULL; }
			virtual ~BST(){ destroy(root); }

			T getMin(){ return minimum(root)->key; }

			T getMax(){ return maximum(root)->key; }

			T getPredecessor(T val);

			T getSuccessor(T val);

			void insert(T val);

			bool del(T val);

			bool find(T val){ return search(val)!=NULL; }

			template <typename Fun>
			void traversal(Fun fn){ inorder(fn); }

			// Preorder Tree Walk
			template <typename Fun>
			void preorder(Fun fn);

			// Inorder Tree Walk
			template <typename Fun>
			void inorder(Fun fn);

			// Postorder Tree Walk
			template <typename Fun>
			void postorder(Fun fn);

		protected:

			node_pointer root;

			virtual void insertp(node_pointer z);

			virtual void deletep(node_pointer z);

			virtual void left_rotate(node_pointer x);

			virtual void right_rotate(node_pointer x);

		private:
			
			alloc_type alloc;

			node_pointer minimum(node_pointer x);

			node_pointer maximum(node_pointer x);

			node_pointer predecessor(node_pointer x);

			node_pointer successor(node_pointer x);

			void transplant(node_pointer u, node_pointer v);

			node_pointer search_r(T val);

			node_pointer search(T val);

			void destroy(node_pointer x);
	};

	// AVL
	template <typename T, typename node_type = avl_node<T>>
	class AVL : public BST<T, node_type> {
		public:
			typedef T value_type;
			typedef BST<T, node_type> base_type;
			typedef node_type* node_pointer;

			int height(node_pointer x);
		
		protected:

			virtual void insertp(node_pointer z);

			virtual void deletep(node_pointer z);

			virtual void left_rotate(node_pointer x);

			virtual void right_rotate(node_pointer x);

		private:

			void update_height(node_pointer x);

			void rebalance(node_pointer x);
	};

	// Red_Black trees (RBT)
	template <typename _Kty,
		typename _Pr = std::less<_Kty>,
		typename _Alloc = pool_alloc<_Kty> >
#if MISC_ISCXX11
		using red_black_tree = std::set<_Kty, _Pr, _Alloc>;
#else
	struct red_black_tree {
		typedef std::set<_Kty, _Pr, _Alloc> type;
	};
#endif

	// Skip Lists
	// http://igoro.com/archive/skip-lists-are-fascinating/
	// http://kunigami.wordpress.com/2012/09/25/skip-lists-in-python/
	template <typename T>
	class skip_lists {
		public:
			typedef T value_type;
			struct node_type {
				T key;
				std::vector<node_type*> lnxt;
				node_type(T k, int level) {
					key = k;
					lnxt.resize(level, NULL);
				}
			};
			typedef node_type* node_pointer;

			skip_lists() { head = new node_type(0, 1); }
			~skip_lists() { delete head; }

			T getMin(){ return head->lnxt[0] == NULL ? NULL : head->lnxt[0]->key; }

			T getMax(){
				node_pointer cur = head;
				for (int i=head->lnxt.size()-1; i>=0; i--)
					for (; cur->lnxt[i] != NULL; cur = cur->lnxt[i]);
				return cur->key;
			}

			T getPredecessor(T val);

			T getSuccessor(T val);

			void insert(T val);

			bool del(T val);

			bool find(T val){ return search(val)!=NULL; }

			template <typename Fun>
			void traversal(Fun fn);

		private:

			node_pointer head;

			node_pointer search(T val);
	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "balanced_tree.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_balanced_tree
