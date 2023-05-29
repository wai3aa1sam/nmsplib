#pragma once

#include "../nmspPointer_Common.h"

/*
references:
- SPtr.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- SPtr_Nmsp-Impl ---
#endif // 0
#if 1

template<class T>
class SPtr_Nmsp : public NonCopyable {
public:
	SPtr_Nmsp() = default;

	SPtr_Nmsp(T* p)					NMSP_NOEXCEPT	{ reset(p); }
	SPtr_Nmsp(SPtr_Nmsp && r)		NMSP_NOEXCEPT	{ _p = r._p; r._p = nullptr; }
	SPtr_Nmsp(const SPtr_Nmsp& r)	NMSP_NOEXCEPT	{ reset(r._p); }

	void operator=(T* p)			NMSP_NOEXCEPT	{ reset(p); }
	void operator=(SPtr_Nmsp &  r)	NMSP_NOEXCEPT	{ reset(r.ptr()); }
	void operator=(SPtr_Nmsp && r)	NMSP_NOEXCEPT	{ reset(nullptr); _p = r._p; r._p = nullptr; }

	~SPtr_Nmsp() NMSP_NOEXCEPT { reset(nullptr); }

		  T* operator->()       NMSP_NOEXCEPT	{ return _p; }
	const T* operator->() const NMSP_NOEXCEPT	{ return _p; }

	operator       T*()       NMSP_NOEXCEPT		{ return _p; }
	operator const T*() const NMSP_NOEXCEPT		{ return _p; }

			T* ptr()       NMSP_NOEXCEPT		{ return _p; }
	const	T* ptr() const NMSP_NOEXCEPT		{ return _p; }

	void reset(T* p) NMSP_NOEXCEPT {
		static_assert(std::is_base_of<RefCount_Base, T>::value, "class T is not base on class RefCount_Base");
		if (p == _p) 
			return;
		if (_p) 
		{
			auto c = --_p->_refCount;
			if (c <= 0)
			{
				NMSP_DELETE(_p);
			}
		}
		_p = p;
		if (_p) 
		{
			++_p->_refCount;
		}
	}

	T* release() NMSP_NOEXCEPT { T* o = _p; _p = nullptr; return o; }
private:
	T* _p = nullptr;
};

#endif


}