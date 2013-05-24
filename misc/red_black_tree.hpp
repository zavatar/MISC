#ifndef misc_red_black_tree
#define misc_red_black_tree

#include <set>

namespace misc {

	template <typename _Kty,
		typename _Pr,
		typename _Alloc >
	class _TRB_traits
	{
	public:
		typedef _Kty key_type;
		typedef _Kty value_type;
		typedef _Pr key_compare;
		typedef _Alloc allocator_type;

		enum{ _Multi = true }; // red_black_tree support multi key

		typedef key_compare value_compare;

		static const _Kty& _Kfn(const value_type& _Val) {
			return (_Val);
		}
	};

	template <typename _Kty,
		typename _Pr = std::less<_Kty>,
		typename _Alloc = pool_alloc<_Kty> >
	class red_black_tree : public std::_Tree<_TRB_traits<_Kty, _Pr, _Alloc> >
	{
	public:
		typedef red_black_tree<_Kty, _Pr, _Alloc> _Myt;
		typedef std::_Tree<_TRB_traits<_Kty, _Pr, _Alloc> > _Mybase;
		typedef _Kty key_type;
		typedef _Pr key_compare;

		// Base typedef could be inherited.
		// value_compare
		// allocator_type
		// size_type
		// difference_type
		// pointer, const_pointer
		// reference, const_reference
		// iterator, const_iterator
		// reverse_iterator, const_reverse_iterator
		// value_type

		red_black_tree()
			: _Mybase(key_compare(), allocator_type())
		{	// construct empty set from defaults
		}

		explicit red_black_tree(const allocator_type& _Al)
			: _Mybase(key_compare(), _Al)
		{	// construct empty set from defaults, allocator
		}

		red_black_tree(const _Myt& _Right)

#if _HAS_CPP0X
			: _Mybase(_Right,
			_Right._Getal().select_on_container_copy_construction())

#else /* _HAS_CPP0X */
			: _Mybase(_Right, _Right._Getal())
#endif /* _HAS_CPP0X */

		{	// construct set by copying _Right
		}

		red_black_tree(const _Myt& _Right, const allocator_type& _Al)
			: _Mybase(_Right, _Al)
		{	// construct set by copying _Right, allocator
		}

		explicit red_black_tree(const key_compare& _Pred)
			: _Mybase(_Pred, allocator_type())
		{	// construct empty set from comparator
		}

		red_black_tree(const key_compare& _Pred, const allocator_type& _Al)
			: _Mybase(_Pred, _Al)
		{	// construct empty set from comparator and allocator
		}

		template<class _Iter>
		red_black_tree(_Iter _First, _Iter _Last)
			: _Mybase(key_compare(), allocator_type())
		{	// construct set from [_First, _Last)
			this->insert(_First, _Last);
		}

		template<class _Iter>
		red_black_tree(_Iter _First, _Iter _Last,
			const key_compare& _Pred)
			: _Mybase(_Pred, allocator_type())
		{	// construct set from [_First, _Last), comparator
			this->insert(_First, _Last);
		}

		template<class _Iter>
		red_black_tree(_Iter _First, _Iter _Last,
			const key_compare& _Pred, const allocator_type& _Al)
			: _Mybase(_Pred, _Al)
		{	// construct set from [_First, _Last), comparator, and allocator
			this->insert(_First, _Last);
		}

		_Myt& operator=(const _Myt& _Right)
		{	// assign by copying _Right
			_Mybase::operator=(_Right);
			return (*this);
		}

		red_black_tree(_Myt&& _Right)
			: _Mybase(std::move(_Right), _Right._Getal())
		{	// construct set by moving _Right
		}

		red_black_tree(_Myt&& _Right, const allocator_type& _Al)
			: _Mybase(std::move(_Right), _Al)
		{	// construct set by moving _Right
		}

		_Myt& operator=(_Myt&& _Right)
		{	// assign by moving _Right
			_Mybase::operator=(std::move(_Right));
			return (*this);
		}

		iterator insert(value_type&& _Val)
		{	// insert a key value
			return (_Mybase::insert(std::forward<value_type>(_Val)).first);
		}

		iterator insert(const_iterator _Where, value_type&& _Val)
		{	// insert a key value, with hint
			return (_Mybase::insert(_Where, std::forward<value_type>(_Val)));
		}

		// emplace

		void swap(_Myt& _Right)
		{	// exchange contents with non-movable _Right
			_Mybase::swap(_Right);
		}

		iterator insert(const value_type& _Val)
		{	// insert a key value
			return (_Mybase::insert(_Val).first);
		}

		iterator insert(const_iterator _Where, const value_type& _Val)
		{	// insert a key value, with hint
			return (_Mybase::insert(_Where, _Val));
		}

		template<class _Iter>
		void insert(_Iter _First, _Iter _Last)
		{	// insert [_First, _Last)
			_DEBUG_RANGE(_First, _Last);
			for (; _First != _Last; ++_First)
				this->insert(*_First);
		}

	};

	template<class _Kty,
	class _Pr,
	class _Alloc> inline
		void swap(red_black_tree<_Kty, _Pr, _Alloc>& _Left,
		red_black_tree<_Kty, _Pr, _Alloc>& _Right)
	{	// swap _Left and _Right red_black_trees
		_Left.swap(_Right);
	}

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "red_black_tree.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_red_black_tree