#include <misc/misc.hpp>

#include "gtest/gtest.h"

// T : (BST, AVL, ...)
template <typename T>
class DynamicSetTest : public testing::Test {
protected:

	virtual void SetUp() {
		typename T::value_type i=0;
		std::for_each(a, a+N, [&i](typename T::value_type &a){ a=i++; });
		srand( (unsigned int)time(NULL) );

		// test insert
		std::random_shuffle(a, a+N);
		std::for_each(a, a+N, [this](typename T::value_type &a){ this->dyset.insert(a); });
	}

	misc::dynamic_set<T> dyset;

	static const int N = 97;
	typename T::value_type a[N];
};

#if GTEST_HAS_TYPED_TEST_P

using testing::Types;

TYPED_TEST_CASE_P(DynamicSetTest);

TYPED_TEST_P(DynamicSetTest, InorderWalking) {
	// test traversal
	std::vector<typename TypeParam::value_type> traversal;
	this->dyset.traversal([&traversal](typename TypeParam::node_pointer x){
		traversal.push_back(x->key);
	});
	EXPECT_TRUE(std::is_sorted(traversal.begin(), traversal.end()));
}

TYPED_TEST_P(DynamicSetTest, Queries) {
	// test minimum
	EXPECT_EQ(this->dyset.getMin(), 0);
	// test maximum
	EXPECT_EQ(this->dyset.getMax(), this->N-1);

	// test predecessor/successor
	EXPECT_EQ(this->dyset.getPredecessor(this->N/2), this->N/2-1);
	EXPECT_EQ(this->dyset.getSuccessor(this->N/2), this->N/2+1);
}

TYPED_TEST_P(DynamicSetTest, Search) {
	// test search(delete)
	for (int i=0; i<this->N/2; i++) {
		EXPECT_TRUE(this->dyset.del(typename TypeParam::value_type(i)));
	}
	EXPECT_FALSE(this->dyset.find(typename TypeParam::value_type(this->N/2-1)));
	EXPECT_EQ(this->dyset.getMin(), typename TypeParam::value_type(this->N/2));
}

REGISTER_TYPED_TEST_CASE_P(
	DynamicSetTest,
	InorderWalking, Queries, Search
	);

typedef Types<misc::BST<float>, misc::AVL<float>, misc::skip_lists<int>> Implementations;

INSTANTIATE_TYPED_TEST_CASE_P(BSTInstance,
							  DynamicSetTest,
							  Implementations);

#endif  // GTEST_HAS_TYPED_TEST_P

class AVLTest : public DynamicSetTest<misc::AVL<int>> {
protected:
	typedef misc::AVL<int> test_type;
	typedef test_type::node_pointer node_pointer;
};

TEST_F(AVLTest, Balanced) {
	auto avl = dyset.getObj();
	// test AVL balanced
	avl->preorder([avl](node_pointer x){
		EXPECT_TRUE( abs(avl->height(x->l) - avl->height(x->r)) <= 1);
	});
}