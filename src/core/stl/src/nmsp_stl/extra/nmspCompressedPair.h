#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

namespace nmsp {

#if 0
//template<class T1, class T2> using CompressedPair = std::pair<T1, T2>;
// temp class
template<class T1, class T2>
class CompressedPair : public std::pair<T1, T2>
{
public:
	using Base = std::pair<T1, T2>;

public:
	template<class... ARGS>
	CompressedPair(ARGS&&... args)
		: Base(forward<ARGS>(args)...)
	{}

	CompressedPair() = default;
	~CompressedPair() = default;

	T1& first() { return Base::first; }
	T2& second() { return Base::second; }
	const	T1& first() const { return Base::first; }
	const	T2& second() const { return Base::second; }

};

#else

template<class T1, class T2>
class CompressedPair_T : public eastl::compressed_pair<T1, T2>
{
	using Base = eastl::compressed_pair<T1, T2>;
public:
	template<class... ARGS>
	CompressedPair_T(ARGS&&... args)
		: Base(forward<ARGS>(args)...)
	{}

	~CompressedPair_T() = default;
};

#endif // 0


}