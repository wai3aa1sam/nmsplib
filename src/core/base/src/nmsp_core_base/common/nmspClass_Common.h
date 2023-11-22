#pragma once

#include "nmsp_core_base_traits.h"
#include "nmspDataType_Common.h"
#include "nmspTypeTraits_Common.h"

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
	const char* file = "";
	const char* func = "";
};

template<> inline
void onFormat(fmt::format_context& ctx, const SrcLoc& v)
{
	formatTo(ctx, "SrcLoc({}:{}: {})", v.file, v.line, v.func);
}

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

template<class BEGIN_FUNC, class END_FUNC>
class ScopedAction : public NonCopyable
{
public:
	using BeginFuncType = Decay<BEGIN_FUNC>;
	using EndFuncType	= Decay<END_FUNC>;

public:
	ScopedAction(BEGIN_FUNC&& funcBeg, END_FUNC&& funcEnd)
		: _end(forward<EndFuncType>(funcEnd))
	{
		funcBeg();
	}
	~ScopedAction()
	{
		_end();
	}

private:
	EndFuncType	_end;
};

template<class BEGIN_FUNC, class END_FUNC>
NMSP_NODISCARD auto makeScopedAction(BEGIN_FUNC&& funcBeg, END_FUNC&& funcEnd)
{
	return ScopedAction { nmsp::forward<BEGIN_FUNC>(funcBeg), nmsp::forward<END_FUNC>(funcEnd) };
}

template<class END_FUNC>
class LeaveScopeAction : public NonCopyable
{
public:
	using FuncLeaveType = Decay<END_FUNC>;

public:
	LeaveScopeAction(END_FUNC&& funcEnd)
		: _end(forward<FuncLeaveType>(funcEnd))
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

template<class END_FUNC>
NMSP_NODISCARD LeaveScopeAction<END_FUNC> makeLeaveScopeAction(END_FUNC&& funcEnd)
{
	return LeaveScopeAction { nmsp::forward<END_FUNC>(funcEnd) };
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

#if 0
#pragma mark --- TypeIdGenerator-Impl ---
#endif // 0
#if 1

class TypeIdGenerator
{
public:
	using IdType = CoreBaseTraits::SizeType;

public:
	template<class U>
	static IdType getId()
	{
		static const IdType idCounter = m_count++;
		return idCounter;
	}
private:
	static IdType _count;
};

#endif // 1



#endif

}

NMSP_FORMATTER( SrcLoc );
