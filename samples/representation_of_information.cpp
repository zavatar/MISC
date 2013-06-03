//////////////////////////////////////////////////////////////////////////
//
// refer to chapter 2 of CSAPP, Computer Systems A Programmer's Perspective
// 
//
//////////////////////////////////////////////////////////////////////////

#include "misc/misc.hpp"

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

int main()
{
	printf("isBigEndian: %d\n", isBigEndian());
	return 0;
}