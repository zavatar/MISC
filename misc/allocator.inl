namespace misc{

#if defined(MISC_STL_VC)

	template <int inst>
	void* _alloc<inst>::_allocate(size_t __n)
	{
		void* __ret = 0;

		if (__n > (size_t) _MAX_BYTES) {
			__ret = (void*)std::_Allocate(__n, (char*)0);
		} else {
			_Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__n);
			_Obj* __result = *__my_free_list;
			if (__result == 0)
				__ret = _S_refill(_S_round_up(__n));
			else {
				*__my_free_list = __result -> _M_free_list_link;
				__ret = __result;
			}
		}

		return __ret;
	}

	template <int inst>
	void _alloc<inst>::_deallocate(void* __p, size_t __n)
	{
		if (__n > (size_t) _MAX_BYTES)
			delete(__p);
		else {
			_Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__n);
			_Obj* __q = (_Obj*)__p;
			__q -> _M_free_list_link = *__my_free_list;
			*__my_free_list = __q;
		}
	}

	template <int inst>
	void* _alloc<inst>::_reallocate(void* __p, size_t __old_sz, size_t __new_sz)
	{
		void* __result;
		size_t __copy_sz;

		if (__old_sz > (size_t) _MAX_BYTES && __new_sz > (size_t) _MAX_BYTES) {
			return(realloc(__p, __new_sz));
		}
		if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) return(__p);
		__result = allocate(__new_sz);
		__copy_sz = __new_sz > __old_sz? __old_sz : __new_sz;
		memcpy(__result, __p, __copy_sz);
		deallocate(__p, __old_sz);
		return(__result);
	}

	// We allocate memory in large chunks in order to avoid fragmenting
	// the malloc heap too much.
	// We assume that size is properly aligned.
	// We hold the allocation lock.
	template <int inst>
	char* _alloc<inst>::_S_chunk_alloc(size_t __size, int& __nobjs)
	{
		char* __result;
		size_t __total_bytes = __size * __nobjs;
		size_t __bytes_left = _S_end_free - _S_start_free;

		if (__bytes_left >= __total_bytes) {
			__result = _S_start_free;
			_S_start_free += __total_bytes;
			return(__result);
		} else if (__bytes_left >= __size) {
			__nobjs = (int)(__bytes_left/__size);
			__total_bytes = __size * __nobjs;
			__result = _S_start_free;
			_S_start_free += __total_bytes;
			return(__result);
		} else {
			size_t __bytes_to_get = 
				2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
			// Try to make use of the left-over piece.
			if (__bytes_left > 0) {
				_Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__bytes_left);
				((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;
				*__my_free_list = (_Obj*)_S_start_free;
			}
			_S_start_free = (char*)malloc(__bytes_to_get);
			if (0 == _S_start_free) {
				size_t __i;
				_Obj* volatile* __my_free_list;
				_Obj* __p;
				// Try to make do with what we have.  That can't
				// hurt.  We do not try smaller requests, since that tends
				// to result in disaster on multi-process machines.
				for (__i = __size;
					__i <= (size_t) _MAX_BYTES;
					__i += (size_t) _ALIGN) {
						__my_free_list = _S_free_list + _S_freelist_index(__i);
						__p = *__my_free_list;
						if (0 != __p) {
							*__my_free_list = __p -> _M_free_list_link;
							_S_start_free = (char*)__p;
							_S_end_free = _S_start_free + __i;
							return(_S_chunk_alloc(__size, __nobjs));
							// Any leftover piece will eventually make it to the
							// right free list.
						}
				}
				_S_end_free = 0;	// In case of exception.
				_S_start_free = std::_Allocate(__bytes_to_get, (char*)0);
				// This should either throw an
				// exception or remedy the situation.  Thus we assume it
				// succeeded.
			}
			_S_heap_size += __bytes_to_get;
			_S_end_free = _S_start_free + __bytes_to_get;
			return(_S_chunk_alloc(__size, __nobjs));
		}
	}

	// Returns an object of size __n, and optionally adds to size __n free list.
	// We assume that __n is properly aligned.
	// We hold the allocation lock.
	template <int inst>
	void* _alloc<inst>::_S_refill(size_t __n)
	{
		int __nobjs = 20;
		char* __chunk = _S_chunk_alloc(__n, __nobjs);
		_Obj* volatile* __my_free_list;
		_Obj* __result;
		_Obj* __current_obj;
		_Obj* __next_obj;
		int __i;

		if (1 == __nobjs) return(__chunk);
		__my_free_list = _S_free_list + _S_freelist_index(__n);

		/* Build free list in chunk */
		__result = (_Obj*)__chunk;
		*__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
		for (__i = 1; ; __i++) {
			__current_obj = __next_obj;
			__next_obj = (_Obj*)((char*)__next_obj + __n);
			if (__nobjs - 1 == __i) {
				__current_obj -> _M_free_list_link = 0;
				break;
			} else {
				__current_obj -> _M_free_list_link = __next_obj;
			}
		}
		return(__result);
	}

	template <int inst>
	typename _alloc<inst>::_Obj* _alloc<inst>::_S_free_list[_alloc<inst>::_NFREELISTS] =
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

	template <int inst>
	char* _alloc<inst>::_S_start_free = 0;

	template <int inst>
	char* _alloc<inst>::_S_end_free = 0;

	template <int inst>
	size_t _alloc<inst>::_S_heap_size = 0;

#endif

} // namespace misc