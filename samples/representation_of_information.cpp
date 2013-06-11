//////////////////////////////////////////////////////////////////////////
//
// refer to chapter 2 of CSAPP, Computer Systems A Programmer's Perspective
// 
// about "magic number" conversion: (insignificant on Modern Compiler)
// http://stereopsis.com/sree/fpu2006.html
// and Qiming's implementation: (Appendix code, but helpful to understand Float format)
// http://www.kunzhou.net/2010/SPAP-TR.pdf
// 
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"
#include <climits>
#include <cmath>

bool isBigEndian()
{
	union {
		char _b1;
		int _b4;
	} num;
	num._b4 = 0x1234;
	if (num._b1 == 0x12)
		return true;
	else
		return false;
}

union ieee754 {
	struct {unsigned int mantissa:23, exp:8, sign:1;};
	float f;
	int i;
	ieee754() : f(0.0){}
	ieee754(float a) : f(a){}
	ieee754(int a) : i(a) {}
};

inline float __int_as_float(int a) {
	union {
		int i;
		float f;
	} _t;
	_t.i = a;
	return _t.f;
}
inline int __float_as_int(float a) {
	union {
		int i;
		float f;
	} _t;
	_t.f = a;
	return _t.i;
}

// only correct for int 0x00800000~0x0 (2^23)
// the interval of neighbor of floats between 8388608.f(0x4b000000)~
// 16777216.f(0x4b800000) is exactly 1.
float fast_i2f_u23(int c) { // fast convert int to float
	return __int_as_float(c^0x4b000000)-8388608.f;
}
// only correct for float 8388608.f~0.f (1.f*2^23)
int fast_f2i_u23(float f) {
	return __float_as_int(f+8388608.f)^0x4b000000;
}
// only correct for int -128~127 (2^8)
// -128~127 to -128.f~127.f
// z^0x4b000080 will mask highest bit of z(8)
float fast_c2f_s8(char c) { // fast convert signed char to signed float
	unsigned int z=(unsigned int)(unsigned char)c;
	return __int_as_float(z^0x4b000080)-8388736.f;
}
// -128.f~127.f to -128~127 (-1.f*2^8)
char fast_f2c_s8(float f) {
	return (char)__float_as_int(f+8388736.f)^0x4b000080;
}

int main()
{
	printf("isBigEndian: %d\n", isBigEndian());

	printf("%d\n", (0x007fffff));
	printf("%f\n", fast_i2f_u23(0x007fffff));
	printf("%d\n", fast_f2i_u23(8388607.f));

	printf("%d\n", (0x00800000));
	printf("%f\n", fast_i2f_u23(0x00800000));
	printf("%d\n", fast_f2i_u23(8388608.f));
	
	printf("%d\n", (0x00800001));
	printf("%f\n", fast_i2f_u23(0x00800001));
	printf("%d\n", fast_f2i_u23(8388609.f));

	printf("%f\n", fast_c2f_s8(-128));
	printf("%f\n", fast_c2f_s8(-1));
	printf("%f\n", fast_c2f_s8(127));

	printf("%d\n", fast_f2c_s8(-128.f));
	printf("%d\n", fast_f2c_s8(-1.f));
	printf("%d\n", fast_f2c_s8(127.f));

	printf("sizeof(ieee754):%d\n", sizeof(ieee754));
	const ieee754 fe23(8388608.f);
	const ieee754 fi23(0x4b000000);
	const ieee754 quietNaN(std::numeric_limits<float>::quiet_NaN());
	const ieee754 signalingNaN(std::numeric_limits<float>::signaling_NaN());

	return 0;
}