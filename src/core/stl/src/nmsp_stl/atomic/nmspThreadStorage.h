#pragma once

#include "../common/nmsp_stl_common.h"

#include "nmsp_stl/container/nmspVector.h"

//#include 

namespace nmsp {

#if 0
#pragma mark --- ThreadDefaultStorage_T-Decl ---
#endif // 0
#if 1

class Logger_T;

class ThreadDefaultStorage_T /*: public NonCopyable*/
{
public:
	ThreadDefaultStorage_T();


public:
	void		setLogger(Logger_T* logger) { _logger = logger; };
	Logger_T*	logger() { return _logger; }


private:
	Logger_T* _logger = nullptr;
};

class AllThreadsDefaultStorage_T : public NonCopyable
{
public:
	using SizeType = size_t;

public:
	AllThreadsDefaultStorage_T(size_t n = StlTraits::logicalThreadCount())
	{
		_threadStorages.resize(n);
	}

	ThreadStorage* operator[](SizeType i) 
	{ 
		return &_threadStorages[i]; 
	}

private:
	Vector_T<ThreadStorage, StlTraits::s_kEstLogicalThreadCount> _threadStorages;
};


#endif
}