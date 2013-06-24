namespace misc{

#if(MISC_PLATFORM == MISC_PLATFORM_WINDOWS || defined(__CYGWIN__))
	MISC_FUNC_QUALIFIER timer::timer()
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&t2);
		QueryPerformanceCounter(&t1);
	}

	MISC_FUNC_QUALIFIER void timer::start()
	{
		QueryPerformanceCounter(&t1);
	}

	MISC_FUNC_QUALIFIER void timer::stop()
	{
		QueryPerformanceCounter(&t2);
	}

	MISC_FUNC_QUALIFIER double timer::elapsed()
	{
		return (t2.QuadPart - t1.QuadPart)*1000.0/frequency.QuadPart;
	}

	MISC_FUNC_QUALIFIER double timer::query()
	{
		QueryPerformanceCounter(&t2);
		return (t2.QuadPart - t1.QuadPart)*1000.0/frequency.QuadPart;
	}

	MISC_FUNC_QUALIFIER double timer::precision()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return 1.0/frequency.QuadPart;
	}
#else
	MISC_FUNC_QUALIFIER timer::timer()
	{
		clock_gettime(CLOCK_REALTIME, &t2);
		clock_gettime(CLOCK_REALTIME, &t1);
// 		gettimeofday(&t2, NULL);
// 		gettimeofday(&t1, NULL);
	}

	MISC_FUNC_QUALIFIER void timer::start()
	{
		clock_gettime(CLOCK_REALTIME, &t1);
//		gettimeofday(&t1, NULL);
	}

	MISC_FUNC_QUALIFIER void timer::stop()
	{
		clock_gettime(CLOCK_REALTIME, &t2);
//		gettimeofday(&t2, NULL);
	}

	MISC_FUNC_QUALIFIER double timer::elapsed()
	{
		return (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_nsec-t1.tv_nsec)/1e6;
//		return (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_usec-t1.tv_usec)/1000.0;
	}

	MISC_FUNC_QUALIFIER double timer::query()
	{
		clock_gettime(CLOCK_REALTIME, &t2);
		return (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_nsec-t1.tv_nsec)/1e6;
// 		gettimeofday(&t2, NULL);
// 		return (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_usec-t1.tv_usec)/1000.0;
	}

	MISC_FUNC_QUALIFIER double timer::precision()
	{
		timespec t1, t2;
		clock_gettime(CLOCK_REALTIME, &t1);
		clock_gettime(CLOCK_REALTIME, &t2);
		while (t2.tv_nsec==t1.tv_nsec)
			clock_gettime(CLOCK_REALTIME, &t2);
		return (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_nsec-t1.tv_nsec)/1e6;
// 		timeval t1, t2;
// 		gettimeofday(&t1, NULL);
// 		gettimeofday(&t2, NULL);
// 		while (t2.tv_usec==t1.tv_usec)
// 			gettimeofday(&t2, NULL);
// 		return (t2.tv_sec-t1.tv_sec)*1000.0+(t2.tv_usec-t1.tv_usec)/1000.0;
	}
#endif

} // namespace misc
