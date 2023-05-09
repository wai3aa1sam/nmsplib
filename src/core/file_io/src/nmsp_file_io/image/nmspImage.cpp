#include "nmsp_file_io-pch.h"

#include "nmspImage.h"

namespace nmsp {

#if 0
#pragma mark --- Image_T-Impl ---
#endif // 0
#if 1



#endif

Image_T::~Image_T()
{
}

void Image_T::clear()
{
}

void Image_T::load(StrViewA_T filename)
{
}

void Image_T::loadPng(StrViewA_T filename)
{
}

void Image_T::loadPngMem(ByteSpan_T data)
{
}

void Image_T::loadDds(StrViewA_T filename)
{
}

void Image_T::loadDdaMem(ByteSpan_T data)
{
}

void Image_T::create(const CreateDesc& cd)
{
}

ByteSpan_T Image_T::data() const
{
	return ByteSpan_T();
}

int Image_T::width() const
{
	return 0;
}

int Image_T::height() const
{
	return 0;
}

typename Image_T::SizeType Image_T::pixelSize() const
{
	return SizeType();
}

ColorType Image_T::colorType() const
{
	return _info.colorType;
}

const ImageInfo& Image_T::info() const
{
	return _info;
}

}