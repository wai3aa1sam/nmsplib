#include "nmsp_file_io-pch.h"

#include "nmspImage.h"

namespace nmsp {

#if 0
#pragma mark --- Image_T-Impl ---
#endif // 0
#if 1

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
    _info.size.set(cd.width, cd.height);
    _info.colorType     = cd.colorType;
    _info.mipmapCount   = cd.mipmapCount;
    _info.strideInBytes = cd.strideInBytes == 0 ? ColorUtil::pixelByteSize(cd.colorType) * cd.width : cd.dataSizeInBytes;

    _pixelData.clear();
    _pixelData.resize(totalByteSize());
}


#endif

}