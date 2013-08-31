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
	try {
		this->dyset.getPredecessor(-1);
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	try {
		this->dyset.getPredecessor(0);
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	try {
		this->dyset.getSuccessor(typename TypeParam::value_type(this->N));
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	try {
		this->dyset.getSuccessor(typename TypeParam::value_type(this->N-1));
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
}

TYPED_TEST_P(DynamicSetTest, Search) {
	// test search(delete)
	for (int i=0; i<this->N/4; i++) {
		EXPECT_TRUE(this->dyset.del(typename TypeParam::value_type(i)));
		EXPECT_FALSE(this->dyset.del(typename TypeParam::value_type(i)));
	}
	EXPECT_TRUE(this->dyset.find(typename TypeParam::value_type(this->N/2-1)));
	EXPECT_FALSE(this->dyset.find(typename TypeParam::value_type(this->N/4-1)));
	EXPECT_FALSE(this->dyset.find(typename TypeParam::value_type(this->N)));

	int i = this->N/4;
	this->dyset.traversal([&i](typename TypeParam::node_pointer x){
		EXPECT_EQ(x->key, i++);
	});
}

REGISTER_TYPED_TEST_CASE_P(
	DynamicSetTest,
	InorderWalking, Queries, Search
	);

typedef testing::Types<
	misc::BST<float>,
	misc::AVL<float>,
	misc::skip_lists<int>,
	misc::SBT<int>,
	misc::red_black_tree<int>,
	misc::order_statistic_tree<int>,
	misc::itv_tree<float>
> Implementations;

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
		EXPECT_TRUE(avl->isbalanced(x));
	});
	int gaps = this->N/5;
	for (int i=0; i<gaps; i++) {
		EXPECT_TRUE(avl->del(i));
	}
	for (int i=0; i<gaps; i++) {
		EXPECT_TRUE(avl->del(2*gaps+i));
	}
	for (int i=0; i<gaps; i++) {
		EXPECT_TRUE(avl->del(4*gaps+i));
	}
	avl->preorder([avl](node_pointer x){
		EXPECT_TRUE(avl->isbalanced(x));
	});

	// special case: delete 5 -> delete 6'
	//          ____5____
	//        _3_     ___8___
	//      _2   4   6'_     _10_
	//     1            7   9    11_
	//                             12
	avl->clear();
	int arr[12] = {5,3,8,2,4,6,10,1,7,9,11,12};
	for (int i=0; i<12; i++)
		avl->insert(arr[i]);
	EXPECT_TRUE(avl->del(5));
	avl->preorder([avl](node_pointer x){
		EXPECT_TRUE(avl->isbalanced(x));
	});
}

class SBTTest : public DynamicSetTest<misc::SBT<int>> {
protected:
	typedef misc::SBT<int> test_type;
	typedef test_type::node_pointer node_pointer;
};

TEST_F(SBTTest, Balanced) {
	// N=10250 will fail AND del may break the balance!!!
// 	auto sbt = dyset.getObj();
// 	// test SBT balanced
// 	sbt->preorder([sbt](node_pointer x){
// 		EXPECT_TRUE(sbt->isbalanced(x));
// 	});
// 	int gaps = this->N/5;
// 	for (int i=0; i<gaps; i++) {
// 		EXPECT_TRUE(sbt->del(i));
// 	}
// 	for (int i=0; i<gaps; i++) {
// 		EXPECT_TRUE(sbt->del(2*gaps+i));
// 	}
// 	for (int i=0; i<gaps; i++) {
// 		EXPECT_TRUE(sbt->del(4*gaps+i));
// 	}
// 	sbt->preorder([sbt](node_pointer x){
// 		EXPECT_TRUE(sbt->isbalanced(x));
// 	});
}

TEST_F(SBTTest, Rank) {
	auto sbt = dyset.getObj();
	// test SBT Rank
	try {
		sbt->getNth(0);
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	EXPECT_EQ(sbt->getNth(1), 0);
	try {
		sbt->getNth(this->N+1);
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	EXPECT_EQ(sbt->getNth(this->N), this->N-1);
}

//////////////////////////////////////////////////////////////////////////

class order_statistic_treeTest
	: public DynamicSetTest<misc::order_statistic_tree<int>> {
protected:
	typedef misc::order_statistic_tree<int> test_type;
	typedef test_type::node_pointer node_pointer;
};

TEST_F(order_statistic_treeTest, Rank) {
	auto ost = dyset.getObj();
	// test order_statistic_tree Rank
	try {
		ost->getNth(0);
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	EXPECT_EQ(ost->getNth(1), 0);
	try {
		ost->getNth(this->N+1);
		EXPECT_TRUE(false);
	} catch (...) { EXPECT_TRUE(true); }
	EXPECT_EQ(ost->getNth(this->N), this->N-1);
}

template <typename T>
class itv_treeTest : public testing::Test  {
protected:

	virtual void SetUp() {
		// case from Introduction to Algorithms
		T low[10] = {16,8,25,5,15,17,26,0,6,19};
		T high[10]= {21,9,30,8,23,19,26,3,10,20};

		// test insert
		for (int i=0; i<10; i++)
			itv.insert(low[i], high[i]);
	}

	misc::itv_tree<T> itv;
};

#if GTEST_HAS_TYPED_TEST_P

TYPED_TEST_CASE_P(itv_treeTest);

TYPED_TEST_P(itv_treeTest, Search) {
	// test search
	EXPECT_TRUE(this->itv.find(22, 25));
	EXPECT_FALSE(this->itv.find(11, 14));
}

REGISTER_TYPED_TEST_CASE_P(
	itv_treeTest,
	Search
	);

typedef testing::Types<int, float> itv_treeTypes;

INSTANTIATE_TYPED_TEST_CASE_P(itv_treeInstance,
							  itv_treeTest,
							  itv_treeTypes);

#endif  // GTEST_HAS_TYPED_TEST_P