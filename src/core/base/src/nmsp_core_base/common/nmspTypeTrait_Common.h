#pragma once

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"
#include <type_traits>

/*
references:
- <type_traits>
*/

namespace nmsp {

#if 0
#pragma mark --- nmspTypeTrait-Impl ---
#endif // 0
#if 1

#if 0
#pragma mark --- nmspTypeTrait_Util-Impl ---
#endif // 0
#if 1

template<bool COND> using EnableIfT = typename std::enable_if<COND>;
template<bool COND> using EnableIf  = typename EnableIfT<COND>::type;

template<bool COND, class IF_TRUE_T, class IF_FASLE_T> using ConditionalT   = typename std::conditional<COND, IF_TRUE_T, IF_FASLE_T>;
template<bool COND, class IF_TRUE_T, class IF_FASLE_T> using Conditional    = typename ConditionalT<COND, IF_TRUE_T, IF_FASLE_T>::type;

#endif

#if 0
#pragma mark --- nmspTypeTrait_Remove-Impl ---
#endif // 0
#if 1

template<class T> using DecayT = typename std::decay<T>;
template<class T> using Decay  = typename DecayT<T>::type;

template<class T> using RemoveRefT  = typename std::remove_reference<T>;
template<class T> using RemoveRef   = typename RemoveRefT<T>::type;

#endif

#if 0
#pragma mark --- nmspTypeTrait_IsType-Impl ---
#endif // 0
#if 1

template<class T> using                 IsEmptyT    = std::is_empty<T>;
template<class T> inline constexpr bool IsEmpty     = IsEmptyT<T>::value;

template<class T1, class T2> using					IsSameT = std::is_same<T1, T2>;
template<class T1, class T2> inline constexpr bool	IsSame  = IsSameT<T1, T2>::value;

template<class T> using                 IsLVRefT    = std::is_lvalue_reference<T>;
template<class T> inline constexpr bool IsLVRef     = IsLVRefT<T>::value;

template<class T> using                 IsTrivialT  = std::is_trivial<T>;
template<class T> inline constexpr bool IsTrivial   = IsTrivialT<T>::value;

template<class BASE, class DERIVED> using				  IsBaseOfT = typename std::is_base_of<BASE, DERIVED>;
template<class BASE, class DERIVED> inline constexpr bool IsBaseOf  = IsBaseOfT<BASE, DERIVED>::value;

template<class T> using					IsFunction_T    = std::is_function<T>;
template<class T> inline constexpr bool	IsFunction      = IsFunction_T<T>::value;

template<class T> using					IsUnsigned_T    = std::is_unsigned<T>;
template<class T> inline constexpr bool	IsUnsigned      = IsUnsigned_T<T>::value;



#endif

#if 0
#pragma mark --- nmspTypeTrait_Value-Impl ---
#endif // 0
#if 1

template<class... ARGS> using VoidType = void;

using TrueType = std::true_type;
using FalseType = std::false_type;

template<class T, T VALUE> using					IntConstant_T   = typename std::integral_constant<T, VALUE>;
template<class T, T VALUE> inline constexpr bool	IntConstant     = std::integral_constant<T, VALUE>::value;


#endif


template<class T>
NMSP_NODISCARD constexpr T&& forward(RemoveRef<T>& arg_) noexcept
{ // forward an lvalue as either an lvalue or an rvalue
    return static_cast<T&&>(arg_);
}

template<class T>
NMSP_NODISCARD constexpr T&& forward(RemoveRef<T>&& arg_) noexcept
{ // forward an rvalue as an rvalue
    static_assert(!IsLVRef<T>, "bad forward call");
    return static_cast<T&&>(arg_);
}

template<class T>
NMSP_NODISCARD constexpr RemoveRef<T>&& move(T&& arg_) noexcept
{ // forward _Arg as movable
    return static_cast<RemoveRef<T>&&>(arg_);
}


#endif // 1
}