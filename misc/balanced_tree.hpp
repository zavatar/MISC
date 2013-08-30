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
//					Treaps (high probability balanced?)
//					*Splay tree
//					*Scapegoat tree
//					*Size Balanced tree (SBT) (order statistic tree)
//
// Augmenting BT:	Order statistic tree (based on AVL)
//					Interval Tree (based on AVL)
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

			value_type getPredecessor(value_type val)
			{ return obj.getPredecessor(val); }

			value_type getSuccessor(value_type val)
			{ return obj.getSuccessor(val); }

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

			void clear(){ destroy(root); root = NULL;}

		protected:

			node_pointer root;

			alloc_type alloc;

			virtual void insertp(node_pointer z);

			virtual void deletep(node_pointer &z);

			// should abstract to balanced BST interface
			virtual void left_rotate(node_pointer x);

			virtual void right_rotate(node_pointer x);

			void transplant(node_pointer u, node_pointer v);

			node_pointer minimum(node_pointer x);

			node_pointer maximum(node_pointer x);

			node_pointer predecessor(node_pointer x);

			node_pointer successor(node_pointer x);

			node_pointer search_r(T val);

			node_pointer search(T val);

		private:

			void destroy(node_pointer x);
	};

	// AVL
	template <typename T, typename node_type = avl_node<T>>
	class AVL : public BST<T, node_type> {
		public:
			typedef T value_type;
			typedef BST<T, node_type> base_type;
			typedef node_type* node_pointer;

			bool isbalanced(node_pointer x){ 
				return x == NULL ? true : abs(height(x->l) - height(x->r)) <= 1; 
			}
		
		protected:

			virtual void insertp(node_pointer z);

			virtual void deletep(node_pointer &z);

			virtual void left_rotate(node_pointer x);

			virtual void right_rotate(node_pointer x);

			virtual void update_from_lr(node_pointer x){}

		private:

			int height(node_pointer x);

			void update_height(node_pointer x);

			void rebalance(node_pointer x);
	};

	// Red_Black trees (RBT)
	template <typename T>
	class red_black_tree {
		public:
			typedef T value_type;
			typedef struct {
				T key;
			} node_type;
			typedef node_type* node_pointer;
			#   if(MISC_ISVC)
			typedef typename pool_alloc<T>::type _Alloc;
			#   elif(MISC_ISGCC)
			typedef pool_alloc<T> _Alloc;
			#   endif
			typedef std::set<T, std::less<T>, _Alloc> proxy_type;

			T getMin(){ return *(rbt.begin()); }

			T getMax(){ return *(rbt.rbegin()); }

			T getPredecessor(T val){
				auto p = rbt.find(val);
				if (p == rbt.end()) throw 0;
				if (p == rbt.begin()) throw 1;
				return *(--p);
			}

			T getSuccessor(T val){
				auto p = rbt.find(val);
				if (p == rbt.end()) throw 0;
				if (++p == rbt.end()) throw 1;
				return *p;
			}

			void insert(T val){ rbt.insert(val); }

			bool del(T val){ return rbt.erase(val)>0; }

			bool find(T val){ return rbt.find(val)!=rbt.end(); }

			template <typename Fun>
			void traversal(Fun fn){
				std::for_each(rbt.begin(), rbt.end(), [&fn](T key){
					node_type wrapper;
					wrapper.key = key;
					fn(&wrapper);
				});
			}

			void clear(){ rbt.clear(); }

		private:

			proxy_type rbt;
	};

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

	template <typename T>
	struct sbt_node {
		T key;
		sbt_node *p;
		sbt_node *l;
		sbt_node *r;
		int s;
	};

	template <typename T, typename node_type = sbt_node<T>>
	class SBT : public BST<T, node_type> {
		public:
			typedef T value_type;
			typedef BST<T, node_type> base_type;
			typedef node_type* node_pointer;

			bool isbalanced(node_pointer x){
				if (x == NULL) return true;
				else return size(x->r) >= std::max(lsize(x->l), rsize(x->l)) && // property a
					size(x->l) >= std::max(lsize(x->r), rsize(x->r)); // property b
			}

			T getNth(int r);

		protected:

			virtual void insertp(node_pointer z);

			//virtual void deletep(node_pointer &z);

			virtual void left_rotate(node_pointer x);

			virtual void right_rotate(node_pointer x);

		private:

			node_pointer nth(node_pointer p, int r);

			int size(node_pointer x);

			int lsize(node_pointer x);

			int rsize(node_pointer x);

			void update_size(node_pointer x);

			void maintain(node_pointer x, bool f);
	};

//////////////////////////////////////////////////////////////////////////

	template <typename T>
	struct statistics_node {
		T key;
		int s;
		statistics_node *p;
		statistics_node *l;
		statistics_node *r;
		int h;
	};

	template <typename T, typename node_type = statistics_node<T>>
	class order_statistic_tree : public AVL<T, node_type> {
		public:
			typedef T value_type;
			typedef AVL<T, node_type> base_type;
			typedef node_type* node_pointer;

			T getNth(int r);

		protected:

			virtual void insertp(node_pointer z);

			virtual void update_from_lr(node_pointer x);

		private:

			node_pointer nth(node_pointer p, int r);

			int size(node_pointer x);
	};

	template <typename T>
	struct interval {
		union {T key;T low;};
		T high;
		T maxh;
		interval *p;
		interval *l;
		interval *r;
		int h;
	};

	template <typename T, typename node_type = interval<T>>
	class itv_tree : public AVL<T, node_type> {
		public:
			typedef T value_type;
			typedef AVL<T, node_type> base_type;
			typedef node_type* node_pointer;

			void insert(T val);

			void insert(T low, T high);

			bool find(T val){ return search(val, val)!=NULL; }

			bool find(T low, T high){ return search(low, high)!=NULL; }

		protected:

			virtual void update_from_lr(node_pointer x);

		private:

			T maxhigh(node_pointer x);

			node_pointer search(T low, T high);

			bool isOverlap(node_pointer x, T low, T high);
	};

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "balanced_tree.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_balanced_tree
