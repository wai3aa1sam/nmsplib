#pragma once

#include <exception>

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"
#include "nmspClass_Common.h"

#define NMSP_ERROR(...) nmsp::Error(NMSP_SRCLOC, nmsp::fmtAs_T<nmsp::TempStringA_T<> >(__VA_ARGS__).c_str())
#define NMSP_THROW(...) throw NMSP_ERROR(__VA_ARGS__)

namespace nmsp {

#if 0
#pragma mark --- ErrorBase-Impl ---
#endif // 0
#if 1

class ErrorBase : public std::exception
{
public:
	ErrorBase(const SrcLoc& srcLoc);

private:
	SrcLoc _srcLoc;
};

#endif


#if 0
#pragma mark --- Error-Decl ---
#endif // 0
#if 1

class Error : public ErrorBase
{
public:
	using Base = ErrorBase;

public:
	Error(const SrcLoc& loc, const char* msg);

private:

};

#endif

template<class... ARGS>
inline void throwIf(bool cond, const char* fmt, ARGS&&... args)
{
	if (cond)
	{
		throw NMSP_ERROR(fmt, nmsp::forward<ARGS>(args)...);
	}
}

}