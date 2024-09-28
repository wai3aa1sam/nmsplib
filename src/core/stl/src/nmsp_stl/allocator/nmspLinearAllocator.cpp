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

void* 
LinearAllocatorChunk_T::alloc(SizeType* outChunkOffset, SizeType n, SizeType align, SizeType offset)
{
	auto newChunkOffset = _alignTo(_offset, align);
	auto available = _buffer.size() - newChunkOffset;
	if (n > available)
	{
		return nullptr;
	}
	
	*outChunkOffset = newChunkOffset;
	_offset = newChunkOffset + n;
	return sCast<void*>(&_buffer[newChunkOffset]);
}

void* 
LinearAllocatorChunk_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	SizeType outChunkOffset = 0;
	return alloc(&outChunkOffset, n, align, offset);
}

void 
LinearAllocatorChunk_T::clear()
{
	_offset = 0;
}

#endif

#if 0
#pragma mark --- LinearAllocator_T-Impl ---
#endif // 0
#if 1

LinearAllocator_T::LinearAllocator_T(const char* name)
	: Base(name)
{

}

//LinearAllocator_T::LinearAllocator_T(const This& rhs)
//{
//	set_name(rhs.name());
//	
//}

LinearAllocator_T::LinearAllocator_T(This&& rhs)
{
	move(nmsp::move(rhs));
}

//void 
//LinearAllocator_T::operator=(const This& rhs)
//{
//
//}

void 
LinearAllocator_T::operator=(This&& rhs)
{
	if (this != &rhs)
		move(nmsp::move(rhs));
}

void 
LinearAllocator_T::move(This&& rhs)
{
	set_name(rhs.name());
	_chunks		= nmsp::move(rhs._chunks);
	_chunkSize	= rhs._chunkSize;
}

void* 
LinearAllocator_T::alloc(SizeType* outChunkId, SizeType* outChunkOffset, SizeType n, SizeType align, SizeType offset)
{
	if (!_chunks.is_empty())
	{
		auto& curChunk = _chunks.back();
		void* p = curChunk->alloc(outChunkOffset, n, align, offset);
		if (p)
		{
			*outChunkId = _chunks.size() - 1;
			return p;
		}
	}

	// case: prev chunk alloc failed
	_chunks.emplace_back(makeUPtr_T<Chunk>(_chunkSize));
	*outChunkId = _chunks.size() - 1;

	void* p = _chunks.back()->alloc(outChunkOffset, n, align, offset);
	NMSP_CORE_ASSERT(p, "{}: n is > ChunkSize", NMSP_SRCLOC);

	return p;
}

void* 
LinearAllocator_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	SizeType outChunkId;
	SizeType outChunkOffset;
	return alloc(&outChunkId, &outChunkOffset, n, align, offset);
}

void*
LinearAllocator_T::alloc(SizeType* outChunkId, SizeType* outChunkOffset, SizeType n)
{
	return alloc(outChunkId, outChunkOffset, n, s_kDefaultAlign, 0);
}

void 
LinearAllocator_T::clear()
{
	_chunks.clear();
}

#endif


}