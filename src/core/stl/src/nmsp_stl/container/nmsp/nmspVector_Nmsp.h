#pragma once

#include "../nmspContainer_Common.h"
#include "../../allocator/nmspLocalAllocator.h"

/*
references
- eastl: https://github.com/electronicarts/EASTL
- SimpleTalkCpp: https://github.com/SimpleTalkCpp/SimpleTalkCpp_Tutorial/blob/main/Advance%20C%2B%2B/001%20MyVector/MyVector.h
*/

namespace nmsp {

#if !NMSP_ENABLE_IVECTOR
	template<typename T, size_t LOCAL_COUNT, class FALLBACK_ALLOC = DefaultAllocator >
	using VectorAllocator_T = class LocalAllocator_T<LOCAL_COUNT * sizeof(T), NMSP_ALIGN_OF(T), 0, FALLBACK_ALLOC>;
#endif // 0


#if 0
#pragma mark --- VectorBase_Nmsp-Decl ---
#endif // 0
#if 1

template<class T, class ALLOC = DefaultAllocator>
class VectorBase_Nmsp
{
public:
	using ValueType = T;
	using SizeType = size_t;
	using Allocator = ALLOC;

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

	T*			_on_allocate(SizeType n);
	void		_on_free(T* p, SizeType n);
	SizeType	_get_new_capacity(SizeType currentCap_, SizeType requestCap_);

	constexpr SizeType	_get_bytes(SizeType n);

	void _assert_boundary(SizeType i)	const;
	void _assert_boundary(T* p)			const;

protected:
	T* _begin	= nullptr;
	T* _end		= nullptr;
	CompressedPair<T*, Allocator> _pair;
private:

};

#endif

#if 0
#pragma mark --- IVector_Nmsp-Decl ---
#endif // 0
#if 1

template<class T, class ALLOC = DefaultAllocator>
class IVector_Nmsp : public VectorBase_Nmsp<T, ALLOC>
{
public:
	using Allocator		= ALLOC;
	using Base			= VectorBase_Nmsp<T, Allocator>;
	using ValueType		= T;
	using SizeType		= typename Base::SizeType;
	using Ptr			= T*;
	using Ref			= T&;

#if 1
	using Iter = T*;
	using CIter = const T*;
#else
	using Iter = IterT<T>;
	using CIter = IterT<const T>;
#endif // 0

	using RevIter	= RevIter_T<Iter>;
	using CRevIter	= RevIter_T<CIter>;

	using RevEnumerator		= RevEnumerator_T<RevIter>;
	using CRevEnumerator	= RevEnumerator_T<CRevIter>;

public:
	using Base = VectorBase_Nmsp<T, ALLOC>;
	using This = IVector_Nmsp<T, Allocator>;

	using IVector = This;

	using Base::size;
	using Base::capacity;

public:
	IVector_Nmsp();
	explicit IVector_Nmsp(const Allocator& alloc);
	explicit IVector_Nmsp(SizeType n, const Allocator& alloc = Allocator);
	IVector_Nmsp(SizeType n, const T& v, const Allocator& alloc = Allocator);
	IVector_Nmsp(const This& rhs_);
	IVector_Nmsp(const This& rhs_, const Allocator& alloc);
	IVector_Nmsp(This&& rhs_) NMSP_NOEXCEPT;
	IVector_Nmsp(This&& rhs_, const Allocator& alloc);
	IVector_Nmsp(std::initializer_list<T> ilist, const Allocator& alloc = Allocator);

	template <typename Iter>
	IVector_Nmsp(Iter beg, Iter end, const Allocator& alloc = Allocator);

	#if NMSP_ENABLE_IVECTOR
	virtual ~IVector_Nmsp();
	#else
	~IVector_Nmsp();
	#endif

	void operator=(const This& x);
	void operator=(std::initializer_list<T> ilist);
	void operator=(This&& x);

	void swap(This& x);

	void assign(SizeType n, const T& v);
	template <typename Iter>
	void assign(Iter beg, Iter end);
	void assign(std::initializer_list<T> ilist);

	void reserve(SizeType n);
	void resize(SizeType n);
	void resize(SizeType n, const T& v);

	void clear();
	void clear_and_free();
	void shrink_to_fit();
	void reset_to_local();

	T& push_back();
	T& push_back(const T& v);
	T& push_back(T&& v);

	template<class... ARGS>
	Ref emplace_back(ARGS&&... args);

	template<class... ARGS>
	Iter emplace(CIter pos, ARGS&&... args);

	template<class... ARGS>
	Iter emplace_range(CIter pos, SizeType n, ARGS&&... args);

	Iter insert(CIter pos, const T& v);
	Iter insert(CIter pos, SizeType n, const T& v);
	Iter insert(CIter pos, CIter otherBeg, CIter otherEnd);

	void pop_back();

	Iter erase(SizeType i);
	Iter erase(CIter pos);
	Iter erase(CIter beg, CIter end);
	Iter erase_unsorted(SizeType i);
	Iter erase_unsorted(CIter pos);

	RevIter erase(CRevIter pos);
	RevIter erase(CRevIter beg, CRevIter end);
	RevIter erase_unsorted(CRevIter pos);

	Iter	erase_first(const T& v);
	Iter	erase_first_unsorted(const T& v);
	RevIter	erase_last(const T& v);
	RevIter	erase_last_unsorted(const T& v);

			ValueType* data();
	const	ValueType* data() const;

			ValueType& operator[](SizeType i);
	const	ValueType& operator[](SizeType i) const;

			ValueType& front();
	const	ValueType& front() const;

			ValueType& back();
	const	ValueType& back() const;

			ValueType& at(SizeType i);
	const	ValueType& at(SizeType i) const;

	Iter		begin();
	CIter		begin() const;
	CIter		cbegin() const;

	Iter		end();
	CIter		end() const;
	CIter		cend() const;

	RevIter     rbegin();
	CRevIter	rbegin() const;
	CRevIter	crbegin() const;

	RevIter     rend();
	CRevIter	rend() const;
	CRevIter	crend() const;

	RevEnumerator	revEach();
	CRevEnumerator	revEach() const;

protected:
	#if NMSP_ENABLE_IVECTOR
	virtual T*		_on_allocate(SizeType n);
	virtual void	_on_free(T* ptr_, SizeType n)	= 0;
	#else
	using Base::_on_allocate;
	using Base::_on_free;
	#endif

	void _on_reserve(SizeType oldCap, SizeType oldSize, SizeType n);
	
	template<class... ARGS>
	void _on_resize(SizeType n, ARGS&&... args);

	template<class... ARGS>
	void _append(SizeType n, ARGS&&... args);

	//template<class... ARGS>
	//void _onappendback(SizeType n, ARGS&&... args);

	template<class... ARGS>
	Iter _on_insert(CIter pos, SizeType n, ARGS&&... args);

	Iter _on_insert_iters(CIter pos, CIter beg, CIter end);

	void _on_move_destruct(Iter dst, Iter srcBeg, Iter srcEnd);

protected:
	using Base::_begin;
	using Base::_end;
	using Base::_pair;
	using Base::_last;
	using Base::_allocator;
	using Base::_get_bytes;
	using Base::_assert_boundary;
	using Base::is_empty;
};

#endif

#if 0
#pragma mark --- Vector_Nmsp-Decl ---
#endif // 0
#if 1

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>
class Vector_Nmsp : 
	#if NMSP_ENABLE_IVECTOR
		public IVector_Nmsp<T, FALLBACK_ALLOC>, protected LocalBuffer_T<N * sizeof(T), NMSP_ALIGN_OF(T)>
	#else
		public IVector_Nmsp<T, VectorAllocator_T<T, N, FALLBACK_ALLOC> >
	#endif
{
public:
	using FallbackAllocator = FALLBACK_ALLOC;
	#if NMSP_ENABLE_IVECTOR
		using Allocator		 = FallbackAllocator;
		using LocalAllocator = typename LocalBuffer_T<N * sizeof(T), NMSP_ALIGN_OF(T)>;
	#else
		using Allocator		 = VectorAllocator_T<T, N, FallbackAllocator>;
		using LocalAllocator = typename VectorAllocator_T<T, N, FallbackAllocator>::PrimaryAllocator;
	#endif

	using Base			= IVector_Nmsp<T, Allocator>;
	using This			= Vector_Nmsp<T, N, FALLBACK_ALLOC>;
public:
	using SizeType	= typename LocalAllocator::SizeType;
	using ValueType = T;

	static constexpr SizeType s_kLocalCount				= N;
	static constexpr SizeType s_kLocalSize				= N * sizeof(T);
	static constexpr SizeType s_kAlign					= FallbackAllocator::s_kAlign;
	static constexpr bool	  s_enableFallbackAlloc		= !IsSame<FallbackAllocator, NoFallbackAllocator_Policy>;

public:
	Vector_Nmsp();
	#if NMSP_ENABLE_IVECTOR
	virtual ~Vector_Nmsp();
	#else
	~Vector_Nmsp();
	#endif

public:


protected:
	#if NMSP_ENABLE_IVECTOR
	virtual T*		_on_allocate(SizeType n);
	virtual void	_on_free(T* ptr_, SizeType n);
	#else
	using Base::_on_allocate;
	using Base::_on_free;

	#endif

protected:
	LocalAllocator& _localAllocator();
};

#endif

#if 0
#pragma mark --- VectorBase_Nmsp-Impl ---
#endif // 0
#if 1

template<class T, class ALLOC> inline
VectorBase_Nmsp<T, ALLOC>::VectorBase_Nmsp()
	:
	_begin(nullptr), _end(nullptr)
{
	_last() = nullptr;
}

template<class T, class ALLOC> inline
VectorBase_Nmsp<T, ALLOC>::~VectorBase_Nmsp()	
{
	_on_free(_begin, capacity());
}

template<class T, class ALLOC> inline constexpr typename VectorBase_Nmsp<T, ALLOC>::SizeType	VectorBase_Nmsp<T, ALLOC>::capacity() const { return _last() - _begin; }
template<class T, class ALLOC> inline constexpr typename VectorBase_Nmsp<T, ALLOC>::SizeType	VectorBase_Nmsp<T, ALLOC>::size() const		{ return _end - _begin; }

template<class T, class ALLOC> inline T*&		VectorBase_Nmsp<T, ALLOC>::_last()			{ return _pair.first(); }
template<class T, class ALLOC> inline T*		VectorBase_Nmsp<T, ALLOC>::_last() const	{ return _pair.first(); }
template<class T, class ALLOC> inline ALLOC&	VectorBase_Nmsp<T, ALLOC>::_allocator()		{ return _pair.second(); }

template<class T, class ALLOC> inline constexpr typename VectorBase_Nmsp<T, ALLOC>::SizeType	
VectorBase_Nmsp<T, ALLOC>::_get_bytes(SizeType n) { return sizeof(T) * n; }

template<class T, class ALLOC> inline
T* VectorBase_Nmsp<T, ALLOC>::_on_allocate(SizeType n)
{
	auto* ptr = static_cast<T*>(_allocator().alloc(_get_bytes(n)));
	_last() = ptr + n;
	return ptr;
}

template<class T, class ALLOC> inline
void VectorBase_Nmsp<T, ALLOC>::_on_free(T* ptr, SizeType n)
{
	if(ptr)
		_allocator().free(ptr, _get_bytes(n));
}

template<class T, class ALLOC> inline typename VectorBase_Nmsp<T, ALLOC>::SizeType 
VectorBase_Nmsp<T, ALLOC>::_get_new_capacity(SizeType currentCap, SizeType requestCap)
{
	NMSP_ASSERT(requestCap > 0);
	auto newCap = currentCap * 2;
	return (currentCap == 0 || newCap < requestCap) ? requestCap : newCap;
}

template<class T, class ALLOC> inline void VectorBase_Nmsp<T, ALLOC>::_assert_boundary(SizeType i) const	{ NMSP_ASSERT(_begin + i < _end,		"VectorBase_Nmsp out of boundary"); }
template<class T, class ALLOC> inline void VectorBase_Nmsp<T, ALLOC>::_assert_boundary(T* p) const			{ NMSP_ASSERT(p >= _begin && p <= _end,	"VectorBase_Nmsp out of boundary"); }

template<class T, class ALLOC> inline bool VectorBase_Nmsp<T, ALLOC>::is_empty() const { return _begin == _end; }

#endif

#if 0
#pragma mark --- IVector_Nmsp-Impl ---
#endif // 0
#if 1

template<class T, class ALLOC> inline
IVector_Nmsp<T, ALLOC>::IVector_Nmsp()
{

}

template<class T, class ALLOC> inline
IVector_Nmsp<T, ALLOC>::~IVector_Nmsp()
{

}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::reserve(SizeType n)
{
	auto oldCap = capacity();
	if (oldCap >= n)
		return;
	_on_reserve(oldCap, size(), n);
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::resize(SizeType n)
{
	_on_resize(n);
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::resize(SizeType n, const T& v)
{
	_on_resize(n, v);
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::clear()
{
	nmsp::destruct(_begin, _end);
	_end = _begin;
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::clear_and_free()
{
	clear();
	_on_free(_begin, capacity());
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::shrink_to_fit()
{
	auto oldSize = size();
	clear_and_free();
	resize(oldSize);
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::reset_to_local()
{
	clear_and_free();
}

template<class T, class ALLOC> inline
T& IVector_Nmsp<T, ALLOC>::push_back()
{
	_append(1, T());
	return back();
}

template<class T, class ALLOC> inline
T& IVector_Nmsp<T, ALLOC>::push_back(const T& v)
{
	_append(1, v);
	return back();
}

template<class T, class ALLOC> inline
T& IVector_Nmsp<T, ALLOC>::push_back(T&& v)
{
	_append(1, move(v));
	return back();
}

template<class T, class ALLOC> 
template<class... ARGS> inline
T& IVector_Nmsp<T, ALLOC>::emplace_back(ARGS&&... args)
{
	_append(1, forward<ARGS>(args)...);
	return back();
}

template<class T, class ALLOC> 
template<class... ARGS> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::emplace(CIter pos, ARGS&&... args)
{
	return _on_insert(pos, 1, forward<ARGS>(args)...);
}

template<class T, class ALLOC> 
template<class... ARGS> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::emplace_range(CIter pos, SizeType n, ARGS&&... args)
{
	return _on_insert(pos, n, forward<ARGS>(args)...);
}
template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::insert(CIter pos, const T& v)
{
	return _on_insert(pos, 1, v);
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::insert(CIter pos, SizeType n, const T& v)
{
	return _on_insert(pos, n, v);
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::insert(CIter pos, CIter otherBeg, CIter otherEnd)
{
	return _on_insert_iters(pos, otherBeg, otherEnd);
}

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::pop_back()
{
	erase(size());
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter
IVector_Nmsp<T, ALLOC>::erase(SizeType i)
{
	_assert_boundary(i);

	Iter target = _begin + i;

	// check is not last element
	if(target + 1 < _end)
		nmsp::move_data(target, target + 1, _end);

	--_end;
	nmsp::destruct(_end);
	return target;
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::erase(CIter pos)
{
	return erase(pos - _begin);
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::erase(CIter beg, CIter end)
{
	Iter beg = const_cast<ValueType*>(beg);        
	Iter end = const_cast<ValueType*>(end);

	_assert_boundary(beg);
	_assert_boundary(end);

	if (beg != end)
	{
#if 1
		auto last = nmsp::move_data(beg, end, _end);
		nmsp::destruct(last, _end);
#else
		// error code, the [_end - n, _end) element will not be free
		nmsp::destruct(beg, end);
		nmsp::move_construct(beg, end, _end);
#endif // 0

		_end -= (end - beg);
	}

	return beg;
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter
IVector_Nmsp<T, ALLOC>::erase_unsorted(SizeType i)
{
	_assert_boundary(i);
	Iter target = _begin + i;

	*target = nmsp::move(*(_end - 1));
		
	--_end;
	nmsp::destruct(_end);

	return target;
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter
IVector_Nmsp<T, ALLOC>::erase_unsorted(CIter pos)
{
	return erase_unsorted(pos - _begin);
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::RevIter
IVector_Nmsp<T, ALLOC>::erase(CRevIter pos)
{
	return erase((pos).base());
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::RevIter
IVector_Nmsp<T, ALLOC>::erase(CRevIter beg, CRevIter end)
{
	return RevIter(erase((--end).base(), (--beg).base()));
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::RevIter 
IVector_Nmsp<T, ALLOC>::erase_unsorted(CRevIter pos)
{
	return RevIter(erase_unsorted((pos).base()));
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter
IVector_Nmsp<T, ALLOC>::erase_first(const T& v)
{
	Iter it = nmsp::find(_begin, _end, v);
	if (it != end())
		return erase(it);
	else
		return it;
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::Iter
IVector_Nmsp<T, ALLOC>::erase_first_unsorted(const T& v)
{
	Iter it = nmsp::find(_begin, _end, v);
	if (it != end())
		return erase_unsorted(it);
	else
		return it;
} 

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::RevIter
IVector_Nmsp<T, ALLOC>::erase_last(const T& v)
{
	RevIter it = nmsp::find(rbegin(), rend(), v);
	if (it != rend())
		return erase(it);
	else
		return it;
}

template<class T, class ALLOC> inline
typename IVector_Nmsp<T, ALLOC>::RevIter
IVector_Nmsp<T, ALLOC>::erase_last_unsorted(const T& v)
{
	RevIter it = nmsp::find(rbegin(), rend(), v);
	if (it != rend())
		return erase_unsorted(it);
	else
		return it;
}

template<class T, class ALLOC> inline		T* IVector_Nmsp<T, ALLOC>::data()							{ return _begin; }
template<class T, class ALLOC> inline const	T* IVector_Nmsp<T, ALLOC>::data() const						{ return _begin; }

template<class T, class ALLOC> inline		T& IVector_Nmsp<T, ALLOC>::operator[](SizeType i)			{ return at(i); }
template<class T, class ALLOC> inline const	T& IVector_Nmsp<T, ALLOC>::operator[](SizeType i) const		{ return at(i); }

template<class T, class ALLOC> inline		T& IVector_Nmsp<T, ALLOC>::front()							{ return *_begin; }	
template<class T, class ALLOC> inline const	T& IVector_Nmsp<T, ALLOC>::front() const					{ return *_begin; }		

template<class T, class ALLOC> inline		T& IVector_Nmsp<T, ALLOC>::back()							{ return *(_end - 1); }
template<class T, class ALLOC> inline const	T& IVector_Nmsp<T, ALLOC>::back() const						{ return *(_end - 1); }

template<class T, class ALLOC> inline		T& IVector_Nmsp<T, ALLOC>::at(SizeType i)					{ _assert_boundary(i); return *(_begin + i);  }
template<class T, class ALLOC> inline const	T& IVector_Nmsp<T, ALLOC>::at(SizeType i) const				{ _assert_boundary(i); return *(_begin + i);  }

template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::Iter			IVector_Nmsp<T, ALLOC>::begin()			{ return _begin; }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CIter		IVector_Nmsp<T, ALLOC>::begin()  const	{ return _begin; }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CIter		IVector_Nmsp<T, ALLOC>::cbegin() const	{ return _begin; }

template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::Iter			IVector_Nmsp<T, ALLOC>::end()			{ return _end; }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CIter		IVector_Nmsp<T, ALLOC>::end()  const	{ return _end; }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CIter		IVector_Nmsp<T, ALLOC>::cend() const	{ return _end; }

template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::RevIter		IVector_Nmsp<T, ALLOC>::rbegin()		{ return RevIter (_end - 1); }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CRevIter		IVector_Nmsp<T, ALLOC>::rbegin()  const	{ return CRevIter(_end - 1); }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CRevIter		IVector_Nmsp<T, ALLOC>::crbegin() const	{ return CRevIter(_end - 1); }

template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::RevIter		IVector_Nmsp<T, ALLOC>::rend()			{ return RevIter (_begin - 1); }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CRevIter		IVector_Nmsp<T, ALLOC>::rend()  const	{ return CRevIter(_begin - 1); }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CRevIter		IVector_Nmsp<T, ALLOC>::crend() const	{ return CRevIter(_begin - 1); }

template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::RevEnumerator	IVector_Nmsp<T, ALLOC>::revEach()		{ return RevEnumerator(rbegin(), rend()); }
template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::CRevEnumerator	IVector_Nmsp<T, ALLOC>::revEach() const	{ return CRevEnumerator(crbegin(), crend()); }

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::_on_reserve(SizeType oldCap, SizeType oldSize, SizeType n)
{
	auto newCap = _get_new_capacity(oldCap, n);
	auto* const pNewData = _on_allocate(newCap); // TODO: try catch or use uptr

	// if not using local buffer
	if (pNewData != _begin)
	{
		_on_move_destruct(pNewData, _begin, _end);
		_on_free(_begin, oldCap);
	}

	_begin  = pNewData;
	_end    = _begin + oldSize;
}

template<class T, class ALLOC> 
template<class... ARGS> inline
void IVector_Nmsp<T, ALLOC>::_on_resize(SizeType n, ARGS&&... args)
{
	auto oldSize = size();
	if (n_ > oldSize)
	{
		_append(n_ - oldSize, forward<ARGS>(args)...);
	}
	else
	{
		nmsp::destruct(_begin + n, _end);
		_end = _begin + n_;
	}

	NMSP_ASSERT(capacity() >= n);
	NMSP_ASSERT(_end <= _last());
	NMSP_ASSERT(size() == n_ && size() <= capacity());
}

template<class T, class ALLOC> 
template<class... ARGS> inline
void IVector_Nmsp<T, ALLOC>::_append(SizeType n, ARGS&&... args)
{
	reserve(size() + n);
	nmsp::construct(_end, _end + n, forward<ARGS>(args)...);
	_end += n;
}

template<class T, class ALLOC> 
template<class... ARGS> inline typename IVector_Nmsp<T, ALLOC>::Iter 
IVector_Nmsp<T, ALLOC>::_on_insert(CIter pos, SizeType n, ARGS&&... args)
{
	NMSP_ASSERT(pos == _begin || pos < _last() && pos >= _begin);
	NMSP_ASSERT(n > 0);

	SizeType index = pos - _begin;

	Iter target = const_cast<ValueType*>(pos);
	auto oldSize = size();

	if (_end + n > _last())
	{
		SizeType oldCap = capacity();
		SizeType newCap = _get_new_capacity(oldCap, oldCap + n);
		auto* pNewData = _on_allocate(newCap);

		// should not using local buffer if we need allocate
		NMSP_ASSERT(pNewData != _begin);

		auto* pNewBeg = pNewData + index;
		auto* pNewEnd = pNewBeg  + n;

		nmsp::move_construct(pNewData, _begin, target);
		nmsp::construct(pNewBeg, pNewEnd, forward<ARGS>(args)...);
		nmsp::move_construct(pNewEnd, target, _end);
		nmsp::destruct(_begin, _end);
		_on_free(_begin, oldCap);

		_begin  = pNewData;
		_end    = _begin + oldSize + n;
	}
	else
	{
		if (!is_empty() && index < oldSize)
		{
			nmsp::construct(_end, _end + n);
			for (auto* p = _end - 1; p >= target; --p)
				*(p + n) = move(*p);

			nmsp::destruct(target, target + n);
		}
		nmsp::construct(target, target + n, forward<ARGS>(args)...);
		_end += n;
	}

	return _begin + index;
}

template<class T, class ALLOC> inline typename IVector_Nmsp<T, ALLOC>::Iter
IVector_Nmsp<T, ALLOC>::_on_insert_iters(CIter pos, CIter beg, CIter end)
{
	NMSP_ASSERT(pos == _begin || pos < _last() && pos >= _begin);
	NMSP_ASSERT(!(end < _last() && beg >= _begin));

	auto n = end - beg;
	NMSP_ASSERT(n > 0);

	Iter target = const_cast<ValueType*>(pos);
	Iter beg	= const_cast<ValueType*>(beg);        
	Iter end	= const_cast<ValueType*>(end);

	SizeType index = target - _begin;
	SizeType oldSize = size();

	if (_end + n > _last())
	{
		auto oldCap		= capacity();
		auto newCap		= _get_new_capacity(oldCap, oldCap + n);
		auto* pNewData	= _on_allocate(newCap);		// TODO: try catch or use uptr

		// should not using local buffer if we need allocate
		NMSP_ASSERT(pNewData != _begin);

		auto* pNewBeg = pNewData + index;
		auto* pNewEnd = pNewBeg  + n;

		nmsp::move_construct(pNewData, _begin, target);
		nmsp::copy_construct(pNewBeg, beg, end);
		nmsp::move_construct(pNewEnd, target, _end);
		nmsp::destruct(_begin, _end);
		_on_free(_begin, oldCap);

		_begin  = pNewData;
		_end    = _begin + oldSize + n;
	}
	else
	{
		if (!is_empty() && index < oldSize)
		{
			nmsp::construct(_end, _end + n);
			for (auto* p = _end - 1; p >= target; --p)
				*(p + n) = move(*p);

			nmsp::destruct(target, target + n);
		}
		nmsp::copy_construct(target, beg, end);
		_end += n;
	}

	return _begin + index;
}

#if NMSP_ENABLE_IVECTOR

template<class T, class ALLOC> inline
T* IVector_Nmsp<T, ALLOC>::_on_allocate(SizeType n)
{
	return Base::_on_allocate(n);
}

#endif // 0

template<class T, class ALLOC> inline
void IVector_Nmsp<T, ALLOC>::_on_move_destruct(Iter dst, Iter srcBeg, Iter srcEnd)
{
	nmsp::move_construct(dst, srcBeg, srcEnd);
	nmsp::destruct(srcBeg, srcEnd);
}

#endif

#if 0
#pragma mark --- Vector_Nmsp-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Nmsp<T, N, FALLBACK_ALLOC>::Vector_Nmsp()
{

}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Nmsp<T, N, FALLBACK_ALLOC>::~Vector_Nmsp()
{
	nmsp::destruct(_begin, _end);

	if (_localAllocator().isUsingLocalBuf(_begin))
	{
		_begin = nullptr;
	}
}

#if NMSP_ENABLE_IVECTOR

template<class T, size_t N, class FALLBACK_ALLOC> inline
T* Vector_Nmsp<T, N, FALLBACK_ALLOC>::_on_allocate(SizeType n)
{
	T* memory = reinCast<T*>(_localAllocator().alloc(_get_bytes(n)));
	if (memory)
	{
		_last() = memory + s_kLocalCount;
		return memory;
	}
	else
	{
		return Base::_on_allocate(n);
	}
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
void Vector_Nmsp<T, N, FALLBACK_ALLOC>::_on_free(T* ptr, SizeType n)
{
	if (ptr && !_localAllocator().isUsingLocalBuf(ptr))
	{
		_allocator().free(ptr, _get_bytes(n));
	}
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Nmsp<T, N, FALLBACK_ALLOC>::LocalAllocator& Vector_Nmsp<T, N, FALLBACK_ALLOC>::_localAllocator()
{
	return *this;
}

#else

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Nmsp<T, N, FALLBACK_ALLOC>::LocalAllocator& Vector_Nmsp<T, N, FALLBACK_ALLOC>::_localAllocator()
{
	return _allocator().first();
}

#endif // 0




#endif





}