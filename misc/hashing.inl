namespace misc{

	inline size_t FNV_1a_fun( const unsigned char* buf, size_t count )
	{
		static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
		const size_t _FNV_offset_basis = 2166136261U;
		const size_t _FNV_prime = 16777619U;

		size_t val = _FNV_offset_basis;
		for (size_t i = 0; i < count; i++) {
			val ^= (size_t)buf[i];
			val *= _FNV_prime;
		}
		return val;
	}


} // namespace misc
