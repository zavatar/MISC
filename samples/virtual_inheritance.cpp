//////////////////////////////////////////////////////////////////////////
//
// Refer to http://www.cppblog.com/chemz/archive/2007/06/12/26135.html
//
//////////////////////////////////////////////////////////////////////////
#include "misc/misc.hpp"
#include <ctime>

/*
 * 带有数据成员的基类
 */
struct Base1
{
    Base1( size_t i ) : m_val( i ) {}
    size_t m_val;
};
/*
 * 虚拟继承体系
 */
struct SubV1 : public virtual Base1
{
    SubV1( size_t i ) : Base1( i ) {}
};

struct SubV2 : public virtual Base1
{
    SubV2( size_t i ) : Base1( i ) {}
};

struct Diamond1 : public SubV1, public SubV2
{
    Diamond1( size_t i ) : Base1( i ), SubV1( i ), SubV2( i ) {}
};

struct DiamondSub1 : public Diamond1
{
    DiamondSub1( size_t i ) : Base1( i ), Diamond1( i ) {}
};
/*
 * 正常继承体系
 */
struct SubN1 : public Base1
{
    SubN1( size_t i ) : Base1( i ) {}
};
struct SubN2 : public Base1
{
    SubN2( size_t i ) : Base1( i ) {}
};
struct Multi1 : public SubN1, public SubN2
{
    Multi1( size_t i ) : SubN1( i ), SubN2( i ) {}
};
struct MultiSub1 : public Multi1
{
    MultiSub1( size_t i ) : Multi1( i ) {}
};
/*
 * 不带有数据成员的接口基类
 */
struct Base2
{
    virtual void func() {};
    virtual ~Base2() {}
};
/*
 * 虚拟继承体系
 */
// struct BaseX { BaseX() {i1 = i2 = 0xFFFFFFFF;} size_t i1, i2;};
struct SubV3 : public virtual Base2
{
};
struct SubV4 : public virtual Base2
{
};
struct Diamond2 : public SubV3, public SubV4
{
};
struct DiamondSub2 : public Diamond2
{
};

/*
 * 正常继承体系
 */
struct SubN3 : public Base2
{
};
struct SubN4 : public Base2
{
};
struct Multi2 : public SubN3, public SubN4
{
};
struct MultiSub2 : public Multi2
{
};

/*
 * 内存布局用类声明.
 */
struct LayoutBase1
{
    LayoutBase1() : m_val1( 0 ), m_val2( 1 ) {}

    size_t m_val1, m_val2;
};
struct LayoutBase2
{
    LayoutBase2() : m_val1( 3 ) {}

    size_t m_val1;
};
struct LayoutSub1 : public virtual Base1, public LayoutBase1, public LayoutBase2
{
    LayoutSub1() : Base1( 2 ) {}
};


#define MAX_TEST_COUNT 1000 * 1000 * 16
#define TIME_ELAPSE() ( std::clock() - start * 1.0 ) / CLOCKS_PER_SEC

int main( int argc, char *argv[] )
{
    /*
     * 类体系中的尺寸.
     */
    std::cout << "================================ sizeof ================================" << std::endl;
    std::cout << "    ----------------------------------------------------------------" << std::endl;
    std::cout << "sizeof( Base1 )       = " << sizeof( Base1 ) << std::endl; Base1 b1(1);
    std::cout << std::endl;
    std::cout << "sizeof( SubV1 )       = " << sizeof( SubV1 ) << std::endl; SubV1 sv1(1);
    std::cout << "sizeof( SubV2 )       = " << sizeof( SubV2 ) << std::endl; SubV2 sv2(1);
    std::cout << "sizeof( Diamond1 )    = " << sizeof( Diamond1 ) << std::endl; Diamond1 d1(1);
    std::cout << "sizeof( DiamondSub1 ) = " << sizeof( DiamondSub1 ) << std::endl; DiamondSub1 ds1(1);
    std::cout << std::endl;
	sv1.m_val = 2; sv2.m_val = 3; d1.m_val = 4;
	// sv1 = *(SubV1*)&b1; conversion from a virtual base class is implied
    std::cout << "sizeof( SubN1 )       = " << sizeof( SubN1 ) << std::endl; SubN1 sn1(1);
    std::cout << "sizeof( SubN2 )       = " << sizeof( SubN2 ) << std::endl; SubN2 sn2(1);
    std::cout << "sizeof( Multi1 )      = " << sizeof( Multi1 ) << std::endl; Multi1 m1(1);
    std::cout << "sizeof( MultiSub1 )   = " << sizeof( MultiSub1 ) << std::endl; MultiSub1 ms1(1);
	sn1.m_val = 2; sn2.m_val = 3; // m1.m_val = 4; ambiguous
    std::cout << "    ----------------------------------------------------------------" << std::endl;
    std::cout << "sizeof( Base2 )       = " << sizeof( Base2 ) << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof( SubV3 )       = " << sizeof( SubV3 ) << std::endl;
    std::cout << "sizeof( SubV4 )       = " << sizeof( SubV4 ) << std::endl;
    std::cout << "sizeof( Diamond2 )    = " << sizeof( Diamond2 ) << std::endl;
    std::cout << "sizeof( DiamondSub2 ) = " << sizeof( DiamondSub2 ) << std::endl;
    std::cout << std::endl;
    std::cout << "sizeof( SubN3 )       = " << sizeof( SubN3 ) << std::endl;
    std::cout << "sizeof( SubN4 )       = " << sizeof( SubN4 ) << std::endl;
    std::cout << "sizeof( Multi2 )      = " << sizeof( Multi2 ) << std::endl;
    std::cout << "sizeof( MultiSub2 )   = " << sizeof( MultiSub2 ) << std::endl;
    /*
     * 对象内存布局
     */
    std::cout << "================================ layout ================================" << std::endl;
    std::cout << "    --------------------------------MI------------------------------" << std::endl;
    LayoutSub1 *lsc = new LayoutSub1;
    std::cout << "sizeof( LayoutSub1 )   = " << sizeof( LayoutSub1 ) << std::endl;
    std::cout << "CLayoutBase1 offset of LayoutSub1 is " << (char*)( LayoutBase1 *)lsc - (char*)lsc << std::endl;
    std::cout << "CBase1  offset of LayoutSub1 is " << (char*)( Base1  *)lsc - (char*)lsc << std::endl;
    std::cout << "CLayoutBase2 offset of LayoutSub1 is " << (char*)( LayoutBase2 *)lsc - (char*)lsc << std::endl;

    int *ptr = (int*)lsc;
#	if(MISC_ISGCC)
	std::cout << "vbc in LayoutSub1 is " << *(int*)ptr[0] << std::endl;
#	elif(MISC_ISVC)
    std::cout << "vbc in LayoutSub1 is " << *(int*)ptr[3] << std::endl;
#	endif

    delete lsc;

    std::cout << "    --------------------------------SI------------------------------" << std::endl;
    SubV1 *scv1 = new SubV1( 1 );
    std::cout << "sizeof( SubV1 )   = " << sizeof( SubV1 ) << std::endl;
    std::cout << "CBase1 offset of SubV1 is " << (char*)( Base1 *)scv1 - (char*)scv1 << std::endl;

    ptr = (int*)scv1;
    std::cout << "vbc in SubV1 is " << *(int*)ptr[0] << std::endl;

    delete scv1;

    /*
     * 性能测试
     */
    std::cout << "================================ Performance ================================" << std::endl;
    double times[4];
    size_t idx = 0;

    SubV1 *ptr1 = new Diamond1( 1 );
    std::clock_t start = std::clock();
    {
        for ( size_t i = 0; i < MAX_TEST_COUNT; ++i )
            ptr1->m_val = i;
    }
    times[idx++] = TIME_ELAPSE();
    delete static_cast< Diamond1*>( ptr1 );

    SubN1 *ptr2 = new Multi1( 0 );
    start = std::clock();
    {
        for ( size_t i = 0; i < MAX_TEST_COUNT; ++i )
            ptr2->m_val = i;
    }
    times[idx++] = TIME_ELAPSE();
    delete static_cast< Multi1*>( ptr2 );

    std::cout << "CSubV1::ptr1->m_val " << times[0] << " s" << std::endl;
    std::cout << "CSubN1::ptr2->m_val " << times[1] << " s" << std::endl;

    return 0; 
}