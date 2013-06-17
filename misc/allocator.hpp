#ifndef misc_allocator
#define misc_allocator

#include <memory.h>

#ifdef MISC_STL_LIBSTDCXX
#include <ext/pool_allocator.h>
#endif

namespace misc{

#ifdef MISC_STL_LIBSTDCXX
	template <typename _Ty>
	using new_alloc = __gnu_cxx::new_allocator<_Ty>;
	template <typename _Ty>
	using pool_alloc = __gnu_cxx::__pool_alloc<_Ty>;
#elif defined(MISC_STL_PORT)
	template <typename _Ty>
	struct new_alloc {}; // STLPort doesn't support changing allocator in runtime
	template <typename _Ty>
	struct pool_alloc {
		typedef std::allocator<_Ty> type;
	};
#elif defined(MISC_STL_VC)

	// C++11 Templates Aliases. 
	// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2258.pdf
	// template <typename _Ty>
	// using new_alloc = std::allocator<_Ty>;
	template <typename _Ty>
	struct new_alloc {
		typedef std::allocator<_Ty> type;
	};

	template <typename _Ty>
	struct value_type_traits {
		typedef _Ty value_type;
	};

	template <typename _Ty>
	struct value_type_traits<const _Ty> {
		typedef _Ty value_type;
	};

	template <int inst>
	class _alloc {
	public:
		// __n must be > 0
		static void* _allocate(size_t __n);

		// __p may not be 0
		static void _deallocate(void* __p, size_t __n);

		static void* _reallocate(void* __p, size_t __old_sz, size_t __new_sz);

	private:
		static const int _ALIGN = 8;
		static const int _MAX_BYTES = 128;
		static const int _NFREELISTS = 16; // _MAX_BYTES/_ALIGN

		union _Obj {
			union _Obj* _M_free_list_link;
			char _M_client_data[1];    // The client sees this.
		};

		static _Obj* _S_free_list[_NFREELISTS];

		static size_t _S_round_up(size_t __bytes) 
		{ return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }

		static size_t _S_freelist_index(size_t __bytes)
		{ return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1); }

		// Returns an object of size __n, and optionally adds to size __n free list.
		static void* _S_refill(size_t __n);
		// Allocates a chunk for nobjs of size size.  nobjs may be reduced
		// if it is inconvenient to allocate the requested number.
		static char* _S_chunk_alloc(size_t __size, int& __nobjs);

		// Chunk allocation state.
		static char* _S_start_free;
		static char* _S_end_free;
		static size_t _S_heap_size;
	};

	template <typename _Ty>
	class pool_alloc
	{
	public:
		typedef pool_alloc<_Ty> type; // for support template alias

		typedef typename value_type_traits<_Ty>::value_type value_type;

		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		typedef value_type& reference;
		typedef const value_type& const_reference;
		
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef _alloc<0> _Alloc_Proxy;

		template <typename _Other>
		struct rebind {
			typedef pool_alloc<_Other> other;
		};

		pointer address(reference __x) const { return std::addressof(__x); }
		const_pointer address(const_reference __x) const { return std::addressof(__x); }

		pool_alloc() noexcept {}
		pool_alloc(const pool_alloc&) noexcept {}
		template <class _Other> pool_alloc(const pool_alloc<_Other>&) noexcept {}
		template<class _Other> pool_alloc<_Ty>& operator=(const pool_alloc<_Other>&) {
			return (*this);
		}
		~pool_alloc() noexcept {}

		// __n is permitted to be 0.  The C++ standard says nothing about what
		// the return value is when __n == 0.
		_Ty* allocate(size_type __n, const void* = 0)
		{ return __n != 0 ? static_cast<_Ty*>(_Alloc_Proxy::_allocate(__n * sizeof(_Ty))) : 0; }

		// __p is not permitted to be a null pointer.
		void deallocate(pointer __p, size_type __n)
		{ _Alloc_Proxy::_deallocate(__p, __n * sizeof(_Ty)); }

		void construct(_Ty* __p, const _Ty& __val) { new(__p) _Ty(__val); }
		void destroy(_Ty* __p) { __p->~_Ty(); }

		size_type max_size() const noexcept
		{ return size_t(-1) / sizeof(_Ty); }

	};

	template<class _Ty,
	class _Other> inline
		bool operator==(const pool_alloc<_Ty>&,
		const pool_alloc<_Other>&) noexcept
	{	// test for allocator equality
		return (true);
	}

	template<class _Ty,
	class _Other> inline
		bool operator!=(const pool_alloc<_Ty>& _Left,
		const pool_alloc<_Other>& _Right) noexcept
	{	// test for allocator inequality
		return (false);
	}

#endif
} // namespace misc

#ifndef MISC_EXTERNAL_TEMPLATE
#include "allocator.inl"
#endif // !MISC_EXTERNAL_TEMPLATE

#endif // !misc_allocator