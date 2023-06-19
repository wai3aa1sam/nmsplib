#pragma once

#include "../nmspPointer_Common.h"

namespace nmsp {

#if 0
#pragma mark --- UPtr_Nmsp-Impl ---
#endif // 0
#if 1

template<class T, class DELETER = DefaultDeleter<T> >
class UPtr_Nmsp : public DELETER/*, NonCopyable */
{
	template <class, class> friend class UPtr_Nmsp;
public:
	UPtr_Nmsp() = default;

	UPtr_Nmsp(T* p)																	NMSP_NOEXCEPT { reset(p); }
	UPtr_Nmsp(const UPtr_Nmsp&) = delete;
	template<class T2, class DELETER2> UPtr_Nmsp(UPtr_Nmsp<T2, DELETER2>&& r)		NMSP_NOEXCEPT { reset(nullptr); _p = r._p; r._p = nullptr;  }

	void operator=(T* p)															NMSP_NOEXCEPT { reset(p); }
	void operator=(const UPtr_Nmsp&) = delete;
	template<class T2, class DELETER2> void operator=(UPtr_Nmsp<T2, DELETER2>&& r)	NMSP_NOEXCEPT { reset(nullptr); _p = r._p; r._p = nullptr; }

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

private:
	T* _p = nullptr;
};

template<class T, class DELETER>
class UPtr_Nmsp<T[], DELETER> : public DELETER/*, NonCopyable */
{
	UPtr_Nmsp()
	{
		NMSP_S_ASSERT(false);
	}
};

#endif


}