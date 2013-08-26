#include <misc/misc.hpp>

#include "gtest/gtest.h"

TEST(balanced_tree_test, standard)
{
	const int N = 97;
	int a[N];
	int i=0;
	std::for_each(a, a+N, [&i](int &a){ a=i++; });
	srand( (unsigned int)time(NULL) );

	misc::AVL<int> bst;

	// test insert
	std::random_shuffle(a, a+N);
	std::for_each(a, a+N, [&bst](int &a){ bst.insert(a); });

	// test inorder
	std::vector<int> inorder;
	bst.inorder([&inorder](misc::AVL<int>::node_pointer x){
		inorder.push_back(x->key);
	});
	EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));

	// test minimum
	EXPECT_EQ(bst.getMin(), 0);
	// test maximum
	EXPECT_EQ(bst.getMax(), N-1);

	// test predecessor/successor
	EXPECT_EQ(bst.getPredecessor(N/2), N/2-1);
	EXPECT_EQ(bst.getSuccessor(N/2), N/2+1);

	// test AVL balanced
	bst.preorder([&bst](misc::AVL<int>::node_pointer x){
		EXPECT_TRUE( abs(bst.height(x->l) - bst.height(x->r)) <= 1);
	});

	// test delete(search)
	for (int i=0; i<N/2; i++) {
		EXPECT_TRUE(bst.del(i));
	}
	EXPECT_FALSE(bst.find(N/2-1));
	EXPECT_EQ(bst.getMin(), N/2);
}