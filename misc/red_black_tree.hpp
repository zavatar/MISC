#ifndef misc_red_black_tree
#define misc_red_black_tree

#include <set>

namespace misc {

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
} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "red_black_tree.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_red_black_tree