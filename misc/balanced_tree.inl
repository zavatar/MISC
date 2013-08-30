namespace misc{

	template <typename T, typename node_type>
	typename BST<T,node_type>::node_pointer BST<T,node_type>::minimum( node_pointer x )
	{
		while (x->l != NULL)
			x = x->l;
		return x;
	}

	template <typename T, typename node_type>
	typename BST<T,node_type>::node_pointer BST<T,node_type>::maximum( node_pointer x )
	{
		while (x->r != NULL)
			x = x->r;
		return x;
	}

	template <typename T, typename node_type>
	typename BST<T,node_type>::node_pointer BST<T,node_type>::predecessor( node_pointer x )
	{
		if (x->l != NULL)
			return maximum(x->l);
		node_pointer y = x->p;
		while (y != NULL && x == y->l) {
			x = y;
			y = y->p;
		}
		return y;
	}

	template <typename T, typename node_type>
	typename BST<T,node_type>::node_pointer BST<T,node_type>::successor( node_pointer x )
	{
		if (x->r != NULL)
			return minimum(x->r);
		node_pointer y = x->p;
		while (y != NULL && x == y->r) {
			x = y;
			y = y->p;
		}
		return y;
	}

	template <typename T, typename node_type>
	T BST<T,node_type>::getPredecessor( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) throw 0;
		p = predecessor(p);
		if (p == NULL) throw 1;
		return p->key;
	}

	template <typename T, typename node_type>
	T BST<T,node_type>::getSuccessor( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) throw 0;
		p = successor(p);
		if (p == NULL) throw 1;
		return p->key;
	}

	template <typename T, typename node_type>
	void BST<T,node_type>::insert( T val )
	{
		node_pointer z = this->alloc.allocate(1);
		z->key = val; z->p = z->l = z->r = NULL;
		insertp(z);
	}

	template <typename T, typename node_type>
	void BST<T,node_type>::insertp( node_pointer z )
	{
		node_pointer x = root;
		node_pointer y = NULL;
		while (x != NULL) {
			y = x;
			if (z->key < x->key)
				x = x->l;
			else
				x = x->r;
		}
		z->p = y;
		if (y == NULL)
			root = z;
		else if (z->key < y->key)
			y->l = z;
		else
			y->r = z;
	}

	template <typename T, typename node_type>
	bool BST<T,node_type>::del( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) return false;
		deletep(p);
		return true;
	}

	template <typename T, typename node_type> template <typename Fun>
	void BST<T,node_type>::preorder( Fun fn )
	{
		std::function<void(node_pointer)> inorder_fun = 
			[&fn, &inorder_fun](node_pointer node) {
				if (node == NULL) return;
				fn(node);
				inorder_fun(node->l);
				inorder_fun(node->r);
		};
		inorder_fun(root);
	}

	// http://stackoverflow.com/questions/5108359/how-do-i-define-a-template-function-within-a-template-class-outside-of-the-class
	template <typename T, typename node_type> template <typename Fun>
	void BST<T,node_type>::inorder( Fun fn )
	{
		std::function<void(node_pointer)> inorder_fun = 
			[&fn, &inorder_fun](node_pointer node) {
				if (node == NULL) return;
				inorder_fun(node->l);
				fn(node);
				inorder_fun(node->r);
		};
		inorder_fun(root);
	}

	template <typename T, typename node_type> template <typename Fun>
	void BST<T,node_type>::postorder( Fun fn )
	{
		std::function<void(node_pointer)> inorder_fun = 
			[&fn, &inorder_fun](node_pointer node) {
				if (node == NULL) return;
				inorder_fun(node->l);
				inorder_fun(node->r);
				fn(node);
		};
		inorder_fun(root);
	}

	template <typename T, typename node_type>
	void BST<T,node_type>::transplant( node_pointer u, node_pointer v )
	{
		if (u->p == NULL)
			root = v;
		else if (u == u->p->l)
			u->p->l = v;
		else
			u->p->r = v;
		if (v != NULL)
			v->p = u->p;
	}

	template <typename T, typename node_type>
	void BST<T,node_type>::deletep( node_pointer &z )
	{
		if (z->l == NULL)
			transplant(z, z->r);
		else if (z->r == NULL)
			transplant(z, z->l);
		else {
			node_pointer y = minimum(z->r);
			z->key = y->key;
			transplant(y, y->r); // y->l == NULL
			z = y;
		}
		node_pointer ret = z->p;
		this->alloc.deallocate(z, 1);
		z = ret;
	}

	template <typename T, typename node_type>
	void BST<T, node_type>::left_rotate( node_pointer x )
	{
		node_pointer y = x->r;
		y->p = x->p;
		if (y->p == NULL)
			this->root = y;
		else {
			if (y->p->l == x)
				y->p->l = y;
			else if (y->p->r == x)
				y->p->r = y;
		}
		x->r = y->l;
		if (x->r != NULL)
			x->r->p = x;
		y->l = x;
		x->p = y;
	}

	template <typename T, typename node_type>
	void BST<T, node_type>::right_rotate( node_pointer x )
	{
		node_pointer y = x->l;
		y->p = x->p;
		if (y->p == NULL)
			this->root = y;
		else {
			if (y->p->l == x)
				y->p->l = y;
			else if (y->p->r == x)
				y->p->r = y;
		}
		x->l = y->r;
		if (x->l != NULL)
			x->l->p = x;
		y->r = x;
		x->p = y;
	}

	template <typename T, typename node_type>
	typename BST<T,node_type>::node_pointer BST<T,node_type>::search_r( T val )
	{
		std::function<void(node_pointer)> search_fun = 
			[val, &search_fun](node_pointer node) {
				if (node == NULL || val == node->key) return node;
				if (val < node->key)
					return search_fun(node->l);
				else
					return search_fun(node->r);
			};
	}

	template <typename T, typename node_type>
	typename BST<T,node_type>::node_pointer BST<T,node_type>::search( T val )
	{
		node_pointer x = root;
		while (x != NULL && val != x->key) {
			if (val < x->key)
				x = x->l;
			else
				x = x->r;
		}
		return x;
	}

	template <typename T, typename node_type>
	void BST<T,node_type>::destroy( node_pointer x )
	{ // post order walk
		if (x != NULL) {
			destroy(x->l);
			destroy(x->r);
			this->alloc.deallocate(x, 1);
		}
	}

//////////////////////////////////////////////////////////////////////////

	template <typename T, typename node_type>
	void AVL<T,node_type>::insertp( node_pointer z )
	{
		BST<T,node_type>::insertp(z);
		rebalance(z);
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::deletep( node_pointer &z )
	{
		BST<T,node_type>::deletep(z);
		rebalance(z);
	}

	template <typename T, typename node_type>
	int AVL<T,node_type>::height( node_pointer x )
	{
		if (x == NULL) return -1;
		else return x->h;
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::update_height( node_pointer x )
	{
		x->h = std::max(height(x->l), height(x->r)) + 1;
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::left_rotate( node_pointer x )
	{
		BST<T,node_type>::left_rotate(x);
		update_height(x);
		update_height(x->p);
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::right_rotate( node_pointer x )
	{
		BST<T,node_type>::right_rotate(x);
		update_height(x);
		update_height(x->p);
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::rebalance( node_pointer x )
	{
		while (x != NULL) {
			update_height(x);
			if (height(x->l) >= 2+height(x->r)) {
				if (height(x->l->l) < height(x->l->r))
					left_rotate(x->l);
				right_rotate(x);
			} else if (height(x->r) >= 2+height(x->l)) {
				if (height(x->r->r) < height(x->r->l))
					right_rotate(x->r);
				left_rotate(x);
			}
			x = x->p;
		}
	}

//////////////////////////////////////////////////////////////////////////

	template <typename T>
	T skip_lists<T>::getPredecessor( T val )
	{
		node_pointer cur = head, pre = NULL;
		if (head->lnxt[0] == NULL || val < head->lnxt[0]->key) throw 0;
		for (int i=head->lnxt.size()-1; i>=0; i--) {
			for (; cur->lnxt[i] != NULL; cur = cur->lnxt[i]) {
				if (cur->lnxt[i]->key >= val) break;
				else pre = cur->lnxt[i];
			}
		}
		if (pre == NULL) throw 1;
		return pre->key;
	}

	template <typename T>
	T skip_lists<T>::getSuccessor( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) throw 0;
		if (p->lnxt[0] == NULL) throw 1;
		return p->lnxt[0]->key;
	}

	template <typename T>
	void skip_lists<T>::insert( T val )
	{
		int level = 0;
		while (rand()&1) {
			level++;
			if (level == head->lnxt.size()) {
				head->lnxt.push_back(NULL);
				break;//why?
			}
		}
		node_pointer newnode = new node_type(val, level+1);
		node_pointer cur = head;
		for (int i=head->lnxt.size()-1; i>=0; i--) {
			for (; cur->lnxt[i] != NULL; cur = cur->lnxt[i])
				if (cur->lnxt[i]->key > val)
					break;
			if (i <= level) {
				newnode->lnxt[i] = cur->lnxt[i];
				cur->lnxt[i] = newnode;
			}
		}
	}

	template <typename T>
	bool skip_lists<T>::del( T val )
	{
		node_pointer cur = head;
		bool found = false;
		for (int i=head->lnxt.size()-1; i>=0; i--) {
			for (; cur->lnxt[i] != NULL; cur = cur->lnxt[i]) {
				if (cur->lnxt[i]->key > val) break;
				if (cur->lnxt[i]->key == val) {
					found = true;
					cur->lnxt[i] = cur->lnxt[i]->lnxt[i];
					break;
				}
			}
		}
		return found;
	}

	template <typename T> template <typename Fun>
	void skip_lists<T>::traversal( Fun fn )
	{
		for (node_pointer cur = head->lnxt[0]; cur!=NULL; cur = cur->lnxt[0])
			fn(cur);
	}

	template <typename T>
	typename skip_lists<T>::node_pointer skip_lists<T>::search( T val )
	{
		node_pointer cur = head;
		for (int i=head->lnxt.size()-1; i>=0; i--) {
			for (; cur->lnxt[i] != NULL; cur = cur->lnxt[i]) {
				if (cur->lnxt[i]->key > val) break;
				if (cur->lnxt[i]->key == val) return cur->lnxt[i];
			}
		}
		return NULL;
	}

//////////////////////////////////////////////////////////////////////////

	template <typename T, typename node_type>
	int SBT<T, node_type>::size( node_pointer x )
	{
		if (x == NULL) return 0;
		else return x->s;
	}

	template <typename T, typename node_type /*= sbt_node<T>*/>
	int misc::SBT<T, node_type>::lsize( node_pointer x )
	{
		if (x == NULL) return -1;
		else return size(x->l);
	}

	template <typename T, typename node_type /*= sbt_node<T>*/>
	int misc::SBT<T, node_type>::rsize( node_pointer x )
	{
		if (x == NULL) return -1;
		else return size(x->r);
	}

	template <typename T, typename node_type>
	void SBT<T, node_type>::update_size( node_pointer x )
	{
		x->s = size(x->l) + size(x->r) + 1;
	}

	template <typename T, typename node_type>
	void SBT<T, node_type>::insertp( node_pointer z )
	{
		z->s = 1;
		std::function<void(node_pointer&)> insert_fun = 
			[z, &insert_fun, this](node_pointer& node) {
				node->s++;
				if (z->key < node->key) {
					if (node->l == NULL) {
						node->l = z;
						z->p = node;
					} else
						insert_fun(node->l);
					this->maintain(node, false);
				} else {
					if (node->r == NULL) {
						node->r = z;
						z->p = node;
					} else
						insert_fun(node->r);
					this->maintain(node, true);
				}
		};
		if (this->root == NULL)
			this->root = z;
		else
			insert_fun(this->root);
	}

	template <typename T, typename node_type>
	void SBT<T, node_type>::deletep( node_pointer &z )
	{
		std::function<void(node_pointer)> delete_fun = 
			[z, &delete_fun, this](node_pointer node) {
				if (node == NULL) return;
				if (z->key < node->key) {
					node->s--;
					delete_fun(node->l);
					this->maintain(node, true);
				} else if (z->key > node->key) {
					node->s--;
					delete_fun(node->r);
					this->maintain(node, false);
				} else {
					if (node->l == NULL) {
						this->transplant(node, node->r);
						this->alloc.deallocate(node, 1);
						return;
					} else if (node->r == NULL) {
						this->transplant(node, node->l);
						this->alloc.deallocate(node, 1);
						return;
					} else {
						node_pointer y = this->minimum(node->r);
						node->key = y->key;
						node->s--;
						delete_fun(node->r);
						this->maintain(node, false);
					}
				}
		};
		delete_fun(this->root);
	}

	template <typename T, typename node_type>
	void SBT<T, node_type>::left_rotate( node_pointer x )
	{
		BST<T,node_type>::left_rotate(x);
		update_size(x);
		update_size(x->p);
	}

	template <typename T, typename node_type>
	void SBT<T, node_type>::right_rotate( node_pointer x )
	{
		BST<T,node_type>::right_rotate(x);
		update_size(x);
		update_size(x->p);
	}

	template <typename T, typename node_type>
	void SBT<T, node_type>::maintain( node_pointer x, bool f )
	{
		if (x == NULL) return;
		if (f == false) {
			if (lsize(x->l) > size(x->r)) // case 1
				right_rotate(x);
			else if (rsize(x->l) > size(x->r)) { // case 2
				left_rotate(x->l);
				right_rotate(x);
			} else
				return;
		} else { // f == true
			if (rsize(x->r) > size(x->l)) // case 1'
				left_rotate(x);
			else if (lsize(x->r) > size(x->l)) { // case 2'
				right_rotate(x->r);
				left_rotate(x);
			} else
				return;
		}
		maintain(x->l, false);
		maintain(x->r, true);
		maintain(x, false);
		maintain(x, true);
	}



} // namespace misc
