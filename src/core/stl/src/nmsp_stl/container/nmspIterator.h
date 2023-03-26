#pragma once
#include "../common/nmsp_stl_common.h"

namespace nmsp {

template <typename ITER>
struct Iter_Traits
{
	using ValueType = typename ITER::ValueType;
};

template <typename T>
struct Iter_Traits<T*>
{
	using ValueType = T;
};

template <typename T>
struct Iter_Traits<const T*>
{
	using ValueType = T;
};

template<typename T>
class Iter_T
{
public:
	using ValueType = T;

	Iter_T(T* ptr_)
		: _ptr(ptr_)
	{}

	ValueType& operator*()		{ return *_ptr; }
	operator ValueType*()		{ return _ptr; }

	constexpr Iter_T& operator++()		{ ++_ptr; return *this; }
	constexpr Iter_T  operator++(int)	{ Iter_T it(*this); ++_ptr; return it; }
	constexpr Iter_T& operator--()		{ --_ptr; return *this; }
	constexpr Iter_T  operator--(int)	{ Iter_T it(*this); --_ptr; return it; }

private:
	T* _ptr = nullptr;
};

template<typename ITER>
class RevIter_T
{
public:
	using Iter = ITER;
	using ValueType = typename Iter_Traits<Iter>::ValueType;
	using SizeType = size_t;

	//constexpr RevIter_T() : _it() {}

	constexpr RevIter_T(Iter it_)
		: _it(it_)
	{}

	constexpr RevIter_T(const RevIter_T& rit_) : _it(rit_._it) {}

	template<class U>
	constexpr RevIter_T(const RevIter_T<U>& rit_) : _it(rit_.base()) {}

	constexpr const ValueType& operator*() const	{ return *_it; }
	constexpr const ValueType* operator->() const	{ return &(operator*()); }

	constexpr explicit operator bool() { return this->base(); }
	//constexpr operator Iter()	{ return _it; }

	constexpr Iter base() const	{ return _it; }

	constexpr RevIter_T& operator++()					{ --_it; return *this; }
	constexpr RevIter_T  operator++(int)				{ RevIter_T rit(*this); --_it; return rit; }
	constexpr RevIter_T& operator--()					{ ++_it; return *this; }
	constexpr RevIter_T  operator--(int)				{ RevIter_T rit(*this); ++_it; return rit; }

	constexpr RevIter_T  operator+(SizeType n)  const	{ return RevIter_T(_it - n); }
	constexpr RevIter_T& operator+=(SizeType n)			{ _it -= n;  return *this; }
	constexpr RevIter_T  operator-(SizeType n)  const	{ return RevIter_T(_it + n); }
	constexpr RevIter_T& operator-=(SizeType n)			{ _it += n;  return *this; }

protected:
	Iter _it = {};
};

template<class REVITER>
class RevEnumerator_T
{
public:
	using RevIter = REVITER;
	using ValueType = typename Iter_Traits<RevIter>::ValueType;

	RevEnumerator_T(RevIter beg, RevIter end)
		: _begin(beg), _end(end)
	{}

	RevIter begin() { return _begin; }
	RevIter end()	{ return _end; }

private:
	RevIter _begin;
	RevIter _end;
};

template<class Iter1, class Iter2> constexpr inline bool operator==(const RevIter_T<Iter1>& lhs_, const RevIter_T<Iter2>& rhs_) { return lhs_.base() == rhs_.base(); }
template<class Iter1, class Iter2> constexpr inline bool operator!=(const RevIter_T<Iter1>& lhs_, const RevIter_T<Iter2>& rhs_) { return lhs_.base() != rhs_.base(); }
template<class Iter1, class Iter2> constexpr inline bool operator> (const RevIter_T<Iter1>& lhs_, const RevIter_T<Iter2>& rhs_) { return lhs_.base() >  rhs_.base(); }
template<class Iter1, class Iter2> constexpr inline bool operator>=(const RevIter_T<Iter1>& lhs_, const RevIter_T<Iter2>& rhs_) { return lhs_.base() >= rhs_.base(); }
template<class Iter1, class Iter2> constexpr inline bool operator< (const RevIter_T<Iter1>& lhs_, const RevIter_T<Iter2>& rhs_) { return lhs_.base() <  rhs_.base(); }
template<class Iter1, class Iter2> constexpr inline bool operator<=(const RevIter_T<Iter1>& lhs_, const RevIter_T<Iter2>& rhs_) { return lhs_.base() <= rhs_.base(); }


}