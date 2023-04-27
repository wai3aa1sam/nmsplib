#include "nmsp_stl-pch.h"

#include "nmspStringView.h"

#include "nmsp_stl/string/nmspUtfUtil.h"

namespace nmsp {

void onFormat(fmt::format_context& ctx, const StrViewA_T& v)
{
	auto it = *ctx.out();
	for (const auto& c : v) {
		it = c;
		it++;
	}
}


void onFormat(fmt::format_context& ctx, const StrViewW_T& v)
{
	TempStringA_T<> tmp = nmsp::UtfUtil::toString(v);
	formatTo(ctx, "{}", tmp);
}


}