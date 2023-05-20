#pragma once

#include "nmspAllocator_Common.h"

#include "nmsp_stl/container/nmspVector.h"
#include "nmsp_stl/container/nmspList.h"
#include "nmsp_stl/pointer/nmspUPtr.h"

/*
references:
- src/core/allocator/LinearAllocator.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- LinearAllocator_T-Decl ---
#endif // 0
#if 1

struct LinearAllocatorChunk_T
{
public:
	using SizeType = StlTraits::SizeType;

public:
	LinearAllocatorChunk_T(SizeType n);

	void* alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign);
	void  clear();

	template<class T> void destruct();
	template<class T> void destructAndClear();

	SizeType size()			const;
	SizeType remainSize()	const;
	SizeType capacity()		const;

private:
	Vector_T<u8>	_buffer;
	SizeType		_offset = 0;
};

class LinearAllocator_T : public Allocator_Base<LinearAllocator_T>
{
public:
	using Chunk = LinearAllocatorChunk_T;

	using SizeType = Chunk::SizeType;
public:
	void setChunkSize(SizeType n);

	void* alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign);
	void  clear();

	template<class T> void destruct();
	template<class T> void destructAndClear();

private:
	Vector_T<UPtr_T<Chunk> > _chunks;
	SizeType _chunkSize = 16 * 1024;
};

#endif

#if 0
#pragma mark --- LinearAllocator_T-Impl ---
#endif // 0
#if 1

inline LinearAllocatorChunk_T::SizeType LinearAllocatorChunk_T::size()			const { return _offset; }
inline LinearAllocatorChunk_T::SizeType LinearAllocatorChunk_T::remainSize()	const { return _buffer.size() - _offset; }
inline LinearAllocatorChunk_T::SizeType LinearAllocatorChunk_T::capacity()		const { return _buffer.size(); }

template<class T> inline 
void LinearAllocatorChunk_T::destruct()
{
	for (size_t i = 0; i < _offset; i += sizeof(T))
	{
		reinCast<T*>(&_buffer[i])->~T();
	}
}

template<class T> inline 
void LinearAllocatorChunk_T::destructAndClear()
{
	destruct<T>();
	clear();
}

// ---

inline
void LinearAllocator_T::setChunkSize(SizeType n)	{ _chunkSize = n; }

template<class T> inline 
void LinearAllocator_T::destruct()
{
	for (auto& chunk : _chunks)
	{
		chunk.destruct<T>();
	}
}

template<class T> inline 
void LinearAllocator_T::destructAndClear()
{
	for (auto& chunk : _chunks)
	{
		chunk.destructAndClear<T>();
	}
}

#endif

}