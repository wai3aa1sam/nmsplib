#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmsp_file_io/color/nmspColorUtil.h"

/*
references:
- src/core/graph/Image.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- Image_T-Decl ---
#endif // 0
#if 1

struct ImageInfo
{
public:
	using SizeType	= FileIoTraits::SizeType;
	using Vec2i		= Vec2i_T;

public:
	Vec2i size;
	ColorType colorType = ColorType::None;
	int strideInBytes	= 0;
	int mipmapCount		= 1;

public:
	int pixelByteSize() const { return ColorUtil::pixelByteSize(colorType); }
};

struct Image_CreateDesc
{
public:
	using SizeType	= FileIoTraits::SizeType;

public:
	ColorType	colorType = ColorType::None;
	int			width;
	int			height;
	int			strideInBytes;
	int			mipmapCount = 1;
};

class Image_T : public NonCopyable
{
public:
	using CreateDesc	= Image_CreateDesc;
	using Info			= ImageInfo;

	using SizeType	= Info::SizeType;
	using Vec2i		= Info::Vec2i;

public:
	static CreateDesc makeCDesc();

public:
	Image_T() = default;
	~Image_T();

	Image_T(Image_T&& rhs);
	void operator=(Image_T&& rhs);

	void clear();

	void load		(StrViewA_T filename);

	void loadPngFile(StrViewA_T filename);
	void loadPngMem	(ByteSpan_T data);

	void loadDdsFile(StrViewA_T filename);
	void loadDdsMem	(ByteSpan_T data);

	void create(const CreateDesc& cd);
	void create(ColorType colorType, int width, int height);
	void create(ColorType colorType, int width, int height, int strideInBytes);
	void create(ColorType colorType, int width, int height, int strideInBytes, int mipmapCount, SizeType dataSizeInBytes);

	void copyToPixelData(ByteSpan_T src);

	template<class COLOR> void fill(const COLOR& v);

	Span_T<		 u8>	data();
	Span_T<const u8>	data() const;

	template<class COLOR> 		COLOR& pixel(int x, int y);
	template<class COLOR> const COLOR& pixel(int x, int y) const;

	template<class COLOR> Span_T<		COLOR> row(int y);
	template<class COLOR> Span_T<const 	COLOR> row(int y) const;

	template<class COLOR> Span_T<		COLOR> row_noCheck(int y);
	template<class COLOR> Span_T<const 	COLOR> row_noCheck(int y) const;

	Span_T< 	 u8> rowBytes(int y);
	Span_T<const u8> rowBytes(int y) const;

			u8* dataPtr();
	const 	u8* dataPtr() const;
	
	SizeType	totalByteSize() const;
	bool		isValid()		const;
	bool		hasData()		const;
	bool		isValidSize()	const;

	int					width			() const;
	int					height			() const;
	int					pixelByteSize	() const;
	int					strideInBytes	() const;
	ColorType			colorType		() const;
	const ImageInfo&	info			() const;

protected:
	void move(Image_T&& rhs);

private:
	void _checkColorType(ColorType v) const;

private:
	ImageInfo		_info;
	Vector_T<u8>	_pixelData;
};

#endif

#if 0
#pragma mark --- Image_T-Impl ---
#endif // 0
#if 1

inline 
typename Image_T::SizeType 
Image_T::totalByteSize() const
{
	return width() * height() * pixelByteSize();
}

inline 
bool
Image_T::isValid() const
{
	return hasData() && isValidSize();
}

inline 
bool
Image_T::hasData() const
{
	return !_pixelData.is_empty();
}

inline 
bool
Image_T::isValidSize() const
{
	return width() > 0 && height() > 0;
}

inline 
Span_T<u8> Image_T::data()
{
	return _pixelData.span(); 
}

inline 
Span_T<const u8> Image_T::data() const
{
	return _pixelData.span(); 
}

template<class COLOR> inline 		
COLOR& Image_T::pixel(int x, int y)
{
	return row_noCheck(y)[x];
}

template<class COLOR> inline 
const COLOR& Image_T::pixel(int x, int y) const
{
	return row_noCheck(y)[x];
}

template<class COLOR> inline
Span_T<		 	COLOR> Image_T::row(int y)
{
	_checkColorType(COLOR::s_kColorType);
	return row_noCheck<COLOR>(y);
}

template<class COLOR> inline
Span_T<const 	COLOR> Image_T::row(int y) const
 {
	_checkColorType(COLOR::s_kColorType);
	return row_noCheck<const COLOR>(y);
 }

template<class COLOR> inline 		
Span_T<		 	COLOR> Image_T::row_noCheck(int y)
{
	return Span_T<COLOR>{reinCast<COLOR*>(rowBytes(y).data()), sCast<SizeType>(width())};
}

template<class COLOR> inline 
Span_T<const 	COLOR> Image_T::row_noCheck(int y) const
{
	return Span_T<const COLOR>{reinCast<const COLOR*>(rowBytes(y).data()), sCast<SizeType>(width())};
}

inline 
Span_T< 	 u8> Image_T::rowBytes(int y)
{
	NMSP_ASSERT(y >= 0 && y < height());
	auto rowByteSize = strideInBytes();
	return Span_T<u8>(dataPtr() + y * rowByteSize, rowByteSize);
}

inline 
Span_T<const u8> Image_T::rowBytes(int y) const
{
	NMSP_ASSERT(y >= 0 && y < height());
	auto rowByteSize = strideInBytes();
	return Span_T<const u8>(dataPtr() + y * rowByteSize, rowByteSize);
}

inline 		
u8* Image_T::dataPtr()
{
	return _pixelData.data();
}

inline 
const 	u8* Image_T::dataPtr() const
{
	return _pixelData.data();
}

inline 
int Image_T::width() const
{
	return info().size.x;
}

inline 
int Image_T::height() const
{
	return info().size.y;
}

inline 
typename int Image_T::pixelByteSize() const
{
	return info().pixelByteSize();
}

inline 
typename int Image_T::strideInBytes() const
{
	return info().strideInBytes;
}

inline 
ColorType Image_T::colorType() const
{
	return _info.colorType;
}

inline 
const ImageInfo& Image_T::info() const
{
	return _info;
}

inline
void 
Image_T::_checkColorType(ColorType v) const
{
	throwIf(v != colorType(), "{}", NMSP_SRCLOC);
}


#endif

}