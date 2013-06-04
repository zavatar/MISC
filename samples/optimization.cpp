//////////////////////////////////////////////////////////////////////////
//
// refer to chapter 5 of CSAPP, Computer Systems A Programmer's Perspective
//
// 1. two optimization blockers. (memory aliasing, side effect of function call)
// 2. 
//////////////////////////////////////////////////////////////////////////

#include <misc/misc.hpp>
#include <chrono>
#include <functional>
#include <vector>
// memory aliasing
// side effect of function call

// Eliminating Loop Inefficiencies
template <typename T>
class Opt {
public:
	static Opt* getInstance() {
		static Opt inst;
		return &inst;
	}
#define op +
	void combine1(T*dest) {
		T* data = iv.data();
		for (int i=0; i < vec_length(); i++) {
			T val=0;
			get_vec_element(data, i, &val);
			*dest = (*dest op val);
		}
	}
	void combine1a(T*dest) {
		for (unsigned int i=0; i < iv.size(); i++) {
			*dest = (*dest op iv[i]);
		}
	}
	void combine2(T*dest) {
		T* data = iv.data();
		for (int i=0; i < len; i++) {
			T val=0;
			get_vec_element(data, i, &val);
			*dest = (*dest op val);
		}
	}
	void combine3(T*dest) {
		T*data = iv.data();
		for (int i=0; i < len; i++) {
			*dest = (*dest op data[i]);
		}
	}
	void combine4(T*dest) {
		T*data = iv.data();
		T acc=*dest;
		for (int i=0; i < len; i++) {
			acc = (acc op data[i]);
		}
		*dest=acc;
	}
	void combine4a(T*dest) {
		unsigned int L = iv.size();
		T acc=*dest;
		for (unsigned int i=0; i < L; i++) {
			acc = (acc op iv[i]);
		}
		*dest=acc;
	}
	void combine4b(T*dest) {
		T acc=*dest;
		for (T& i: iv) {
			acc = (acc op i);
		}
		*dest=acc;
	}
	void combine5(T*dest) {
		T*data = iv.data();
		T acc=*dest;
		int i=0;
		for (i=0; i < len-1; i+=2) {
			acc = (acc op data[i]) op data[i+1];
		}
		for (; i < len; i++) {
			acc = (acc op data[i]);
		}
		*dest=acc;
	}
	void combine6(T*dest) {
		T*data = iv.data();
		T acc0=*dest;
		T acc1=1; // T acc1=*dest;
		int i=0;
		for (i=0; i < len-1; i+=2) {
			acc0 = (acc0 op data[i]);
			acc1 = (acc1 op data[i+1]);
		}
		for (; i < len; i++) {
			acc0 = (acc0 op data[i]);
		}
		*dest=acc0 op acc1;
	}
	void combine7(T*dest) {
		T*data = iv.data();
		T acc=*dest;
		int i=0;
		for (i=0; i < len-1; i+=2) {
			acc = acc op (data[i] op data[i+1]);
		}
		for (; i < len; i++) {
			acc = (acc op data[i]);
		}
		*dest=acc;
	}
#undef op
	static const int len = 1000000;
private:
	std::vector<T> iv; // constructed in non-trivial default constructor list

	Opt():iv(len,1){printf("Singleton Opt constructed\n");}
	~Opt() {printf("Singleton Opt destructed\n");};

	int vec_length() {
		return len;
	}

	void get_vec_element(T*v, int i, T*val) {
		if (i<0 || i>=len)
			return;
		*val = v[i];
	}
};

int main()
{
	Opt<int> *opt1 = Opt<int>::getInstance();
	auto opt2 = Opt<int>::getInstance();
	int dest=1;
	opt1->combine1(&dest); // warm up
	opt1->combine2(&dest); // warm up
	dest=1;
	misc::timer t;
	opt1->combine1(&dest);
	printf("combine1: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine1a(&dest);
	printf("combine1a: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine2(&dest);
	printf("combine2: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine3(&dest);
	printf("combine3: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine4(&dest);
	printf("combine4: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine4a(&dest);
	printf("combine4a: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine4b(&dest);
	printf("combine4b: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine5(&dest);
	printf("combine5: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine6(&dest);
	printf("combine6: %d, Time: %.3f\n", dest, t.query());

	t.start();
	opt1->combine7(&dest);
	printf("combine7: %d, Time: %.3f\n", dest, t.query());

	return 0;
}