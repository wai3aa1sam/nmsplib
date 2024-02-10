#include "nmsp_file_io-pch.h"

#include "nmspImageIO_png.h"

NMSP_DISABLE_ALL_WARNINGS();

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

NMSP_RESTORE_ALL_WARNINGS();

#include "nmspImageIO_hdr.h"


namespace nmsp {

#if 0
#pragma mark --- ImageIO_png::Reader-Impl ---
#endif // 0
#if 1

ImageIO_png::Reader::~Reader()
{

}

void ImageIO_png::Reader::load(Image_T& image, ByteSpan_T data, ColorType expectType)
{
	auto imageCd = image.makeCDesc();

	int size			= sCast<int>(data.size());
	int channel			= 0;
	int reqChannel		= ColorUtil::getColorElementCount(expectType);
	
	stbi__context s;
	stbi__start_mem(&s, data.data(), size);
	stbi__result_info ri;
	void* p = stbi__load_main(&s, &imageCd.width, &imageCd.height, &channel, reqChannel, &ri, 8);
	auto lsa = makeLeaveScopeAction
	(
		[&p]()
		{
			stbi_image_free(p);
		}
	);

	NMSP_ASSERT(channel != 0, "");
	NMSP_ASSERT(p, "");

	channel = reqChannel;

	ColorType			outColorType		= ColorType::None;
	ColorElementType	outColorElementType = ColorElementType::None;
	ColorModel			outColorModel		= ColorModel::None;

	if (expectType == ColorType::None)
	{
		switch (channel)
		{
			case 1:		{ outColorModel = ColorModel::R;	} break;
			case 2:		{ outColorModel = ColorModel::RG;	} break;
			case 3:		{ outColorModel = ColorModel::RGB;	} break;
			case 4:		{ outColorModel = ColorModel::RGBA;	} break;
			default:	{ throwIf(true, "png error: unsupported format"); } break;
		}

		if (ri.bits_per_channel == 8)
		{
			outColorElementType = ColorElementType::UNorm8;
		}
		else if (ri.bits_per_channel == 16)
		{
			outColorElementType = ColorElementType::UNorm16;
		}
		else
		{
			throwIf(true, "png error: unsupported format");
		}

		outColorType = TBM<ColorType>::make(outColorModel, outColorElementType, ColorCompressType::None);
	}
	else
	{
		outColorType = expectType;
	}

	NMSP_ASSERT(ri.channel_order == STBI_ORDER_RGB, "png error: unsupported format order");
	throwIf(outColorType == ColorType::None, "png error: unsupported format");
	
	imageCd.colorType = outColorType;
	image.create(imageCd);
	memory_copy(image.dataPtr(), reinCast<const u8*>(p), image.totalByteSize());
}


// only one definiton for stb
void ImageIO_hdr::Reader::load(Image_T& image, ByteSpan_T data, ColorType expectType)
{
	auto imageCd = image.makeCDesc();

	int size			= sCast<int>(data.size());
	int channel			= 0;
	int reqChannel		= ColorUtil::getColorElementCount(expectType);

	stbi__context s;
	stbi__start_mem(&s, data.data(), size);
	stbi__result_info ri;
	void* p = stbi__load_main(&s, &imageCd.width, &imageCd.height, &channel, reqChannel, &ri, 8);
	auto lsa = makeLeaveScopeAction
	(
		[&p]()
		{
			stbi_image_free(p);
		}
	);

	NMSP_ASSERT(channel != 0, "");
	NMSP_ASSERT(p, "");

	channel = reqChannel;

	ColorType			outColorType		= ColorType::None;
	ColorElementType	outColorElementType = ColorElementType::None;
	ColorModel			outColorModel		= ColorModel::None;

	if (expectType == ColorType::None)
	{
		switch (channel)
		{
			case 1:		{ outColorModel = ColorModel::R;	} break;
			case 2:		{ outColorModel = ColorModel::RG;	} break;
			case 3:		{ outColorModel = ColorModel::RGB;	} break;
			case 4:		{ outColorModel = ColorModel::RGBA;	} break;
			default:	{ throwIf(true, "hdr error: unsupported format"); } break;
		}

		if (ri.bits_per_channel == 8)
		{
			outColorElementType = ColorElementType::UNorm8;
		}
		else if (ri.bits_per_channel == 16)
		{
			outColorElementType = ColorElementType::UNorm16;
		}
		else
		{
			throwIf(true, "hdr error: unsupported format");
		}

		outColorType = TBM<ColorType>::make(outColorModel, outColorElementType, ColorCompressType::None);
	}
	else
	{
		outColorType = expectType;
	}

	NMSP_ASSERT(ri.channel_order == STBI_ORDER_RGB, "hdr error: unsupported format order");
	throwIf(outColorType == ColorType::None, "hdr error: unsupported format");

	imageCd.colorType = outColorType;
	image.create(imageCd);
	memory_copy(image.dataPtr(), reinCast<const u8*>(p), image.totalByteSize());
}

#endif

}