#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"
#include <EASTL/slist.h>
#include <EASTL/fixed_slist.h>

namespace nmsp {

#if 0
#pragma mark --- SList_Eastl-Impl ---
#endif // 0
#if 0

template<class T, int N = 0, class T_Deleter = DefaultDeleter<T>, class T_FallbackAlloc = DefaultAllocator>
class SList_T : public NonCopyable
{
public:
	using Int = i64;
	static constexpr Int s_kLocalSize = N ;

	// TODO: my Iterator for all container
	using Iter	= T*;
	using CIter = const T*;
	using UPtr  = UPtr_T<T, T_Deleter>;

public:
	~SList_T();
	SList_T();
	SList_T(const SList_T& v);
	SList_T(SList_T&& v);

	void operator=(const SList_T& v);
	void operator=(SList_T&& v);

public:
	void clear();
	void reserve(Int n);
	void resize(Int n);

	void insert(UPtr p);
	void append(UPtr p);

	UPtr popHeadPtr();
	UPtr popTailPtrSlow();

	UPtr popHead()	{ return popHeadPtr(); }
	UPtr popTail()	{ return popTailPtrSlow(); }

public:
	Int	size() const;

			T*  head();
	const	T*  head() const;

			T*  tail();
	const	T*  tail() const;

	Iter  begin();
	CIter begin() const;

	Iter  end();
	CIter end() const;

private:
	#if NMSP_STL_BUILD_CONTAINER_EASTL

	template<class T, size_t N, bool bEnableOverflow = true, class OverflowAllocator = DefaultAllocator>
	struct EASTL_SList
	{
		enum { s_kLocalSize = N };
		using This = eastl::fixed_slist<T, N, bEnableOverflow, OverflowAllocator>;
	};

	template<class T, class T_Allocator>
	struct EASTL_SList<T, 0, true, T_Allocator>
	{
		enum { s_kLocalSize = 0 };
		using This = eastl::slist<T, T_Allocator>;
	};
	
	using Data_T = typename EASTL_SList<UPtr, N, !IsSame<T_FallbackAlloc, NoFallbackAllocator_Policy>, T_FallbackAlloc>::This;
	Data_T _data;
	T*   _tail() 
	{
		NMSP_TODO("temp: workaround");
		T* last = nullptr;
		for (auto& e : _data)
		{
			last = e.ptr();
		}
		return last;
	}
	const T*   _tail() const
	{
		NMSP_TODO("temp: workaround");
		const T* last = nullptr;
		for (auto& e : _data)
		{
			last = e.ptr();
		}
		return last;
	}



	#else
	#error "--- error: nmsp_stl unsupported build container"
	#endif
};

#endif

#if 0
#pragma mark --- SList_Eastl-Impl ---
#endif // 0
#if 0

#if NMSP_STL_BUILD_CONTAINER_EASTL

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
SList_T<T, N, T_Deleter, T_FallbackAlloc>::~SList_T()
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
SList_T<T, N, T_Deleter, T_FallbackAlloc>::SList_T()
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
SList_T<T, N, T_Deleter, T_FallbackAlloc>::SList_T(const SList_T& v)
	: _data(v)
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
SList_T<T, N, T_Deleter, T_FallbackAlloc>::SList_T(SList_T&& v)
	: _data(nmsp::move(v))
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::operator=(const SList_T& v)
{
	data = v;
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::operator=(SList_T&& v)
{
	data = nmsp::move(v);
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::clear()
{
	_data.clear();
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::reserve(Int n)
{
	_data.reserve(n);
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::resize(Int n)
{
	_data.resize(n);
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::insert(UPtr p)
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
void 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::append(UPtr p)
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto
SList_T<T, N, T_Deleter, T_FallbackAlloc>::popHeadPtr() 
-> UPtr
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto
SList_T<T, N, T_Deleter, T_FallbackAlloc>::popTailPtrSlow()
-> UPtr
{

}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::size() const 
-> Int 
{ 
	return sCast<Int>(data.size());
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::head() const
-> const T*
{
	return ;
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::head() const 
-> const T*
{
	return ;
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::tail() const
-> const T*
{
	return _data.end();
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::tail() const 
-> const T*
{
	return _data.end();
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::begin() -> Iter
{
	return _data.begin();
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::begin() const -> CIter
{
	return _data.begin();
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::end() -> Iter
{
	return _data.end();
}

template<class T, int N, class T_Deleter, class T_FallbackAlloc> inline
auto 
SList_T<T, N, T_Deleter, T_FallbackAlloc>::end() const -> CIter
{
	return _data.end();
}

#endif // NMSP_STL_BUILD_CONTAINER_EASTL

#endif

}
