#pragma once

#include "nmspDataType_Common.h"

namespace nmsp {

#if 0
#pragma mark --- nmspClass-Impl ---
#endif // 0
#if 1

#if 0
#pragma mark --- NonCopyable-Impl ---
#endif // 0
#if 1

class NonCopyable
{
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	void operator=(const NonCopyable&) = delete;
};

#endif

#if 0
#pragma mark --- SrcLoc-Impl ---
#endif // 0
#if 1

class SrcLoc
{
public:
	SrcLoc() = default;
	SrcLoc(const char* file_, u32 line_, const char* func_)
		: line(line_), file(file_), func(func_)
	{
	}

public:
	u32			line = 0;
	const char* file = nullptr;
	const char* func = nullptr;
};

#endif

#if 0
#pragma mark --- RefCount_Base-Impl ---
#endif // 0
#if 1

class RefCount_Base : public NonCopyable
{
public:
	std::atomic_int	_refCount = 0;
public:
	RefCount_Base()		= default;
	~RefCount_Base()	= default;
};

#endif


#endif



}