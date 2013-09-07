#ifndef misc_hashing
#define misc_hashing

namespace misc {

//////////////////////////////////////////////////////////////////////////
//
// refer to: http://programmers.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
// https://code.google.com/p/smhasher/wiki/MurmurHash3
//
// Hash Function: FNV-1a (vs stl)
//
// Hash Table: STL unordered_set (open address)
//
// Rabin-Karp algorithm (Rolling hash)
//
//////////////////////////////////////////////////////////////////////////

	inline size_t FNV_1a_fun(const unsigned char* buf, size_t count);

	template<class T>
	struct FNV_1a_base {
		size_t operator()(const T& val) const {
			return (FNV_1a_fun((const unsigned char *)&val, sizeof(T)));
		}
	};

	template <typename T>
	struct FNV_1a : public FNV_1a_base<T>{};

	template <>
	struct FNV_1a<int> : public FNV_1a_base<int>{};

	template <>
	struct FNV_1a<bool> : public FNV_1a_base<bool>{};

	template <>
	struct FNV_1a<char> : public FNV_1a_base<char>{};

	template <>
	struct FNV_1a<float> : public FNV_1a_base<float>
	{
		typedef float T;
		typedef FNV_1a_base<T> base_type;

		size_t operator()(const T& val) const {
			return (base_type::operator()(
				val == 0 ? 0 : val)); // map -0 to 0
		}
	};

	template<typename T>
	struct FNV_1a<T *>: public FNV_1a_base<T *>{};

	template<typename Elem, typename Traits, typename Alloc>
	struct FNV_1a<std::basic_string<Elem, Traits, Alloc>> {
		typedef std::basic_string<Elem, Traits, Alloc> T;

		size_t operator()(const T& val) const {
			return FNV_1a_fun((const unsigned char*)val.c_str(),
				val.size() * sizeof(T));
		}
	};

	// http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
	inline size_t Paul_Larson_hash(const char* s)
	{
		const size_t SALT = 0;
		size_t h = SALT;
		while (*s)
			h = h * 101 + (unsigned char) *s++;
		return h;
	}

} // misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "hashing.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_hashing
