#ifndef misc_setup
#define misc_setup

//////////////////////////////////////////////////////////////////////////
// Version
#define MISC_VERSION			13
#define MISC_VERSION_MAJOR		0
#define MISC_VERSION_MINOR		2

//////////////////////////////////////////////////////////////////////////
// Platform
#define MISC_PLATFORM_UNKNOWN		0x00000000
#define MISC_PLATFORM_WINDOWS		0x00010000
#define MISC_PLATFORM_LINUX			0x00020000
#define MISC_PLATFORM_UNIX			0x00040000

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
#	if(MISC_PLATFORM == MISC_PLATFORM_WINDOWS)
#		pragma message("MISC: Windows platform detected")
#	elif(MISC_PLATFORM == MISC_PLATFORM_LINUX)
#		pragma message("MISC: Linux platform detected")
#	elif(MISC_PLATFORM == MISC_PLATFORM_UNIX)
#		pragma message("MISC: UNIX platform detected")
#	elif(MISC_PLATFORM == MISC_PLATFORM_UNKNOWN)
#		pragma message("MISC: platform unknown")
#	else
#		error("MISC: platform not detected")
#	endif
#endif

//////////////////////////////////////////////////////////////////////////
// Compiler
#define MISC_COMPILER_UNKNOWN			0x00000000

// Visual C++ defines
#define MISC_COMPILER_VC				0x01000000
#define MISC_COMPILER_VC2012			0x01000020

// GCC defines
#define MISC_COMPILER_GCC				0x02000000
#define MISC_COMPILER_GCC47				0x02000010
#define MISC_COMPILER_GCC48				0x02000020

// Force generic C++ compiler
#ifdef MISC_FORCE_COMPILER_UNKNOWN
#	define MISC_COMPILER MISC_COMPILER_UNKNOWN
#elif defined(_MSC_VER) // Visual C++
#	if _MSC_VER == 1700
#		define MISC_COMPILER MISC_COMPILER_VC2012
#	else//_MSC_VER
#		define MISC_COMPILER MISC_COMPILER_VC
#	endif//_MSC_VER
#elif(defined(__GNUC__) || defined(__MINGW32__)) // G++
#	if   (__GNUC__ == 4) && (__GNUC_MINOR__ == 7)
#		define MISC_COMPILER MISC_COMPILER_GCC47
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)
#		define MISC_COMPILER MISC_COMPILER_GCC48
#	else
#		define MISC_COMPILER MISC_COMPILER_GCC
#	endif
#else
#	define MISC_COMPILER MISC_COMPILER_UNKNOWN
#endif

#if(defined(MISC_MESSAGES) && !defined(MISC_MESSAGE_COMPILER_DISPLAYED))
#	define MISC_MESSAGE_COMPILER_DISPLAYED
#	if(MISC_COMPILER == MISC_COMPILER_VC2012)
#		pragma message("MISC: Visual Studio 2012")
#	elif(MISC_COMPILER == MISC_COMPILER_GCC47)
#		pragma message("MISC: GCC 4.7")
#	elif(MISC_COMPILER == MISC_COMPILER_GCC48)
#		pragma message("MISC: GCC 4.8")
#   elif(MISC_COMPILER == MISC_COMPILER_VC)
#       error("MISC: Other VC compiler")
#   elif(MISC_COMPILER == MISC_COMPILER_GCC)
#       error("MISC: Other GCC compiler")
#	else
#		error("MISC: compiler not detected")
#	endif//MISC_MODEL
#endif//MISC_MESSAGE

#define MISC_ISGCC (MISC_COMPILER & MISC_COMPILER_GCC)
#define MISC_ISVC (MISC_COMPILER & MISC_COMPILER_VC)

//////////////////////////////////////////////////////////////////////////
// STL Version

#ifdef __GLIBCXX__
#	define MISC_STL_LIBSTDCXX __GLIBCXX__
#elif defined(__SGI_STL_PORT)
#	define MISC_STL_PORT __SGI_STL_PORT
#elif defined(_CPPLIB_VER)
#	define MISC_STL_VC _CPPLIB_VER
#endif

#if(defined(MISC_MESSAGES) && !defined(MISC_MESSAGE_STL_DISPLAYED))
#	define MISC_MESSAGE_STL_DISPLAYED
#	ifdef __GLIBCXX__
#		pragma message("MISC: libstdc++")
#	elif defined(__SGI_STL_PORT)
#		pragma message("MISC: STLPort")
#	elif defined(_CPPLIB_VER)
#		pragma message("MISC: VS Dinkumware STL")
#	else
#		error("MISC: Include setup.hpp after STL header file")
#	endif
#endif


//////////////////////////////////////////////////////////////////////////
// C++ Version
#define MISC_LANG_CXX			(0 << 0)
#define MISC_LANG_CXX98			(1 << 1)
#define MISC_LANG_CXX0X			(1 << 2)
#define MISC_LANG_CXX11			(1 << 3)

// http://gcc.gnu.org/gcc-4.7/changes.html
#if(MISC_ISGCC)
#	if(__cplusplus == 201103L)
#		define MISC_LANG MISC_LANG_CXX11
#	elif(__cplusplus == 199711L)
#		define MISC_LANG MISC_LANG_CXX98
#	else
#		define MISC_LANG MISC_LANG_CXX
#	endif
#elif(MISC_ISVC)
#	if(MISC_COMPILER == MISC_COMPILER_VC2012)
#		define MISC_LANG MISC_LANG_CXX0X
#	else
#		define MISC_LANG MISC_LANG_CXX98
#	endif
#else
#	define MISC_LANG MISC_LANG_CXX
#endif

#if(defined(MISC_MESSAGES) && !defined(MISC_MESSAGE_LANG_DISPLAYED))
#	define MISC_MESSAGE_LANG_DISPLAYED
#	if(MISC_LANG == MISC_LANG_CXX11)
#		pragma message("MISC: C++11")
#	elif(MISC_LANG == MISC_LANG_CXX0X)
#		pragma message("MISC: C++0x")
#	elif(MISC_LANG == MISC_LANG_CXX98)
#       error("MISC: C++98")
#   else
#       error("MISC: C++ language undetected")
#	endif//MISC_MODEL
#endif//MISC_MESSAGE

#define MISC_ISCXX11 (MISC_LANG == MISC_LANG_CXX11)
#define MISC_ISCXX0X (MISC_LANG == MISC_LANG_CXX0X)

//////////////////////////////////////////////////////////////////////////
// Qualifiers
#   if(MISC_ISVC)
#		define MISC_TALIAS ::type
#		define noexcept _THROW0()
#   elif(MISC_ISGCC)
#		define MISC_TALIAS
#   endif//MISC_COMPILER

#define MISC_FUNC_DECL	
#define MISC_FUNC_QUALIFIER inline

#endif//misc_setup