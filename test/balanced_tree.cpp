#include <misc/misc.hpp>

#include "gtest/gtest.h"

// T : (BST, AVL, ...)
template <typename T>
class BinarySearchTreeTest : public testing::Test {
protected:

	BinarySearchTreeTest() { bst = new T; }

	virtual ~BinarySearchTreeTest() { delete bst; }

	virtual void SetUp() {
		typename T::value_type i=0;
		std::for_each(a, a+N, [&i](typename T::value_type &a){ a=i++; });
		srand( (unsigned int)time(NULL) );

		// test insert
		std::random_shuffle(a, a+N);
		std::for_each(a, a+N, [this](typename T::value_type &a){ this->bst->insert(a); });
	}

	typename T::base_type *bst;

	static const int N = 8;
	typename T::value_type a[N];
};

#if GTEST_HAS_TYPED_TEST_P

using testing::Types;

TYPED_TEST_CASE_P(BinarySearchTreeTest);

TYPED_TEST_P(BinarySearchTreeTest, InorderWalking) {
	// test inorder
	std::vector<typename TypeParam::value_type> inorder;
	this->bst->inorder([&inorder](typename TypeParam::node_pointer x){
		inorder.push_back(x->key);
	});
	EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));
}

TYPED_TEST_P(BinarySearchTreeTest, Queries) {
	// test minimum
	EXPECT_EQ(this->bst->getMin(), 0);
	// test maximum
	EXPECT_EQ(this->bst->getMax(), this->N-1);

	// test predecessor/successor
	EXPECT_EQ(this->bst->getPredecessor(this->N/2), this->N/2-1);
	EXPECT_EQ(this->bst->getSuccessor(this->N/2), this->N/2+1);
}

TYPED_TEST_P(BinarySearchTreeTest, Search) {
	// test search(delete)
	for (int i=0; i<this->N/2; i++) {
		EXPECT_TRUE(this->bst->del(typename TypeParam::value_type(i)));
	}
	EXPECT_FALSE(this->bst->find(typename TypeParam::value_type(this->N/2-1)));
	EXPECT_EQ(this->bst->getMin(), typename TypeParam::value_type(this->N/2));
}

REGISTER_TYPED_TEST_CASE_P(
	BinarySearchTreeTest,
	InorderWalking, Queries, Search
	);

typedef Types<misc::BST<float>, misc::AVL<float>> Implementations;

INSTANTIATE_TYPED_TEST_CASE_P(BSTInstance,
							  BinarySearchTreeTest,
							  Implementations);

#endif  // GTEST_HAS_TYPED_TEST_P

class AVLTest : public BinarySearchTreeTest<misc::AVL<int>> {
protected:
	typedef misc::AVL<int> test_type;
	typedef test_type::node_pointer node_pointer;
};

TEST_F(AVLTest, Balanced) {
	auto avl = static_cast<test_type*>(bst);
	// test AVL balanced
	avl->preorder([avl](node_pointer x){
		EXPECT_TRUE( abs(avl->height(x->l) - avl->height(x->r)) <= 1);
	});
}