#include <misc/misc.hpp>

#include <iterator>
#include <vector>
#include <list>

template<class BDIter>
void my_reverse(BDIter first, BDIter last)
{
	typename std::iterator_traits<BDIter>::difference_type n = std::distance(first, last);
	--n;
	while(n > 0) {
		typename std::iterator_traits<BDIter>::value_type tmp = *first;
		*first++ = *--last;
		*last = tmp;
		n -= 2;
	}
}

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	std::vector<int> v(a, a+5);
	my_reverse(v.begin(), v.end());
	for (int n : v)
		std::cout << n << ' ';
	std::cout << '\n';

	std::list<int> l(a, a+5);
	my_reverse(l.begin(), l.end());
	for (auto n : l)
		std::cout << n << ' ';
	std::cout << '\n';

	//    std::istreambuf_iterator<char> i1(std::cin), i2;
	//    my_reverse(i1, i2); // compilation error

	return 0;
}