namespace misc{

	template <typename T>
	typename BST<T>::node_pointer BST<T>::minimum( node_pointer x )
	{
		while (x->l != NULL)
			x = x->l;
		return x;
	}

	template <typename T>
	typename BST<T>::node_pointer BST<T>::maximum( node_pointer x )
	{
		while (x->r != NULL)
			x = x->r;
		return x;
	}

	template <typename T>
	typename BST<T>::node_pointer BST<T>::predecessor( node_pointer x )
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

	template <typename T>
	typename BST<T>::node_pointer BST<T>::successor( node_pointer x )
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

	template <typename T>
	T BST<T>::getPredecessor( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) throw;
		return predecessor(p)->key;
	}

	template <typename T>
	T BST<T>::getSuccessor( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) throw;
		return successor(p)->key;
	}

	template <typename T>
	void BST<T>::insert( T val )
	{
		node_pointer x = root;
		node_pointer y = NULL;
		node_pointer z = alloc.allocate(1);
		z->key = val; z->p = z->l = z->r = NULL;
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

	template <typename T>
	bool BST<T>::del( T val )
	{
		node_pointer p = search(val);
		if (p == NULL) return false;
		deletep(p);
		return true;
	}

	// http://stackoverflow.com/questions/5108359/how-do-i-define-a-template-function-within-a-template-class-outside-of-the-class
	template <typename T> template <typename Fun>
	void BST<T>::inorder( Fun fn )
	{
		std::function<void(node_pointer)> inorder_fun = 
			[&fn, &inorder_fun](node_pointer node) {
				if (node == NULL) return;
				inorder_fun(node->l);
				fn(node->key);
				inorder_fun(node->r);
		};
		inorder_fun(root);
	}

	template <typename T>
	void BST<T>::transplant( node_pointer u, node_pointer v )
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

	template <typename T>
	void BST<T>::deletep( node_pointer z )
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
		alloc.deallocate(z, 1);
	}

	template <typename T>
	typename BST<T>::node_pointer BST<T>::search_r( T val )
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

	template <typename T>
	typename BST<T>::node_pointer BST<T>::search( T val )
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

	template <typename T>
	void misc::BST<T>::destroy( node_pointer x )
	{ // post order walk
		if (x != NULL) {
			destroy(x->l);
			destroy(x->r);
			alloc.deallocate(x, 1);
		}
	}

} // namespace misc
