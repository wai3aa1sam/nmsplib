#pragma once

#include "nmsp_file_io/common/nmsp_file_io_common.h"

#include "nmsp_file_io/image/nmspImage.h"

namespace nmsp {

#if 0
#pragma mark --- ImageIO_hdr-Decl ---
#endif // 0
#if 1

struct ImageIO_hdr
{
public:
	class Reader
	{
	public:
		~Reader();

		void load(Image_T& image, ByteSpan_T data, ColorType expectType = ColorType::None);

	};

public:
	class Writer
	{
	public:
		~Writer();

		void write();
	};
};


#endif

}