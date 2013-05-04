#ifndef misc_setup
#define misc_setup

//////////////////////////////////////////////////////////////////////////
// Version
#define MISC_VERSION			13
#define MISC_VERSION_MAJOR		0
#define MISC_VERSION_MINOR		1

//////////////////////////////////////////////////////////////////////////
// Platform
#define MISC_PLATFORM_UNKNOWN		0x00000000
#define MISC_PLATFORM_WINDOWS		0x00010000
#define MISC_PLATFORM_LINUX			0x00020000
#define MISC_PLATFORM_UNIX			0x00400000

#ifdef MISC_FORCE_PLATFORM_UNKNOWN
#	define MISC_PLATFORM MISC_PLATFORM_UNKNOWN
#elif defined(_WIN32)
#	define MISC_PLATFORM MISC_PLATFORM_WINDOWS
#elif defined(__linux)
#   define MISC_PLATFORM MISC_PLATFORM_LINUX
#elif defined(__unix)
#   define MISC_PLATFORM MISC_PLATFORM_UNIX
#else
#	define MISC_PLATFORM MISC_PLATFORM_UNKNOWN
#endif

// Report platform detection
#if(defined(MISC_MESSAGES) && !defined(MISC_MESSAGE_PLATFORM_DISPLAYED))
#	define MISC_MESSAGE_PLATFORM_DISPLAYED
#	if(MISC_PLATFORM & MISC_PLATFORM_WINDOWS)
#		pragma message("MISC: Windows platform detected")
#	elif(MISC_PLATFORM & MISC_PLATFORM_LINUX)
#		pragma message("MISC: Linux platform detected")
#	elif(MISC_PLATFORM & MISC_PLATFORM_UNIX)
#		pragma message("MISC: UNIX platform detected")
#	elif(MISC_PLATFORM & MISC_PLATFORM_UNKNOWN)
#		pragma message("MISC: platform unknown")
#	else
#		pragma message("MISC: platform not detected")
#	endif
#endif

//////////////////////////////////////////////////////////////////////////
// Compiler
#define MISC_COMPILER_UNKNOWN		0x00000000

// Visual C++ defines
#define MISC_COMPILER_VC				0x01000000
#define MISC_COMPILER_VC2005			0x01000070
#define MISC_COMPILER_VC2008			0x01000080
#define MISC_COMPILER_VC2010			0x01000090
#define MISC_COMPILER_VC2012			0x010000A0

// GCC defines
#define MISC_COMPILER_GCC           0x02000000
#define MISC_COMPILER_GCC45			0x020000C0
#define MISC_COMPILER_GCC46			0x020000D0
#define MISC_COMPILER_GCC47			0x020000E0
#define MISC_COMPILER_GCC48			0x020000F0
#define MISC_COMPILER_GCC49			0x02000100

// Force generic C++ compiler
#ifdef MISC_FORCE_COMPILER_UNKNOWN
#	define MISC_COMPILER MISC_COMPILER_UNKNOWN

// Visual C++
#elif defined(_MSC_VER)
#	if _MSC_VER == 1400
#		define MISC_COMPILER MISC_COMPILER_VC2005
#	elif _MSC_VER == 1500
#		define MISC_COMPILER MISC_COMPILER_VC2008
#	elif _MSC_VER == 1600
#		define MISC_COMPILER MISC_COMPILER_VC2010
#	elif _MSC_VER == 1700
#		define MISC_COMPILER MISC_COMPILER_VC2012
#	else//_MSC_VER
#		define MISC_COMPILER MISC_COMPILER_VC
#	endif//_MSC_VER

// G++ 
#elif(defined(__GNUC__) || defined(__MINGW32__))
#	if   (__GNUC__ == 4) && (__GNUC_MINOR__ == 5)
#		define MISC_COMPILER MISC_COMPILER_GCC45
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 6)
#		define MISC_COMPILER MISC_COMPILER_GCC46
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 7)
#		define MISC_COMPILER MISC_COMPILER_GCC47
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)
#		define MISC_COMPILER MISC_COMPILER_GCC48
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 9)
#		define MISC_COMPILER MISC_COMPILER_GCC49
#	else
#		define MISC_COMPILER MISC_COMPILER_GCC
#	endif

#else
#	define MISC_COMPILER MISC_COMPILER_UNKNOWN
#endif

#ifndef MISC_COMPILER
#error "MISC_COMPILER undefined, your compiler may not be supported by MISC. Add #define MISC_COMPILER 0 to ignore this message."
#endif//MISC_COMPILER

//////////////////////////////////////////////////////////////////////////
// C++ Version
#define MISC_LANG_CXX			(0 << 0)
#define MISC_LANG_CXX98			((1 << 1) | MISC_LANG_CXX)
#define MISC_LANG_CXX03			((1 << 2) | MISC_LANG_CXX98)
#define MISC_LANG_CXX0X			((1 << 3) | MISC_LANG_CXX03)
#define MISC_LANG_CXX11			((1 << 4) | MISC_LANG_CXX0X)
#define MISC_LANG_CXXMS			(1 << 5)
#define MISC_LANG_CXXGNU		(1 << 6)

#if(defined(MISC_FORCE_CXX11))
#	define MISC_LANG MISC_LANG_CXX11
#elif(defined(MISC_FORCE_CXX03))
#	define MISC_LANG MISC_LANG_CXX03
#elif(defined(MISC_FORCE_CXX98))
#	define MISC_LANG MISC_LANG_CXX98
#else
//  -std=c++0x or -std=gnu++0x
#	if(((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC) && defined(__GXX_EXPERIMENTAL_CXX0X__)) 
#		define MISC_LANG MISC_LANG_CXX0X
#	elif(((MISC_COMPILER & MISC_COMPILER_VC) == MISC_COMPILER_VC) && defined(_MSC_EXTENSIONS))
#		define MISC_LANG MISC_LANG_CXXMS
#	elif(((MISC_COMPILER & MISC_COMPILER_VC) == MISC_COMPILER_VC) && !defined(_MSC_EXTENSIONS))
#		if(MISC_COMPILER >= MISC_COMPILER_VC2010)
#			define MISC_LANG MISC_LANG_CXX0X
#		else
#			define MISC_LANG MISC_LANG_CXX98
#		endif//(MISC_COMPILER == MISC_COMPILER_VC2010)
#	elif((MISC_COMPILER & MISC_COMPILER_GCC) == MISC_COMPILER_GCC) //&& defined(__STRICT_ANSI__))
#		define MISC_LANG MISC_LANG_CXX98
#	else
#		define MISC_LANG MISC_LANG_CXX
#	endif
#endif

#if(defined(MISC_MESSAGES) && !defined(MISC_MESSAGE_LANG_DISPLAYED))
#	define MISC_MESSAGE_LANG_DISPLAYED
#	if(MISC_LANG == MISC_LANG_CXX98)
#		pragma message("MISC: C++98")
#	elif(MISC_LANG == MISC_LANG_CXX03)
#		pragma message("MISC: C++03")
#	elif(MISC_LANG == MISC_LANG_CXX0X)
#		pragma message("MISC: C++0x")
#	elif(MISC_LANG == MISC_LANG_CXX11)
#		pragma message("MISC: C++11")
#	elif(MISC_LANG == MISC_LANG_CXXGNU)
#		pragma message("MISC: C++ with GNU language extensions")
#	elif(MISC_LANG == MISC_LANG_CXXMS)
#		pragma message("MISC: C++ with VC language extensions")
#   else
#       pragma message("MISC: C++ language undetected")
#	endif//MISC_MODEL
#endif//MISC_MESSAGE

//////////////////////////////////////////////////////////////////////////
// Qualifiers
#if(defined(MISC_FORCE_INLINE))
#   if((MISC_COMPILER & MISC_COMPILER_VC) && (MISC_COMPILER >= MISC_COMPILER_VC2005))
#       define MISC_INLINE __forceinline
#   elif((MISC_COMPILER & MISC_COMPILER_GCC) && (MISC_COMPILER >= MISC_COMPILER_GCC34))
#       define MISC_INLINE __attribute__((always_inline))
#   else
#       define MISC_INLINE inline
#   endif//MISC_COMPILER
#else
#   define MISC_INLINE inline
#endif//defined(MISC_FORCE_INLINE)

#define MISC_FUNC_DECL	
#define MISC_FUNC_QUALIFIER		MISC_INLINE

#endif//misc_setup