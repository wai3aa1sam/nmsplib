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

void* LinearAllocatorChunk_T::alloc(SizeType n, SizeType align)
{
	auto newOffset = _alignTo(_offset, align);
	if (n > remainSize())
	{
		return nullptr;
	}

	_offset = newOffset + n;
	return sCast<void*>(&_buffer[_offset]);
}

void LinearAllocatorChunk_T::clear()
{
	_offset = 0;
}

void* LinearAllocator_T::alloc(SizeType n, SizeType align)
{
	if (!_chunks.is_empty())
	{
		auto& curChunk = _chunks.back();
		auto* p = curChunk->alloc(n, align);
		if (p)
			return p;
	}

	auto newChunk = makeUnique<Chunk>(_chunkSize);
	_chunks.emplace_back(nmsp::move(newChunk));

	auto* p = newChunk->alloc(n, align);
	NMSP_ASSERT(p, "{}: n is > ChunkSize", NMSP_SRCLOC);
	return p;
}

void LinearAllocator_T::clear()
{
	_chunks.clear();
}

#endif


}