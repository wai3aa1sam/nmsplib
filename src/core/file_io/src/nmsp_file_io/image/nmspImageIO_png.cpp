#include "nmsp_file_io-pch.h"

#include "nmspImageIO_png.h"

#pragma warning( push )
#pragma warning( disable : 4244 )

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#pragma warning( pop )


#include "nmsp_file_io/color/nmspColorUtil.h"

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
	int size		= sCast<int>(data.size());
	auto imageCd	= image.makeCDesc();
	int channel		= 0;
	int reqChannel	= ColorUtil::getElementCount(expectType);

	stbi_uc* p = stbi_load_from_memory(data.data(), size, &imageCd.width, &imageCd.height, &channel, reqChannel);
	NMSP_ASSERT(channel != 0, "");
	NMSP_ASSERT(p, "");

	// setReadFilter

	image.create(imageCd);

	memory_copy(image.data().data(), reinCast<const u8*>(p), image.totalByteSize());

}

#endif

}