#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"
#include "nmsp_file_io/serializer/json/nmspJsonUtil.h"

#include <nmsp_stl/extra/nmspTypeBitMixture.h>

/*
references:
- src/core/graph/Color.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- ColorModel-Impl ---
#endif // 0
#if 1

#define ColorModel_ENUM_LIST(E) \
	E(None, = 0) \
	E(R,) \
	E(RG,) \
	E(RGB,) \
	E(RGBA,) \
	E(L,)  /* Luminance */ \
	E(LA,) /* Luminance Alpha */ \
	E(HSV,) \
	E(BlockCompression,) \
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(ColorModel, u8);

#endif

#if 0
#pragma mark --- ColorElementType-Impl ---
#endif // 0
#if 1

#define ColorElementType_ENUM_LIST(E) \
	E(None, = 0) \
	E(UNorm8,) \
	E(UNorm16,) \
	E(Float16,) \
	E(Float32,) \
	E(Float64,) \
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(ColorElementType, u8);

template<class T> inline constexpr ColorElementType getColorElementType();
template<> constexpr ColorElementType getColorElementType<void>()	{ return ColorElementType::None; }
template<> constexpr ColorElementType getColorElementType<u8 >()	{ return ColorElementType::UNorm8; }
template<> constexpr ColorElementType getColorElementType<u16>()	{ return ColorElementType::UNorm16; }
//template<> constexpr ColorElementType getColorElementType<f16>()	{ return ColorElementType::Float16; }
template<> constexpr ColorElementType getColorElementType<f32>()	{ return ColorElementType::Float32; }
template<> constexpr ColorElementType getColorElementType<f64>()	{ return ColorElementType::Float64; }

#define ColorCompressType_ENUM_LIST(E) \
	E(None, = 0) \
	E(BC1,) \
	E(BC2,) \
	E(BC3,) \
	E(BC4,) \
	E(BC5,) \
	E(BC6h,) \
	E(BC7,) \
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(ColorCompressType, u8);

#endif

#if 0
#pragma mark --- ColorType-Impl ---
#endif // 0
#if 1

enum class ColorType : u16;

template<>
struct TypeBitMixture_Impl<ColorType>
{
	using Types								= Tuple_T<ColorModel, ColorElementType, ColorCompressType>;
	static constexpr size_t s_kBitCounts[]	=		 {		   8,				 4,					4,};
};

#define ColorType_ENUM_LIST(E) \
	E(None, = 0) \
	E(Rb,		= TBM<ColorType>::makeInt(ColorModel::R,	ColorElementType::UNorm8 , ColorCompressType::None)) \
	E(Rs,		= TBM<ColorType>::makeInt(ColorModel::R,	ColorElementType::UNorm16, ColorCompressType::None)) \
	E(Rh,		= TBM<ColorType>::makeInt(ColorModel::R,	ColorElementType::Float16, ColorCompressType::None)) \
	E(Rf,		= TBM<ColorType>::makeInt(ColorModel::R,	ColorElementType::Float32, ColorCompressType::None)) \
	\
	E(RGb,		= TBM<ColorType>::makeInt(ColorModel::RG,	ColorElementType::UNorm8 , ColorCompressType::None)) \
	E(RGs,		= TBM<ColorType>::makeInt(ColorModel::RG,	ColorElementType::UNorm16, ColorCompressType::None)) \
	E(RGh,		= TBM<ColorType>::makeInt(ColorModel::RG,	ColorElementType::Float16, ColorCompressType::None)) \
	E(RGf,		= TBM<ColorType>::makeInt(ColorModel::RG,	ColorElementType::Float32, ColorCompressType::None)) \
	\
	E(RGBb,		= TBM<ColorType>::makeInt(ColorModel::RGB,	ColorElementType::UNorm8 , ColorCompressType::None)) \
	E(RGBs,		= TBM<ColorType>::makeInt(ColorModel::RGB,	ColorElementType::UNorm16, ColorCompressType::None)) \
	E(RGBh,		= TBM<ColorType>::makeInt(ColorModel::RGB,	ColorElementType::Float16, ColorCompressType::None)) \
	E(RGBf,		= TBM<ColorType>::makeInt(ColorModel::RGB,	ColorElementType::Float32, ColorCompressType::None)) \
	\
	E(RGBAb,	= TBM<ColorType>::makeInt(ColorModel::RGBA,	ColorElementType::UNorm8 , ColorCompressType::None)) \
	E(RGBAs,	= TBM<ColorType>::makeInt(ColorModel::RGBA,	ColorElementType::UNorm16, ColorCompressType::None)) \
	E(RGBAh,	= TBM<ColorType>::makeInt(ColorModel::RGBA,	ColorElementType::Float16, ColorCompressType::None)) \
	E(RGBAf,	= TBM<ColorType>::makeInt(ColorModel::RGBA,	ColorElementType::Float32, ColorCompressType::None)) \
	\
	E(Lb,		= TBM<ColorType>::makeInt(ColorModel::L,	ColorElementType::UNorm8 , ColorCompressType::None)) \
	E(Ls,		= TBM<ColorType>::makeInt(ColorModel::L,	ColorElementType::UNorm16, ColorCompressType::None)) \
	E(Lh,		= TBM<ColorType>::makeInt(ColorModel::L,	ColorElementType::Float16, ColorCompressType::None)) \
	E(Lf,		= TBM<ColorType>::makeInt(ColorModel::L,	ColorElementType::Float32, ColorCompressType::None)) \
	\
	E(LAb,		= TBM<ColorType>::makeInt(ColorModel::LA,	ColorElementType::UNorm8 , ColorCompressType::None)) \
	E(LAs,		= TBM<ColorType>::makeInt(ColorModel::LA,	ColorElementType::UNorm16, ColorCompressType::None)) \
	E(LAh,		= TBM<ColorType>::makeInt(ColorModel::LA,	ColorElementType::Float16, ColorCompressType::None)) \
	E(LAf,		= TBM<ColorType>::makeInt(ColorModel::LA,	ColorElementType::Float32, ColorCompressType::None)) \
	\
	E(BC1,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC1)) \
	E(BC2,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC2)) \
	E(BC3,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC3)) \
	E(BC4,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC4)) \
	E(BC5,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC5)) \
	E(BC6h,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC6h)) \
	E(BC7,		= TBM<ColorType>::makeInt(ColorModel::BlockCompression, ColorElementType::None,	ColorCompressType::BC7)) \
	\
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(ColorType, u16);

#endif

#if 0
#pragma mark --- ColorR_T-Impl ---
#endif // 0
#if 1

template<class T>
class ColorR_T
{
public:
	using ElementType	= T;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 1;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::R, getColorElementType<ElementType>(), ColorCompressType::None);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);

public:
	union 
	{
		struct { T r; };
		T data[s_kElementCount];
	};

	ColorR_T() = default;
	ColorR_T(const T& r_)
		: r(r_) 
	{}

	template<class SE>
	void onJsonIo(SE& se) 
	{
		NMSP_NAMED_FIXED_IO(se, r);
	}
};

#endif

#if 0
#pragma mark --- ColorRG_T-Impl ---
#endif // 0
#if 1

template<class T>
class ColorRG_T
{
public:
	using ElementType	= T;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 2;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::RG, getColorElementType<ElementType>(), ColorCompressType::None);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
public:
	union 
	{
		struct { T r, g; };
		T data[s_kElementCount];
	};

	ColorRG_T() = default;
	ColorRG_T(const T& r_, const T& g_)
		: r(r_), g(g_)
	{}

	template<class SE>
	void onJsonIo(SE& se) 
	{
		NMSP_NAMED_FIXED_IO(se, r);
		NMSP_NAMED_FIXED_IO(se, g);
	}
};

#endif

#if 0
#pragma mark --- ColorRGB_T-Impl ---
#endif // 0
#if 1

template<class T>
class ColorRGB_T
{
public:
	using ElementType	= T;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 3;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::RGB, getColorElementType<ElementType>(), ColorCompressType::None);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);

public:
	union 
	{
		struct { T r, g, b; };
		T data[s_kElementCount];
	};

	ColorRGB_T() = default;
	ColorRGB_T(const T& r_, const T& g_, const T& b_)
		: r(r_), g(g_), b(b_)
	{}

	template<class SE>
	void onJsonIo(SE& se) 
	{
		NMSP_NAMED_FIXED_IO(se, r);
		NMSP_NAMED_FIXED_IO(se, g);
		NMSP_NAMED_FIXED_IO(se, b);
	}
};

#endif

#if 0
#pragma mark --- ColorRGBA_T-Impl ---
#endif // 0
#if 1

template<class T>
class ColorRGBA_T
{
public:
	using ElementType	= T;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 4;
	static constexpr int				s_kAlphaBits			= sCast<int>(BitUtil::bitSize<T>());
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::RGB, getColorElementType<ElementType>(), ColorCompressType::None);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);

public:
	union 
	{
		struct { T r, g, b, a; };
		T data[s_kElementCount];
	};

	ColorRGBA_T() = default;
	ColorRGBA_T(const T& r_, const T& g_, const T& b_, const T& a_)
		: r(r_), g(g_), b(b_), a(a_)
	{}

	template<class SE>
	void onJsonIo(SE& se) 
	{
		NMSP_NAMED_FIXED_IO(se, r);
		NMSP_NAMED_FIXED_IO(se, g);
		NMSP_NAMED_FIXED_IO(se, b);
		NMSP_NAMED_FIXED_IO(se, a);
	}
};

template<class T>
void onFormat(fmt::format_context& ctx, const ColorRGBA_T<T>& v)
{
	formatTo(ctx, "Color4({}, {}, {}, {})", v.r, v.g, v.b, v.a);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), ColorRGBA_T<NMSP_ARGS(T)> );

#endif

#if 0
#pragma mark --- ColorL_T-Impl ---
#endif // 0
#if 1

template<class T>
class ColorL_T
{
public:
	using ElementType	= T;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 1;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::L, getColorElementType<ElementType>(), ColorCompressType::None);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);

public:
	union 
	{
		struct { T l; };
		T data[s_kElementCount];
	};

	ColorL_T() = default;
	ColorL_T(const T& l_)
		: l(l_) 
	{}

	template<class SE>
	void onJsonIo(SE& se) 
	{
		NMSP_NAMED_FIXED_IO(se, l);
	}
};

#endif

#if 0
#pragma mark --- ColorL_T-Impl ---
#endif // 0
#if 1

template<class T>
class ColorLA_T
{
public:
	using ElementType	= T;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 2;
	static constexpr int				s_kAlphaBits			= sCast<int>(BitUtil::byteSize<T>());
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::LA, getColorElementType<ElementType>(), ColorCompressType::None);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);

public:
	union 
	{
		struct { T l, a; };
		T data[s_kElementCount];
	};

	ColorLA_T() = default;
	ColorLA_T(const T& l_, const T& a_)
		: l(l_), a(a_)
	{}

	template<class SE>
	void onJsonIo(SE& se) 
	{
		NMSP_NAMED_FIXED_IO(se, l);
		NMSP_NAMED_FIXED_IO(se, a);
	}
};

#endif


#if 0
#pragma mark --- ColorBC_T-Impl ---
#endif // 0
#if 1

class ColorBC1_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 1;
	static constexpr int				s_kBytesPerPixelBlock	= 8;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC1);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

class ColorBC2_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 4;
	static constexpr int				s_kBytesPerPixelBlock	= 16;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC2);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

class ColorBC3_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 8;
	static constexpr int				s_kBytesPerPixelBlock	= 16;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC3);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

class ColorBC4_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr int				s_kBytesPerPixelBlock	= 8;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC4);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

class ColorBC5_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr int				s_kBytesPerPixelBlock	= 16;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC5);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

class ColorBC6h_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 0;
	static constexpr int				s_kBytesPerPixelBlock	= 16;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC6h);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

class ColorBC7_T
{
public:
	using ElementType	= void;
	using SizeType		= FileIoTraits::SizeType;
	using IndexType		= FileIoTraits::IndexType;

public:
	static constexpr SizeType			s_kElementCount			= 0;
	static constexpr int				s_kAlphaBits			= 8;
	static constexpr int				s_kBytesPerPixelBlock	= 16;
	static constexpr ColorType			s_kColorType			= TBM<ColorType>::make(ColorModel::BlockCompression, getColorElementType<ElementType>(), ColorCompressType::BC7);
	static constexpr ColorModel			s_kColorModel			= TBM<ColorType>::getElementValue<0>(s_kColorType);
	static constexpr ColorElementType	s_kColorElementType		= TBM<ColorType>::getElementValue<1>(s_kColorType);
	static constexpr ColorCompressType	s_kColorCompressType	= TBM<ColorType>::getElementValue<2>(s_kColorType);
};

#endif

using ColorRb_T 	= ColorR_T<u8>;
using ColorRs_T 	= ColorR_T<u16>;
using ColorRf_T 	= ColorR_T<float>;

using ColorRGb_T 	= ColorRG_T<u8>;
using ColorRGs_T 	= ColorRG_T<u16>;
using ColorRGf_T 	= ColorRG_T<float>;

using ColorRGBb_T 	= ColorRGB_T<u8>;
using ColorRGBs_T 	= ColorRGB_T<u16>;
using ColorRGBf_T 	= ColorRGB_T<float>;

using ColorRGBAb_T 	= ColorRGBA_T<u8>;
using ColorRGBAs_T 	= ColorRGBA_T<u16>;
using ColorRGBAf_T 	= ColorRGBA_T<float>;

using Color1b_T = ColorRb_T;
using Color1s_T = ColorRs_T;
using Color1f_T = ColorRf_T;

using Color2b_T = ColorRGb_T;
using Color2s_T = ColorRGs_T;
using Color2f_T = ColorRGf_T;

using Color3b_T = ColorRGBb_T;
using Color3s_T = ColorRGBs_T;
using Color3f_T = ColorRGBf_T;

using Color4b_T = ColorRGBAb_T;
using Color4s_T = ColorRGBAs_T;
using Color4f_T = ColorRGBAf_T;

using ColorLb_T = ColorL_T<u8>;
using ColorLs_T = ColorL_T<u16>;
using ColorLf_T = ColorL_T<float>;

using ColorLAb_T = ColorLA_T<u8>;
using ColorLAs_T = ColorLA_T<u16>;
using ColorLAf_T = ColorLA_T<float>;


}