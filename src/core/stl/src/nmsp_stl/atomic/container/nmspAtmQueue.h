#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include "nmsp_stl/allocator/nmspAllocator.h"

#include <concurrentqueue/concurrentqueue.h>
// Provides a C++11 implementation of a multi-producer, multi-consumer lock-free queue.
// An overview, including benchmark results, is provided here:
//     http://moodycamel.com/blog/2014/a-fast-general-purpose-lock-free-queue-for-c++
// The full design is also described in excruciating detail at:
//    http://moodycamel.com/blog/2014/detailed-design-of-a-lock-free-queue

// Simplified BSD license:
// Copyright (c) 2013-2020, Cameron Desrochers.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this list of
// conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of
// conditions and the following disclaimer in the documentation and/or other materials
// provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Also dual-licensed under the Boost Software License (see LICENSE.md)

namespace nmsp {

template<size_t N, class ALLOC> struct AtmQueueTraits;
template<class T, size_t N, class ALLOC, class TRAITS> class AtmQueue_Mc;

template<class T, size_t N = 256, class ALLOC = DefaultAllocator, class TRAITS = AtmQueueTraits<N, ALLOC> >
using AtmQueue_T = AtmQueue_Mc<T, N, ALLOC, TRAITS>;

#if 0
#pragma mark --- AtmQueue_Mc-Decl ---
#endif // 0
#if 1

struct AtmQueueDefaultTraits : public moodycamel::ConcurrentQueueDefaultTraits
{

};

template<size_t N, class ALLOC = DefaultAllocator>
struct AtmQueueTraits : public AtmQueueDefaultTraits
{
	//static ALLOC allocator;
	static const size_t BLOCK_SIZE = N;		// Use bigger blocks

	static inline void* malloc(size_t size) 
	{ 
		return nmsp_alloc(size); 
	}
	static inline void free(void* ptr) 
	{ 
		return nmsp_free(ptr); 
	}
};

template<class T, size_t N = 256, class ALLOC = DefaultAllocator, class TRAITS = AtmQueueTraits<N, ALLOC> > 
class AtmQueue_Mc : public NonCopyable
{
public:
	using Traits = AtmQueueTraits<N, ALLOC>;
	using Queue = moodycamel::ConcurrentQueue<T, Traits>;
	using SizeType = typename Queue::size_t;

public:
	AtmQueue_Mc() = default;
	~AtmQueue_Mc() = default;

	void push(const T& data);
	bool try_pop(T& o);

	SizeType	size	()	const;
	bool		is_empty()	const;

private:
	Queue _queue;
};


#endif


#if 0
#pragma mark --- AtmQueue_Mc-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class ALLOC, class TRAITS >  inline
void		AtmQueue_Mc<T, N, ALLOC, TRAITS>::push(const T& data)
{
	_queue.enqueue(data);
}

template<class T, size_t N, class ALLOC, class TRAITS>  inline
bool		AtmQueue_Mc<T, N, ALLOC, TRAITS>::try_pop(T& o)
{
	return _queue.try_dequeue(o);
}

template<class T, size_t N, class ALLOC, class TRAITS> inline
typename AtmQueue_Mc<T, N, ALLOC, TRAITS>::SizeType
AtmQueue_Mc<T, N, ALLOC, TRAITS>::size() const
{
	return _queue.size_approx();
}

template<class T, size_t N, class ALLOC, class TRAITS>  inline
bool		AtmQueue_Mc<T, N, ALLOC, TRAITS>::is_empty() const
{
	return size() == 0;
}


#endif

}
