#pragma once

/*
references:
- sge_marco.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if 0
#pragma mark --- util_marco-Impl ---
#endif // 0
#if 1

#define NMSP_COMMA ,
#define NMSP_EMPTY
#define NMSP_ARGS(...) __VA_ARGS__
#define NMSP_STRINGIFY(...)	#__VA_ARGS__

#define NMSP_IDENTITY(x) x
#define NMSP_CALL(M, ARGS) NMSP_IDENTITY( M(ARGS) )

#define NMSP_VA_ARGS_COUNT(...) NMSP_IDENTITY( NMSP_VA_ARGS_COUNT_INTERNAL(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1) )
#define NMSP_VA_ARGS_COUNT_INTERNAL(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, COUNT, ...) COUNT

#define NMSP_NOEXCEPT				noexcept
#define NMSP_NOEXCEPT_IF(...)		noexcept(__VA_ARGS__)

#if NMSP_ENABLE_ASSERT
	#define NMSP_CORE_ASSERT(x, ...)	do{ if(!(x)) { NMSP_DEBUG_BREAK(); assert(x);  } } while(false)
	#define NMSP_ASSERT(x, ...)			do{ if(!(x)) { NMSP_DEBUG_BREAK(); assert(x);  } } while(false)
#else
	#define NMSP_CORE_ASSERT(x, ...)
	#define NMSP_ASSERT(x, ...)	
#endif // NMSP_ENABLE_ASSERT

#define NMSP_ALIGN_OF(x) alignof(x)
#define NMSP_ALIGN_AS(x) alignas(x)

#if NMSP_DEBUG
#define NMSP_SRCLOC	SrcLoc(__FILE__, __LINE__, NMSP_FUNC_NAME_SZ)
#else
#define NMSP_SRCLOC	SrcLoc()
#endif


#endif