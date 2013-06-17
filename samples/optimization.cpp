//////////////////////////////////////////////////////////////////////////
//
// refer to chapter 5 of CSAPP, Computer Systems A Programmer's Perspective
//
// 1. two optimization blockers. (memory aliasing, side effect of function call)
// 2. 
//////////////////////////////////////////////////////////////////////////

#include <misc/misc.hpp>
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
		size_t L = iv.size();
		T acc=*dest;
		for (size_t i=0; i < L; i++) {
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
	// overload int, only +
	void combine4sse2(int*dest) {
		int*data = iv.data();
		int acci = *dest;
		int i=0;
		__m128i acc = _mm_setzero_si128();
		for (i=0; i < len-3; i+=4) {
			acc = _mm_add_epi32(acc, _mm_loadu_si128((__m128i*)(data+i)));
		}
		for (; i < len; i++) {
			acci = (acci + data[i]);
		}
		for (i=0; i < 4; i++) {
			acci = (acci + ((int*)&acc)[i]);
		}
		*dest=acci;
	}
	// overload float, only +
	void combine4sse2(float*dest) {
		float*data = iv.data();
		float acci = *dest;
		int i=0;
		__m128 acc = _mm_setzero_ps();
		for (i=0; i < len-3; i+=4) {
			acc = _mm_add_ps(acc, _mm_loadu_ps(data+i));
		}
		for (; i < len; i++) {
			acci = (acci + data[i]);
		}
		for (i=0; i < 4; i++) {
			acci = (acci + ((float*)&acc)[i]);
		}
		*dest=acci;
	}
	// only supported on Haswell
// 	void combine4avx2(int*dest) {
// 		int*data = iv.data();
// 		int acci = *dest;
// 		int i=0;
// 		__m256i acc = _mm256_setzero_si256();
// 		for (i=0; i < len-7; i+=8) {
// 			acc = _mm256_add_epi32(acc, _mm256_loadu_si256((__m256i*)(data+i)));
// 		}
// 		for (; i < len; i++) {
// 			acci = (acci + data[i]);
// 		}
// 		for (i=0; i < 8; i++) {
// 			acci = (acci + ((int*)&acc)[i]);
// 		}
// 		*dest=acci;
// 	}
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
	static const int len = 1024*1024*128;
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
	typedef int Ty;
	Opt<Ty> *opt1 = Opt<Ty>::getInstance();
	auto opt2 = Opt<Ty>::getInstance();
	Ty dest=1;
	opt1->combine1(&dest); // warm up
	opt1->combine2(&dest); // warm up
	std::cout<<std::fixed;
	dest=1;
	misc::timer t;
	opt1->combine1(&dest);
	std::cout<<"combine1:\t"<<std::hex<<dest<<" \t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine1a(&dest);
	std::cout<<"combine1a:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine2(&dest);
	std::cout<<"combine2:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine3(&dest);
	std::cout<<"combine3:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine4(&dest);
	std::cout<<"combine4:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine4a(&dest);
	std::cout<<"combine4a:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine4b(&dest);
	std::cout<<"combine4b:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine4sse2(&dest);
	std::cout<<"combine4sse2:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine5(&dest);
	std::cout<<"combine5:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine6(&dest);
	std::cout<<"combine6:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	t.start();
	opt1->combine7(&dest);
	std::cout<<"combine7:\t"<<dest<<"\t Time: "<<t.query()<<std::endl;

	return 0;
}