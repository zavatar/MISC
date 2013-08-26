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
		if (p == NULL) throw;
		return predecessor(p)->key;
	}

	template <typename T, typename node_type>
	T BST<T,node_type>::getSuccessor( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) throw;
		return successor(p)->key;
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
	void BST<T,node_type>::deletep( node_pointer z )
	{
		if (z->l == NULL)
			transplant(z, z->r);
		else if (z->r == NULL)
			transplant(z, z->l);
		else {
			node_pointer y = minimum(z->r);
			if (y->p != z) {
				transplant(y, y->r);
				y->r = z->r;
				y->r->p = y;
			}
			transplant(z, y);
			y->l = z->l;
			y->l->p = y;
		}
		this->alloc.deallocate(z, 1);
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
	void AVL<T,node_type>::deletep( node_pointer z )
	{
		node_pointer p = z->p;
		BST<T,node_type>::deletep(z);
		rebalance(p);
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
		x->h = 
#ifndef max
		std::
#endif // !max
		max(height(x->l), height(x->r)) + 1;
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::left_rotate( node_pointer x )
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
		update_height(x);
		update_height(y);
	}

	template <typename T, typename node_type>
	void AVL<T,node_type>::right_rotate( node_pointer x )
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
		update_height(x);
		update_height(y);
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

} // namespace misc
