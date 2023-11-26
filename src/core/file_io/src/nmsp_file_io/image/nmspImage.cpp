#include "nmsp_file_io-pch.h"

#include "nmspImage.h"

#include "nmspImageIO_png.h"
#include "nmspImageIO_dds.h"

namespace nmsp {

#if 0
#pragma mark --- Image_T-Impl ---
#endif // 0
#if 1

Image_T::CreateDesc Image_T::makeCDesc()
{
	return CreateDesc{};
}

Image_T::~Image_T()
{
}

Image_T::Image_T(Image_T&& rhs)
{
	move(nmsp::move(rhs));
}

void 
Image_T::operator=(Image_T&& rhs)
{
	NMSP_CORE_ASSERT(this != &rhs, "");
	move(nmsp::move(rhs));
}

void Image_T::clear()
{
	_pixelData.clear();
}

void Image_T::load(StrViewA_T filename)
{
	_info.colorType = _info.colorType == ColorType::None ? ColorType::RGBAb : _info.colorType;

	auto ext	= Path::extension(filename);
	int ret		= 0;

	ret = StrUtil::ignoreCaseCompare(ext, "png");
	if (ret == 0) { return loadPngFile(filename); }

	ret = StrUtil::ignoreCaseCompare(ext, "dds");
	if (ret == 0) { return loadDdsFile(filename); }
}

void Image_T::loadPngFile(StrViewA_T filename)
{
	MemMapFile_T mmf;
	mmf.open(filename);
	return loadPngMem(mmf.span());
}

void Image_T::loadPngMem(ByteSpan_T data)
{
	ImageIO_png::Reader reader;
	reader.load(*this, data, colorType());
}

void Image_T::loadDdsFile(StrViewA_T filename)
{
	MemMapFile_T mmf;
	mmf.open(filename);
	return loadDdsMem(mmf.span());
}

void Image_T::loadDdsMem(ByteSpan_T data)
{
	ImageIO_dds::Reader reader;
	reader.load(*this, data, colorType());
}

void Image_T::create(const CreateDesc& cd)
{
    _info.size.set(cd.width, cd.height);
    _info.colorType     = cd.colorType;
    _info.mipmapCount   = cd.mipmapCount;
    _info.strideInBytes = cd.strideInBytes == 0 ? ColorUtil::pixelByteSize(cd.colorType) * cd.width : cd.strideInBytes;

    _pixelData.clear();
    _pixelData.resize(totalByteSize());
}

void 
Image_T::create(ColorType colorType, int width, int height)
{
	create(colorType, width, height, width * ColorUtil::pixelByteSize(colorType));
}

void 
Image_T::create(ColorType colorType, int width, int height, int strideInBytes)
{
	create(colorType, width, height, strideInBytes, 1, height * strideInBytes);
}

void 
Image_T::create(ColorType colorType, int width, int height, int strideInBytes, int mipmapCount, SizeType dataSizeInBytes)
{
	auto cDesc = makeCDesc();
	cDesc.colorType			= colorType;
	cDesc.width				= width;
	cDesc.height			= height;
	cDesc.strideInBytes		= strideInBytes;
	cDesc.mipmapCount		= mipmapCount;
	create(cDesc);
}

void 
Image_T::copyToPixelData(ByteSpan_T src) 
{ 
	_pixelData.assign(src.begin(), src.end()); 
}

void 
Image_T::move(Image_T&& rhs)
{
	_info		= rhs._info;
	_pixelData	= nmsp::move(rhs._pixelData);
}

#endif

}