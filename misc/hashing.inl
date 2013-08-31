namespace misc{

	inline size_t FNV_1a_fun( const unsigned char* buf, size_t count )
	{
#	ifdef ENVIRONMENT64
		const size_t _FNV_offset_basis = 14695981039346656037ULL;
		const size_t _FNV_prime = 1099511628211ULL;
#	else
		const size_t _FNV_offset_basis = 2166136261U;
		const size_t _FNV_prime = 16777619U;
#	endif
		size_t val = _FNV_offset_basis;
		for (size_t i = 0; i < count; i++) {
			val ^= (size_t)buf[i];
			val *= _FNV_prime;
		}
#	ifdef ENVIRONMENT64
		val ^= val >> 32;
#	endif
		return val;
	}

} // namespace misc
