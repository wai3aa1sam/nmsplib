#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp {

#if 0
#pragma mark --- Job_T-Decl ---
#endif // 0
#if 1

template<class T, size_t ALIGN>
struct Padding_Helper
{
	static constexpr size_t s_kValue = _alignTo(sizeof(T), ALIGN) - sizeof(T);
	static constexpr bool   s_shouldPad = s_kValue > 0;
};

template<class T, size_t ALIGN, class ENABLE = void>
struct PaddedData_T : public T
{

private:
	u8 _padding[Padding_Helper<T, ALIGN>::s_kValue];
};

template<class T, size_t ALIGN>
struct PaddedData_T<T, ALIGN, EnableIf<!Padding_Helper<T, ALIGN>::s_shouldPad> > : public T
{

};


#endif
}