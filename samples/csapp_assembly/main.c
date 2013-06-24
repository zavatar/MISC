#include "head.h"
#include <stdio.h>
#include <malloc.h>
//#include <sys/time.h>
#include <windows.h>

int main()
{
	//struct timespec t1, t2;
	LARGE_INTEGER frequency, t1, t2;
	T acc=0;
	T*data=(T*)malloc(__SIZE_*sizeof(T));
	int i=0;
	for (; i < __SIZE_; i++)
		data[i] = .5f;
	
	//clock_gettime(CLOCK_REALTIME, &t1);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	
	acc = combine4(data);
	
	//clock_gettime(CLOCK_REALTIME, &t2);
	QueryPerformanceCounter(&t2);
	printf("%f\t",acc);
	//printf("Time: %.3f ms.\n", (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_nsec-t1.tv_nsec)/1e6);
	printf("Time: %.3f ms.\n", (double)(t2.QuadPart - t1.QuadPart)*1000.0/frequency.QuadPart);
	return 0;
}