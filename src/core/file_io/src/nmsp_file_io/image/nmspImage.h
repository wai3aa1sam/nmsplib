#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmsp_file_io/color/nmspColor.h"

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
	SizeType pixelSize() const { return 0; }
};

struct Image_CreateDesc
{
public:
	using SizeType	= FileIoTraits::SizeType;

public:
	ColorType colorType = ColorType::None;
	int width;
	int height;
	int strideInBytes;
	int mipmapCount = 1;
	SizeType dataSizeInBytes;
};

class Image_T : public NonCopyable
{
public:
	using CreateDesc = Image_CreateDesc;
	using Info = ImageInfo;

	using SizeType	= Info::SizeType;
	using Vec2i		= Info::Vec2i;

public:
	static CreateDesc makeCDesc();

public:
	Image_T() = default;
	~Image_T();

	void clear();

	void load		(StrViewA_T filename);

	void loadPng	(StrViewA_T filename);
	void loadPngMem	(ByteSpan_T data);

	void loadDds	(StrViewA_T filename);
	void loadDdaMem	(ByteSpan_T data);

	void create(const CreateDesc& cd);

	Span_T<const u8>	data() const;
	Span_T<u8>			data() ;

	SizeType totalByteSize() const;

	int					width		() const;
	int					height		() const;
	SizeType			pixelSize	() const;
	ColorType			colorType	() const;
	const ImageInfo&	info		() const;

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
typename Image_T::SizeType Image_T::totalByteSize() const
{
	return width() * height() * pixelSize();
}


inline ByteSpan_T Image_T::data() const
{
	return ByteSpan_T();
}

inline int Image_T::width() const
{
	return 0;
}

inline int Image_T::height() const
{
	return 0;
}

inline typename Image_T::SizeType Image_T::pixelSize() const
{
	return SizeType();
}

inline ColorType Image_T::colorType() const
{
	return _info.colorType;
}

inline const ImageInfo& Image_T::info() const
{
	return _info;
}

#endif

}