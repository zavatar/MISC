//////////////////////////////////////////////////////////////////////////
//
// refer to https://code.google.com/p/googletest/
// http://www.cnblogs.com/coderzh/archive/2009/03/31/1426758.html
// gtest samples 1~10
//
//////////////////////////////////////////////////////////////////////////

#include <misc/misc.hpp>
#include "gtest/gtest.h"

// sample 1: unit test function
TEST(TestCaseName, TestName)
{
	EXPECT_PRED2([](int,int){return false;}, 1, 2) << "print when error";
	// ASSERT_*, EXPECT_*
	// * == TRUE, FALSE, EQ, NE, LT, LE, GT, GE, STREQ, STRNE,
	// STRCASEEQ, STRCASENE, THROW, ANY_THROW, NO_THROW, PREDn(1~5)
	// PRED_FORMATn(1~5), FLOAT_EQ, DOUBLE_EQ
}

// sample 2: fixture
class fixture : public testing::Test {
protected:
	// called before each Test Case
	static void SetUpTestCase() {printf("Test Case Begin...\n");}

	// called after each Test Case
	static void TearDownTestCase() {printf("Test Case End...\n");}

	// called before each Test
	virtual void SetUp() {printf("\tTest Begin...\n");}

	// called after each Test
	virtual void TearDown() {printf("\tTest End...\n");}
};
TEST_F(fixture, Test1){}
TEST_F(fixture, Test2){}

// sample 3: parameter list
#if GTEST_HAS_PARAM_TEST
class ParamTest : public testing::TestWithParam<std::tuple<int,int,int(*)(int,int)> > {
protected:
	virtual void SetUp() {
		pf = std::get<2>(GetParam());
	}
	virtual void TearDown() {
		pf = NULL;
	}
	bool run() {
		auto tup = GetParam();
		int a=std::get<0>(tup);
		int b=std::get<1>(tup);
		return (a+b) == pf(a,b);
	}
private:
	int(*pf)(int,int);
};
TEST_P(ParamTest, Test1){
	EXPECT_TRUE(run());
}
INSTANTIATE_TEST_CASE_P(
	In,
	ParamTest,
	testing::Combine( // generator could be Range, Values, ValuesIn, Bool, Combine
		testing::Values(1),
		testing::Range(0x10,0x21,0x10),
		testing::Values([](int a,int b){return a+b;},[](int a,int b){return b-a;})
	)
);
#endif

// sample 4: type list
template <typename T>
class TypeTest : public testing::Test {};
#if GTEST_HAS_TYPED_TEST

#endif
#if GTEST_HAS_TYPED_TEST_P
TYPED_TEST_CASE_P(TypeTest);
TYPED_TEST_P(TypeTest, Test1) {
	printf("\t%s\n", typeid(TypeParam).name());
}
REGISTER_TYPED_TEST_CASE_P(TypeTest, Test1);
typedef testing::Types<char, int> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(In, TypeTest, MyTypes);
#endif

// sample 5: listener API
class listener : public testing::EmptyTestEventListener {};
TEST(listener, Test1) {}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	// append listener
	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
	//delete listeners.Release(listeners.default_result_printer());
	listeners.Append(new listener);

	return RUN_ALL_TESTS();
}