#include "nmsp_file_io-pch.h"

#include "nmspImageIO_png.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace nmsp {

#if 0
#pragma mark --- ImageIO_png::Reader-Impl ---
#endif // 0
#if 1

ImageIO_png::Reader::~Reader()
{

}

void ImageIO_png::Reader::load(Image_T& image, ByteSpan_T data, ColorType execptType)
{
	int size = sCast<int>(data.size());
	auto imageCd = image.makeCDesc();

	stbi_load_from_memory(data.data(), size, &imageCd.width, &imageCd.height);
}

#endif

}