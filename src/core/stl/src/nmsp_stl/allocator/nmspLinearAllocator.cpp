#include "nmsp_stl-pch.h"
#include "nmspLinearAllocator.h"

namespace nmsp {

#if 0
#pragma mark --- LinearAllocator_T-Impl ---
#endif // 0
#if 1

LinearAllocatorChunk_T::LinearAllocatorChunk_T(SizeType n)
{
	_buffer.resize(n);
	_offset = 0;
}

void* LinearAllocatorChunk_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	return alloc(n, align, offset, nullptr);
}

void* LinearAllocatorChunk_T::alloc(SizeType n, SizeType align, SizeType offset, SizeType* outOffset)
{
	auto newOffset = _alignTo(_offset, align);
	auto available = _buffer.size() - newOffset;
	if (n > available)
	{
		return nullptr;
	}
	
	*outOffset = newOffset;
	_offset = newOffset + n;
	return sCast<void*>(&_buffer[newOffset]);
}


void LinearAllocatorChunk_T::clear()
{
	_offset = 0;
}

LinearAllocator_T::LinearAllocator_T(const char* name)
	: Base(name)
{

}

void* LinearAllocator_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	SizeType outOffset;
	return alloc(n, align, offset, &outOffset);
}

void* LinearAllocator_T::alloc(SizeType n, SizeType align, SizeType offset, SizeType* outOffset)
{
	if (!_chunks.is_empty())
	{
		auto& curChunk = _chunks.back();
		auto* p = curChunk->alloc(n, align, offset, outOffset);
		if (p)
			return p;
	}

	_chunks.emplace_back(makeUPtr<Chunk>(_chunkSize));

	auto* p = _chunks.back()->alloc(n, align, offset, outOffset);
	NMSP_ASSERT(p, "{}: n is > ChunkSize", NMSP_SRCLOC);
	return p;
}

void LinearAllocator_T::clear()
{
	_chunks.clear();
}

#endif


}