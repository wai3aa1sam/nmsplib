#pragma once

#include "../nmspPointer_Common.h"

namespace nmsp {

#if 0
#pragma mark --- UPtr_Nmsp-Impl ---
#endif // 0
#if 1

template<class T>
struct UPtr_Deleter
{
	void operator() (T* p)
	{
		if (p)
		{
			NMSP_DELETE(p);
		}
	}
};

template<class T, class DELETER = UPtr_Deleter<T> >
class UPtr_Nmsp : public DELETER/*, NonCopyable */
{
public:
	UPtr_Nmsp() = default;

	UPtr_Nmsp(T* p)					NMSP_NOEXCEPT	{ reset(p); }
	//UPtr_Nmsp(UPtr_Nmsp && r)		NMSP_NOEXCEPT	{ _p = r._p; r._p = nullptr; }
	UPtr_Nmsp(const UPtr_Nmsp& r)	NMSP_NOEXCEPT	{ reset(r._p); }

	void operator=(T* p)			NMSP_NOEXCEPT	{ reset(p); }
	//void operator=(UPtr_Nmsp &  r)	NMSP_NOEXCEPT	{ reset(r.ptr()); }
	void operator=(UPtr_Nmsp && r)	NMSP_NOEXCEPT	{ reset(nullptr); _p = r._p; r._p = nullptr; }

	~UPtr_Nmsp() NMSP_NOEXCEPT { reset(nullptr); }

		  T* operator->()		NMSP_NOEXCEPT	{ return _p; }
	const T* operator->() const NMSP_NOEXCEPT	{ return _p; }

	operator       T*()       NMSP_NOEXCEPT		{ return _p; }
	operator const T*() const NMSP_NOEXCEPT		{ return _p; }

			T* ptr()       NMSP_NOEXCEPT		{ return _p; }
	const	T* ptr() const NMSP_NOEXCEPT		{ return _p; }

	void reset(T* p) NMSP_NOEXCEPT 
	{
		if (_p == p) 
			return;

		DELETER::operator()(_p);
		_p = nmsp::move(p);
	}

	T* release() NMSP_NOEXCEPT { T* o = _p; _p = nullptr; return o; }

	UPtr_Nmsp(const NonCopyable&)		= delete;
	void operator=(const NonCopyable&)	= delete;
private:
	T* _p = nullptr;
};

#endif


}