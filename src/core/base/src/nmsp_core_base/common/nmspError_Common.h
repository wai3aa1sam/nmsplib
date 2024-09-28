#pragma once

#include <exception>

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"
#include "nmspClass_Common.h"

#define NMSP_ERROR(...) nmsp::Error_T(NMSP_SRCLOC, nmsp::fmtAs_T<nmsp::TempStringA_T<> >(__VA_ARGS__).c_str())
#define NMSP_THROW(...) throw NMSP_ERROR(__VA_ARGS__)

namespace nmsp {

#if 0
#pragma mark --- Error_Base-Impl ---
#endif // 0
#if 1

class Error_Base : public std::exception
{
public:
	Error_Base(const SrcLoc& srcLoc);

private:
	SrcLoc _srcLoc;
};

#endif


#if 0
#pragma mark --- Error_T-Decl ---
#endif // 0
#if 1

class Error_T : public Error_Base
{
public:
	using Base = Error_Base;

public:
	Error_T(const SrcLoc& loc, const char* msg);

private:

};

#endif

template<class... ARGS> inline 
void 
throwIf(bool cond, const char* fmt, ARGS&&... args)
{
	if (cond)
	{
		throwError(fmt, nmsp::forward<ARGS>(args)...);
	}
}

template<class... ARGS> inline 
void 
throwError(const char* fmt, ARGS&&... args)
{
	throw NMSP_ERROR(fmt, nmsp::forward<ARGS>(args)...);
}

}