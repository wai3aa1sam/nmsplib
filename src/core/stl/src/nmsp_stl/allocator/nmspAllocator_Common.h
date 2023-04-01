#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp {

static constexpr size_t s_kDefaultAlign = NMSP_ALIGN_OF(std::max_align_t);

template<class T>
static constexpr T _alignTo(T n, T a) 
{
	static_assert(IsUnsigned<T>, "");
	T r = n % a;
	return r ? (n + a - r) : n;
}

#if 0
#pragma mark --- Allocator_Base-Decl ---
#endif // 0
#if 1

template<class ALLOC>
class Allocator_Base : public ALLOC
{
public:
	using This = Allocator_Base<ALLOC>;
public:
	using SizeType = size_t;

public:
	Allocator_Base()	= default;
	~Allocator_Base()	= default;

	void* alloc(SizeType n, SizeType align = s_kDefaultAlign, SizeType offset = 0);
	void* alloc_all(SizeType n);

	void free(void* p, SizeType n = 0);
	void free_all();

	bool is_owning(void* p, SizeType n);

	bool operator==(const Allocator_Base& rhs);
	bool operator!=(const Allocator_Base& rhs);
private:
};

#endif

}