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


#if 0
#pragma mark --- ScopedAction-Impl ---
#endif // 0
#if 1

template<class FUNC_BEGIN, class FUNC_END>
class ScopedAction : public NonCopyable
{
public:
	ScopedAction(FUNC_BEGIN&& funcBeg, FUNC_END&& funcEnd)
	{
		_end = forward<FUNC_END>(funcEnd);
		funcBeg();
	}
	~ScopedAction()
	{
		_end();
	}
	
private:
	FUNC_END	_end;
};
template<class FUNC_BEGIN, class FUNC_END>
NMSP_NODISCARD ScopedAction<FUNC_BEGIN, FUNC_END> makeScopedAction(FUNC_BEGIN&& funcBeg, FUNC_END&& funcEnd)
{
	return ScopedAction{ funcBeg, funcEnd };
}

template<class FUNC_END>
class LeaveScopeAction : public NonCopyable
{
public:
	using FuncLeaveType = Decay<FUNC_END>;

	LeaveScopeAction(FUNC_END&& funcEnd)
		: _end(funcEnd)
	{
		//static_assert(IsFunction<FuncLeaveType>, "");
	}
	~LeaveScopeAction()
	{
		_end();
	}

private:
	FuncLeaveType _end;
};
template<class FUNC_END>
NMSP_NODISCARD LeaveScopeAction<FUNC_END> makeLeaveScopeAction(FUNC_END&& funcEnd)
{
	return LeaveScopeAction{ forward<FUNC_END>(funcEnd) };
}

#endif

#if 0
#pragma mark --- _Internal_Timer-Impl ---
#endif // 0
#if 1

class _Internal_Timer
{

};

class _Internal_ScopedTimer
{

};

#endif // 1

#endif



}