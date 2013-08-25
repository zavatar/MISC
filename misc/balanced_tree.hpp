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
	class BST {
		public:
			typedef struct bt_node {
				T key;
				bt_node *p;
				bt_node *l;
				bt_node *r;
			} node_type;
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

			// Inorder Tree Walk
			template <typename Fun>
			void inorder(Fun fn);

		private:
			node_pointer root;
			alloc_type alloc;

			node_pointer minimum(node_pointer x);

			node_pointer maximum(node_pointer x);

			node_pointer predecessor(node_pointer x);

			node_pointer successor(node_pointer x);

			void transplant(node_pointer u, node_pointer v);

			void deletep(node_pointer z);

			node_pointer search_r(T val);

			node_pointer search(T val);

			void destroy(node_pointer x);
	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "balanced_tree.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_balanced_tree
