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

class LinearAllocator_T;

struct LinearAllocatorChunk_T
{
	friend class LinearAllocator_T;

public:
	using This = LinearAllocatorChunk_T;
	using SizeType = StlTraits::SizeType;

public:
	static constexpr SizeType s_kDefaultAlign = StlTraits::s_kDefaultAlign;

public:
	LinearAllocatorChunk_T(SizeType n);

	void* alloc(SizeType* outChunkOffset, SizeType n, SizeType align, SizeType offset);
	void* alloc(SizeType n, SizeType align = s_kDefaultAlign, SizeType offset = 0);
	void  clear();

	template<class T> void destruct(		SizeType align);
	template<class T> void destructAndClear(SizeType align);

	const u8*	data()			const;
	SizeType	size()			const;
	SizeType	remainSize()	const;
	SizeType	capacity()		const;

private:
	Vector_T<u8>	_buffer;
	SizeType		_offset = 0;
};

class LinearAllocator_T : public Allocator_Base<LinearAllocator_T>
{
public:
	using This	= LinearAllocator_T;
	using Base  = Allocator_Base<LinearAllocator_T>;
	using Chunk = LinearAllocatorChunk_T;

	using SizeType = Chunk::SizeType;

public:
	static constexpr SizeType s_kDefaultAlign = LinearAllocatorChunk_T::s_kDefaultAlign;

public:
	LinearAllocator_T(const char* name = "LinearAllocator_T");
	//void operator=(This&& rhs);
	LinearAllocator_T(const This&	rhs) = delete;
	LinearAllocator_T(		This&&	rhs);
	void operator=(const	This&	rhs) = delete;
	void operator=(			This&&	rhs);

public:
	void setChunkSize(SizeType n);

	void* alloc(SizeType* outChunkId, SizeType* outChunkOffset, SizeType n, SizeType align, SizeType offset);
	void* alloc(SizeType n, SizeType align = s_kDefaultAlign, SizeType offset = 0);
	void* alloc(SizeType* outChunkId, SizeType* outChunkOffset, SizeType n);

	void  free(void* p, SizeType n = 0) {}

	/*
	* reset all chunk to 0 offset and start from first chunk, but this need to rewrite current alloc
	*/
	void  clear();

	/*
	* free all chunks
	*/
	// void destroy();

	template<class T> void destruct(		SizeType align);
	template<class T> void destructAndClear(SizeType align);

public:
	SizeType						chuckCount()	const;
	Span_T<const UPtr_T<Chunk> >	chunks()		const;

protected:
	void move(This&& rhs);

private:
	Vector_T<UPtr_T<Chunk> > _chunks;
	SizeType _chunkSize = 16 * 1024;
};

inline LinearAllocator_T::SizeType LinearAllocator_T::chuckCount() const { return _chunks.size(); }

inline
Span_T<const UPtr_T<LinearAllocator_T::Chunk> > 
LinearAllocator_T::chunks() const
{
	return _chunks.span();
}

#endif

#if 0
#pragma mark --- LinearAllocator_T-Impl ---
#endif // 0
#if 1

//inline 
//void LinearAllocatorChunk_T::operator=(This&& rhs)
//{
//	_buffer = nmsp::move(rhs._buffer);
//	_offset = rhs._offset;
//}

inline const u8* LinearAllocatorChunk_T::data() const { return _buffer.data(); }

inline LinearAllocatorChunk_T::SizeType LinearAllocatorChunk_T::size()			const { return _offset; }
inline LinearAllocatorChunk_T::SizeType LinearAllocatorChunk_T::remainSize()	const { return _buffer.size() - _offset; }
inline LinearAllocatorChunk_T::SizeType LinearAllocatorChunk_T::capacity()		const { return _buffer.size(); }

template<class T> inline 
void LinearAllocatorChunk_T::destruct(SizeType align)
{
	auto alignedSize = _alignTo(sizeof(T), align);
	for (size_t i = 0; i < _offset; i += alignedSize)
	{
		reinCast<T*>(&_buffer[i])->~T();
	}
}

template<class T> inline 
void LinearAllocatorChunk_T::destructAndClear(SizeType align)
{
	destruct<T>(align);
	clear();
}

// ---

//inline
//void LinearAllocator_T::operator=(This&& rhs)
//{
//	_chunks.clear();
//	_chunks.reserve(rhs._chunks.size());
//	for (auto& e : rhs._chunks)
//	{
//		_chunks.emplace_back(nmsp::move(e));
//	}
//	_chunkSize	= rhs._chunkSize;
//}

inline
void LinearAllocator_T::setChunkSize(SizeType n)	{ _chunkSize = n; }

template<class T> inline 
void LinearAllocator_T::destruct(SizeType align)
{
	for (auto& chunk : _chunks)
	{
		chunk->destruct<T>(align);
	}
}

template<class T> inline 
void LinearAllocator_T::destructAndClear(SizeType align)
{
	for (auto& chunk : _chunks)
	{
		chunk->destructAndClear<T>(align);
	}
}

#endif

}