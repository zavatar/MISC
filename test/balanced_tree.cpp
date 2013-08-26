#include <misc/misc.hpp>

#include "gtest/gtest.h"

// T : (BST, AVL, ...)
template <typename T>
class BinarySearchTreeTest : public testing::Test {
protected:
	typedef T test_type;
	typedef typename test_type::value_type value_type;
	typedef typename test_type::node_pointer node_pointer;

	BinarySearchTreeTest() { bst = new test_type; }

	virtual ~BinarySearchTreeTest() { delete bst; }

	virtual void SetUp() {
		value_type i=0;
		std::for_each(a, a+N, [&i](value_type &a){ a=i++; });
		srand( (unsigned int)time(NULL) );

		// test insert
		std::random_shuffle(a, a+N);
		std::for_each(a, a+N, [this](value_type &a){ this->bst->insert(a); });
	}

	typename test_type::base_type *bst;

	static const int N = 8;
	value_type a[N];
};

#if GTEST_HAS_TYPED_TEST_P

using testing::Types;

TYPED_TEST_CASE_P(BinarySearchTreeTest);

TYPED_TEST_P(BinarySearchTreeTest, InorderWalking) {
	// test inorder
	std::vector<value_type> inorder;
	bst->inorder([&inorder](node_pointer x){
		inorder.push_back(x->key);
	});
	EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));
}

TYPED_TEST_P(BinarySearchTreeTest, Queries) {
	// test minimum
	EXPECT_EQ(bst->getMin(), 0);
	// test maximum
	EXPECT_EQ(bst->getMax(), N-1);

	// test predecessor/successor
	EXPECT_EQ(bst->getPredecessor(N/2), N/2-1);
	EXPECT_EQ(bst->getSuccessor(N/2), N/2+1);
}

TYPED_TEST_P(BinarySearchTreeTest, Search) {
	// test search(delete)
	for (int i=0; i<N/2; i++) {
		EXPECT_TRUE(bst->del(value_type(i)));
	}
	EXPECT_FALSE(bst->find(value_type(N/2-1)));
	EXPECT_EQ(bst->getMin(), value_type(N/2));
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