#pragma once

#include "nmsp_core_base/common/nmspClass_Common.h"


namespace nmsp {

#if 0
#pragma mark --- AllocStats_Base-Decl ---
#endif // 0
#if 1

struct AllocStats_Base
{
public:
	AllocStats_Base()	= default;
	~AllocStats_Base()	= default;

	AllocStats_Base(const SrcLoc& srcloc);

	void setTime(double t);

	const SrcLoc& srcloc() const;
	double time() const;


private:
	SrcLoc _srcloc;
	double _time;
};


#endif

#if 0
#pragma mark --- AllocStats_Base-Impl ---
#endif // 0
#if 1

inline
AllocStats_Base::AllocStats_Base(const SrcLoc& srcloc)
	: _srcloc(srcloc)
{}

inline void 
AllocStats_Base::setTime(double t)
{
	_time = t;
}

inline const SrcLoc&
AllocStats_Base::srcloc() const
{
	return _srcloc;
}

inline double 
AllocStats_Base::time() const
{
	return _time;
}

#endif

}

