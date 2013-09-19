#ifndef misc_timer
#define misc_timer

#if(MISC_PLATFORM == MISC_PLATFORM_WINDOWS || defined(__CYGWIN__))
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace misc {

	class timer
	{
		friend struct Loki::CreateUsingNew<timer>;
	public:
		MISC_FUNC_DECL void start();
		MISC_FUNC_DECL void stop();
		MISC_FUNC_DECL double elapsed(); // in millisecond
		MISC_FUNC_DECL double query(); // in millisecond
		static double precision();
	private:
#	if(MISC_PLATFORM == MISC_PLATFORM_WINDOWS || defined(__CYGWIN__))
		LARGE_INTEGER frequency, t1, t2;
#	else
		timespec t1, t2;
		//timeval t1, t2;
#	endif

		MISC_FUNC_DECL timer();
		MISC_FUNC_DECL timer(const timer&);
		MISC_FUNC_DECL timer& operator=(const timer&);
	};

	typedef Loki::SingletonHolder<timer> singleton_timer;

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "timer.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_timer
