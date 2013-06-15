# refer to CSAPP, Computer Systems A Programmer's Perspective
# and http://software.intel.com/en-us/blogs/2012/09/26/gcc-x86-performance-hints

# using x86_64-pc-cygwin-gcc-4.8.1.exe compiler.

#define T float
#define _SIZE (1024*1024*128)
#define _OP +

1. _-m32_-O1.s :
x86_64-pc-cygwin-gcc -O1 -S -m32 combine.c

2. _-march=native_-mfpmath=sse.s :
x86_64-pc-cygwin-gcc -O1 -S -m32 -march=native -mfpmath=sse combine.c
x86_64-pc-cygwin-gcc -O1 -S -m32 -march=native -mfpmath=sse -ffast-math combine.c

3. _-funroll-loops.s :
x86_64-pc-cygwin-gcc -O1 -S -m32 -march=native -mfpmath=sse -funroll-loops combine.c

4. _-O3.s :
x86_64-pc-cygwin-gcc -O3 -S -m32 -march=native -mfpmath=sse -funroll-loops combine.c

5. _final_mul.s, _final_add.s:
x86_64-pc-cygwin-gcc -Ofast -S -m32 -march=native -mfpmath=sse -funroll-loops combine.c

benchmark:
gcc -O3 -o p main.c _XXX.s

   Time     Result (67108864)
1. 144 ms, 67108864.000000
2. 144 ms,  8388608.000000 // Why? 8388608.000000 + .5f == 8388608.000000
3. 144 ms,  8388608.000000
4. 141 ms,  8388608.000000
5.  38 ms, 67108864.000000

gcc -Ofast -march=native -o p main.c combine.c
6.  38 ms, 67108864.000000

///////////////////////////////////////////////////////////////////////////
For VS 2012
-Ox					==		/Od /O1 /O2 /Ox (C/C++ -> General)
-S					==		/FA (C/C++ -> Output Files)
-m32				==		CMake GUI ...
-mfpmath=sse		==		/arch:SSE /arch:SSE2 /arch:AVX
-ffast-math			==		/fp:fast
add main.c and combine.c or vs2012.asm. (enable masam Build Customization of Project then add .asm)
-> build -> run:
	38 ms, 67108864.000000