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
	template <typename T, typename node_type = bst_node<T>>
	class BST {
		public:
			typedef T value_type;
			typedef BST<T, node_type> base_type;
			typedef node_type* node_pointer;
			typedef typename pool_alloc<node_type >MISC_TALIAS alloc_type;

			BST(){ root = NULL; }
			~BST(){ destroy(root); }

			T getMin(){ return minimum(root)->key; }

			T getMax(){ return maximum(root)->key; }

			T getPredecessor(T val);

			T getSuccessor(T val);

			void insert(T val);

			bool del(T val);

			bool find(T val){ return search(val)!=NULL; }

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

		private:

			void update_height(node_pointer x);

			void left_rotate(node_pointer x);

			void right_rotate(node_pointer x);

			void rebalance(node_pointer x);
	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "balanced_tree.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_balanced_tree
