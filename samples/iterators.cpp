#include <misc/misc.hpp>

#include <iterator>
#include <vector>
#include <list>

class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
	int* p;
public:
	MyIterator(int* x) :p(x) {}
	MyIterator(const MyIterator& mit) : p(mit.p) {}
	MyIterator& operator++() {++p;return *this;}
	MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
	bool operator==(const MyIterator& rhs) {return p==rhs.p;}
	bool operator!=(const MyIterator& rhs) {return p!=rhs.p;}
	int& operator*() {return *p;}
};

template<class BDIter>
typename std::iterator_traits<BDIter>::value_type
	my_reverse(BDIter first, BDIter last)
{
	// typename std::iterator_traits<BDIter>::difference_type
	auto n = std::distance(first, last);
	--n;
	while(n > 0) {
		// typename std::iterator_traits<BDIter>::value_type
		auto tmp = *first;
		*first++ = *--last;
		*last = tmp;
		n -= 2;
	}
	return *first;
}

int main()
{
	int numbers[]={10,20,30,40,50};
	MyIterator from(numbers);
	MyIterator until(numbers+5);
	for (MyIterator it=from; it!=until; it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	// Fucking the Question 5 in http://blog.csdn.net/fengbingyang/article/details/8764931
	// refer to http://programmers.stackexchange.com/questions/153386/why-is-x-x-undefined
	int x=10;
	x = x++;
	from = from++;
	printf("int++: %d, iter++: %d\n",x,*from);

	std::vector<int> vc1(numbers, numbers+5);
	std::vector<int> vc2(vc1.begin(), vc1.end());

	std::vector<int> v(vc1);
	auto mid1 = my_reverse(v.begin(), v.end());
	for (int n : v)
		std::cout << n << ' ';
	std::cout << "Mid: " << mid1 <<'\n';

	std::list<int> l(numbers, numbers+5);
	auto mid2 = my_reverse(l.begin(), l.end());
	for (auto n : l)
		std::cout << n << ' ';
	std::cout << "Mid: " << mid2<< '\n';

	//    std::istreambuf_iterator<char> i1(std::cin), i2;
	//    my_reverse(i1, i2); // compilation error

	return 0;
}