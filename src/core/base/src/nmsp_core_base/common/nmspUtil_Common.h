#pragma once

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"
#include "nmspInclude_Common.h"
#include "nmspClass_Common.h"

#define NMSP_NOT_YET_SUPPORT() _notYetSupported(NMSP_SRCLOC)

#define _NMSP_LOG(...) do{ ::nmsp::_log(__VA_ARGS__); } while(false)

#define _NMSP_DUMP_VAR_1(v0)				do{ _NMSP_LOG("DUMP_VAR: {}=[{}]",								#v0, (v0)); } while(false)
#define _NMSP_DUMP_VAR_2(v0, v1)			do{ _NMSP_LOG("DUMP_VAR: {}=[{}], {}=[{}]",						#v0, (v0), #v1, (v1)); } while(false)
#define _NMSP_DUMP_VAR_3(v0, v1, v2)		do{ _NMSP_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}]",			#v0, (v0), #v1, (v1), #v2, (v2)); } while(false)
#define _NMSP_DUMP_VAR_4(v0, v1, v2, v3)	do{ _NMSP_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}]",	#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3)); } while(false)

#define _NMSP_DUMP_VAR_SELECT(COUNT) _NMSP_DUMP_VAR_##COUNT
#define _NMSP_DUMP_VAR(...) NMSP_IDENTITY(NMSP_CALL(_NMSP_DUMP_VAR_SELECT, NMSP_VA_ARGS_COUNT(__VA_ARGS__) (__VA_ARGS__)))


namespace nmsp 
{

#if 0
#pragma mark --- nmspUtil_Common-Impl ---
#endif // 0
#if 1


#if 0
#pragma mark --- nmspInternalLog-Impl ---
#endif // 0
#if 1

inline void _log()
{

}

template<class... ARGS> inline
void _log(const char* format, ARGS&&... args)
{
	std::cout << fmtAs_T<std::string>(format, nmsp::forward<ARGS>(args)...) << "\n"/* << std::flush*/;
}

inline
void 
_flushLog()
{
	std::cout << std::flush;
}

#endif

inline 
void 
_notYetSupported(const SrcLoc& srcLoc)
{
	NMSP_ASSERT(false, "{}:({}) is not yet supported", srcLoc.func, srcLoc.line);
}

template<class... ARGS> inline 
std::string 
_todo(const SrcLoc& srcLoc, const char* fmt, ARGS&&... args)
{
	std::string out;
	std::string temp;

	fmtTo(temp, fmt, nmsp::forward<ARGS>(args)...);
	fmtTo(out, "// TODO: {{ {} }} - {}", srcLoc.func, temp);
	return out;
}



#endif

}