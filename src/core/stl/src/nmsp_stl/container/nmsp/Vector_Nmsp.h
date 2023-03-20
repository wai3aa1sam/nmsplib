#pragma once

#include "../nmspContainer_Common.h"
#include "../../allocator/nmspVectorAllocator.h"

namespace nmsp {

template<class T, size_t N, bool ENABLE_FALLBACK_ALLOC, class FALLBACK_ALLOCATOR> class Vector_Nmsp;

#if 0
#pragma mark --- VectorBase_Nmsp-Decl
#endif // 0
#if 1

template<class T, class ALLOCATOR = DefaultAllocator>
class VectorBase_Nmsp
{
public:
	using ValueType = T;
	using SizeType = size_t;
	using Allocator = ALLOCATOR;

public:
	using This			= VectorBase_Nmsp<T, Allocator>;
	using VectorBase	= This;
public:
	VectorBase_Nmsp();
	VectorBase_Nmsp(const Allocator& alloc);
	VectorBase_Nmsp(SizeType n, const Allocator& alloc);

	~VectorBase_Nmsp();

	bool is_empty() const;
	constexpr SizeType capacity()	const;
	constexpr SizeType size()		const;

protected:
	T*& _last();
	T* _last() const;
	Allocator& _allocator();

	T* _on_allocate(SizeType n);
	void		_on_free(T* p, SizeType n);
	SizeType	_get_new_capacity(SizeType currentCap_, SizeType requestCap_);

	constexpr SizeType	_get_bytes(SizeType n);

	void _assert_boundary(SizeType i_)	const;
	void _assert_boundary(T* p)			const;

protected:
	T* _begin = nullptr;
	T* _end = nullptr;
	CompressedPair<T*, Allocator> _pair;
private:

};

#endif

#if 0
#pragma mark --- IVector_Nmsp-Decl
#endif // 0
#if 1

template<class T, class ALLOCATOR = DefaultAllocator>
class IVector_Nmsp : public VectorBase_Nmsp<T, ALLOCATOR>
{

};

#endif

#if 0
#pragma mark --- Vector_Nmsp-Decl
#endif // 0
#if 1

template<class T, size_t N = 0, bool ENABLE_FALLBACK_ALLOC = true, class FALLBACK_ALLOCATOR = DefaultAllocator>
class Vector_Nmsp : public IVector_Nmsp<T, FALLBACK_ALLOCATOR>, public VectorAllocator_T<T, N, s_kDefaultAlign, ENABLE_FALLBACK_ALLOC, FALLBACK_ALLOCATOR>
{

};


#endif

#if 0
#pragma mark --- VectorBase_Nmsp-Impl
#endif // 0
#if 1

template<class T, class ALLOCATOR>
VectorBase_Nmsp<T, ALLOCATOR>::VectorBase_Nmsp()
{

}

template<class T, class ALLOCATOR>
VectorBase_Nmsp<T, ALLOCATOR>::~VectorBase_Nmsp()
{

}

#endif

#if 0
#pragma mark --- IVector_Nmsp-Impl
#endif // 0
#if 1


#endif


#if 0
#pragma mark --- Vector_Nmsp-Impl
#endif // 0
#if 1


#endif





}