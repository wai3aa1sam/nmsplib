#pragma once

/*
references:
- sge_marco.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
- REP in https://stackoverflow.com/questions/8551418/c-preprocessor-macro-for-returning-a-string-repeated-a-certain-number-of-times
*/

#include <assert.h>

#if 0
#pragma mark --- util_marco-Impl ---
#endif // 0
#if 1

#define NMSP_FILE __FILE__
#define NMSP_LINE __LINE__

#define NMSP_COMMA ,
#define NMSP_EMPTY
#define NMSP_ARGS(...) __VA_ARGS__
#define NMSP_STRINGIFY(...)	#__VA_ARGS__

#define NMSP_IDENTITY(X) X
#define NMSP_CALL(M, ARGS) NMSP_IDENTITY( M(ARGS) )

#define NMSP_CONCAT(X, ...)		X ## __VA_ARGS__

#define NMSP_CALL_ARGS(X, ...)	NMSP_IDENTITY( X(__VA_ARGS__) )
#define NMSP_ANGLE_BRACKET(...) NMSP_IDENTITY( <__VA_ARGS__> )
#define NMSP_BRACKET(...)		NMSP_IDENTITY( (__VA_ARGS__) )

#define NMSP_VA_ARGS_COUNT(...) NMSP_IDENTITY( NMSP_VA_ARGS_COUNT_INTERNAL(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1) )
#define NMSP_VA_ARGS_COUNT_INTERNAL(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, COUNT, ...) COUNT

#define NMSP_UNUSED(X)	(void)X

#define NMSP_CONSTEXPR				constexpr
#define NMSP_NOEXCEPT				noexcept
#define NMSP_NOEXCEPT_IF(...)		noexcept(__VA_ARGS__)

#define NMSP_ALIGN_OF(X) alignof(X)
#define NMSP_ALIGN_AS(X) alignas(X)

#define NMSP_S_ASSERT(COND, ...) static_assert(COND, NMSP_FUNC_NAME_SZ ## "() " "--- " #COND ## " --- " ## __VA_ARGS__)


#if NMSP_DEBUG || NMSP_ENABLE_ASSERT
	#define NMSP_CORE_ASSERT(X, ...)	do{ if(!(X)) { ::nmsp::_log(__VA_ARGS__); NMSP_DEBUG_BREAK(); assert(X);  } } while(false)
	#define NMSP_ASSERT(X, ...)			do{ if(!(X)) { ::nmsp::_log(__VA_ARGS__); NMSP_DEBUG_BREAK(); assert(X);  } } while(false)
#else
	#define NMSP_CORE_ASSERT(X, ...)
	#define NMSP_ASSERT(X, ...)	
#endif // NMSP_ENABLE_ASSERT

#if NMSP_DEBUG
	#define NMSP_SRCLOC	SrcLoc(NMSP_FILE, NMSP_LINE, NMSP_FUNC_NAME_SZ)

	#define NMSP_DEBUG_CALL(FUNC) FUNC

	#define NMSP_TODO(FMT, ...) ::nmsp::_todo(NMSP_SRCLOC, FMT, __VA_ARGS__)

#else
	#define NMSP_SRCLOC	SrcLoc()

	#define NMSP_DEBUG_CALL(FUNC) FUNC

	#define NMSP_TODO(FMT, ...) 

#endif

#define NMSP_REP_0(X)
#define NMSP_REP_1(X) X
#define NMSP_REP_2(X)  NMSP_REP_1(X) X
#define NMSP_REP_3(X)  NMSP_REP_2(X) X
#define NMSP_REP_4(X)  NMSP_REP_3(X) X
#define NMSP_REP_5(X)  NMSP_REP_4(X) X
#define NMSP_REP_6(X)  NMSP_REP_5(X) X
#define NMSP_REP_7(X)  NMSP_REP_6(X) X
#define NMSP_REP_8(X)  NMSP_REP_7(X) X
#define NMSP_REP_9(X)  NMSP_REP_8(X) X
#define NMSP_REP_10(X) NMSP_REP_9(X) X
//#define NMSP_REP_N(HUNDREDS,TENS,ONES,X) \
//  NMSP_REP##HUNDREDS(NMSP_REP10(NMSP_REP10(X))) \
//  NMSP_REP##TENS(REP10(X)) \
//  NMSP_REP##ONES(X)

#define NMSP_IDX_SEQ_IMPL(SEP, I, X, ...)	SEP NMSP_IDENTITY(X(I __VA_ARGS__))
#define NMSP_IDX_SEQ_1(SEP, X, ...)		NMSP_IDENTITY(X(0 __VA_ARGS__))
#define NMSP_IDX_SEQ_2(SEP, X, ...)		NMSP_IDX_SEQ_1(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 1, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_3(SEP, X, ...)		NMSP_IDX_SEQ_2(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 2, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_4(SEP, X, ...)		NMSP_IDX_SEQ_3(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 3, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_5(SEP, X, ...)		NMSP_IDX_SEQ_4(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 4, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_6(SEP, X, ...)		NMSP_IDX_SEQ_5(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 5, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_7(SEP, X, ...)		NMSP_IDX_SEQ_6(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 6, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_8(SEP, X, ...)		NMSP_IDX_SEQ_7(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 7, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_9(SEP, X, ...)		NMSP_IDX_SEQ_8(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 8, X, __VA_ARGS__)
#define NMSP_IDX_SEQ_10(SEP, X, ...)	NMSP_IDX_SEQ_9(SEP, X, __VA_ARGS__) NMSP_IDX_SEQ_IMPL(SEP, 9, X, __VA_ARGS__)

#define NMSP_PARAMS_IMPL(I) A ## I
#define NMSP_PARAMS_1		NMSP_IDX_SEQ_1(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_2		NMSP_IDX_SEQ_2(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_3		NMSP_IDX_SEQ_3(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_4		NMSP_IDX_SEQ_4(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_5		NMSP_IDX_SEQ_5(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_6		NMSP_IDX_SEQ_6(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_7		NMSP_IDX_SEQ_7(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_8		NMSP_IDX_SEQ_8(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_9		NMSP_IDX_SEQ_9(NMSP_COMMA, NMSP_PARAMS_IMPL)
#define NMSP_PARAMS_10		NMSP_IDX_SEQ_10(NMSP_COMMA, NMSP_PARAMS_IMPL)


#endif