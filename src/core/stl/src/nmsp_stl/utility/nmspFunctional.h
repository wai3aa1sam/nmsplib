#pragma once

#include "../common/nmsp_stl_common.h"

#include "EASTL/functional.h"

namespace nmsp {

template<class T> struct Less		: public eastl::less<T>		{};
template<class T> struct EqualTo	: public eastl::equal_to<T>	{};
template<class T> struct StrLess	: public eastl::str_less<T>	{};

template<class T> struct Hash		: public eastl::hash<T>		{};



}