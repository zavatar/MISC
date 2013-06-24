#ifndef misc_intrinsics
#define misc_intrinsics

#if MISC_ISVC
#include <intrin.h>
#elif MISC_ISGCC
#include <x86intrin.h>
#endif

namespace misc {



} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "intrinsics.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_intrinsics
