#ifndef misc_interval_tree
#define misc_interval_tree

namespace misc{

	template <typename T>
	class interval_tree
	{
	public:
		MISC_FUNC_DECL interval_tree();
	};

}//namespace misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "interval_tree.inl"
#endif//MISC_EXTERNAL_TEMPLATE

#endif//misc_interval_tree