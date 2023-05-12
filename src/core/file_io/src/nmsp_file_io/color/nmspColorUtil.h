#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmspColor.h"

/*
references:
- src/core/graph/ColorUtil.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- ColorUtil-Decl ---
#endif // 0
#if 1

struct ColorUtil
{

	static int getElementCount(ColorType v);
	static int getElementCount(ColorModel v);

	static int pixelByteSize(ColorType v);

};

#endif


#if 0
#pragma mark --- ColorUtil-Decl ---
#endif // 0
#if 1

inline 
int ColorUtil::getElementCount(ColorType v)
{
	auto type = TBM<ColorType>::getElementValue<0>(v);
	return getElementCount(type);
}

inline 
int ColorUtil::getElementCount(ColorModel v)
{
	using EM = ColorModel;
	switch (v)
	{
		case EM::None:				{ return 0; } break;
		case EM::R:					{ return 1; } break;
		case EM::RG:				{ return 2; } break;
		case EM::RGB:				{ return 3; } break;
		case EM::RGBA:				{ return 4; } break;
		case EM::L:					{ return 1; } break;
		case EM::LA:				{ return 2; } break;
		//case EM::HSV:				{ return 1; } break;
		//case EM::BlockCompression:	{ return 1; } break;
	}
	NMSP_ASSERT(false, "not supported ColorModel");
	return 0;
}

inline 
int ColorUtil::pixelByteSize(ColorType v)
{
	using EM = ColorType;
	switch (v)
	{
		#define E(TYPE) case EM::TYPE:				{ return sizeof(Color ## TYPE ## _T); } break
		E(Rb);
		E(Rs);
		E(Rf);
		E(RGb);
		E(RGs);
		E(RGf);
		E(RGBb);
		E(RGBs);
		E(RGBf);
		E(RGBAb);
		E(RGBAs);
		E(RGBAf);
		//case EM::HSV:				{ return 1; } break;
		//case EM::BlockCompression:	{ return 1; } break;
	}
	NMSP_ASSERT(false, "not supported ColorType");
	return 0;
}


#endif	
}