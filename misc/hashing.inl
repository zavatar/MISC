namespace misc{

	MISC_FUNC_QUALIFIER size_t FNV_1a_fun( const unsigned char* buf, size_t count )
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

	MISC_FUNC_QUALIFIER size_t Paul_Larson_hash(const char* s)
	{
		const size_t SALT = 0;
		size_t h = SALT;
		while (*s)
			h = h * 101 + (unsigned char) *s++;
		return h;
	}

	MISC_FUNC_QUALIFIER rabin_karp::rabin_karp(const char* s, int m)
	{
		assert(m>0);
		sq.push(s[0]);
		h=1; val=s[0]%Q;
		for(int i=1; i<m; i++) {
			h = (h*D) % Q; // (h^m-1)%Q
			val = (val*D + s[i]) % Q; // hash(0,m-1)
			sq.push(s[i]);
		}
	}

	MISC_FUNC_QUALIFIER int rabin_karp::hash()
	{
		return val;
	}

	MISC_FUNC_QUALIFIER int rabin_karp::rehash(const char& c)
	{
		val = (D*(val - h*sq.front()) + c) % Q;
		if (val < 0) val += Q;
		sq.pop();
		sq.push(c);
		return val;
	}

	MISC_FUNC_QUALIFIER int rabin_karp::size()
	{
		return sq.size();
	}

	MISC_FUNC_QUALIFIER void rabin_karp::push(const char& c)
	{
		h = (h*D) % Q;
		val = (D*val + c) % Q;
		sq.push(c);
	}

} // namespace misc
