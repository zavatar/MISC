#include <misc/misc.hpp>

#include "gtest/gtest.h"

// T : (BST, AVL, ...)
template <typename T>
class BinarySearchTreeTest : public testing::Test {
protected:
	typedef T test_type;

	BinarySearchTreeTest() { bst = new T; }

	virtual ~BinarySearchTreeTest() { delete bst; }

	virtual void SetUp() {
		int i=0;
		std::for_each(a, a+N, [&i](int &a){ a=i++; });
		srand( (unsigned int)time(NULL) );

		// test insert
		std::random_shuffle(a, a+N);
		std::for_each(a, a+N, [this](int &a){ this->bst->insert(a); });
	}

	typename T::base_type *bst;

	static const int N = 97;
	int a[N];
};

#if GTEST_HAS_TYPED_TEST

using testing::Types;

typedef Types<misc::BST<int>, misc::AVL<int>> Implementations;

TYPED_TEST_CASE(BinarySearchTreeTest, Implementations);

TYPED_TEST(BinarySearchTreeTest, InorderWalking) {
	// test inorder
	std::vector<int> inorder;
	bst->inorder([&inorder](test_type::node_pointer x){
		inorder.push_back(x->key);
	});
	EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));
}

TYPED_TEST(BinarySearchTreeTest, Queries) {
	// test minimum
	EXPECT_EQ(bst->getMin(), 0);
	// test maximum
	EXPECT_EQ(bst->getMax(), N-1);

	// test predecessor/successor
	EXPECT_EQ(bst->getPredecessor(N/2), N/2-1);
	EXPECT_EQ(bst->getSuccessor(N/2), N/2+1);
}

TYPED_TEST(BinarySearchTreeTest, Search) {
	// test search(delete)
	for (int i=0; i<N/2; i++) {
		EXPECT_TRUE(bst->del(i));
	}
	EXPECT_FALSE(bst->find(N/2-1));
	EXPECT_EQ(bst->getMin(), N/2);
}

#endif  // GTEST_HAS_TYPED_TEST

class AVLTest : public BinarySearchTreeTest<misc::AVL<int>> {};

TEST_F(AVLTest, Balanced) {
	auto avl = static_cast<AVLTest::test_type*>(bst);
	// test AVL balanced
	avl->preorder([avl](test_type::node_pointer x){
		EXPECT_TRUE( abs(avl->height(x->l) - avl->height(x->r)) <= 1);
	});
}