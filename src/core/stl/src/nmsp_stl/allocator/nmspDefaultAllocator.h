#pragma once

#include "nmspAllocator_Common.h"

namespace nmsp {

#if 0
#pragma mark --- DefaultAllocator-Decl
#endif // 0
#if 1


template<size_t ALIGN = s_kDefaultAlign>
class DefaultAllocator_T
{
public:
	using SizeType = size_t;

	static constexpr SizeType s_kAlignment = ALIGN;

	void* alloc(SizeType n)
	{
		intptr_t new_n = _alignTo(n, s_kAlignment);
		return new u8[new_n];
	}

	void free(void* p, size_t n)
	{
		delete[] p;
	}

	//void freeAll() { _offset = _storage; }
	//bool isOwn(void* p) const { return p >= _storage && p < _storage + N; }
};

using DefaultAllocator = DefaultAllocator_T<s_kDefaultAlign>;

#endif

}


