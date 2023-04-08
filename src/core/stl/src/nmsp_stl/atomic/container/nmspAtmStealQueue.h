#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include "nmspAtmQueue.h"

namespace nmsp {

#if 0
#pragma mark --- AtmStealQueue_T-Decl ---
#endif // 0
#if 1

template<class T, class QUEUE = AtmQueue_T<T> >
class AtmStealQueue_T : public NonCopyable
{
public:
	using SizeType = size_t;
	using Queue = QUEUE;

public:
	AtmStealQueue_T()	= default;
	~AtmStealQueue_T()	= default;

	void		push		(const T& data);
	bool		try_pop		(T& o);
	bool		try_steal	(T& o);

	SizeType	size		() const;
	bool		is_empty	() const;

private:
	mutable Queue _queue;
};

#endif

#if 0
#pragma mark --- AtmStealQueue_T-Impl ---
#endif // 0
#if 1

template<class T, class QUEUE> inline
void AtmStealQueue_T<T, QUEUE>::push(const T& data)
{
	_queue.push(data);
}

template<class T, class QUEUE> inline
bool AtmStealQueue_T<T, QUEUE>::try_pop(T& o)
{
	return _queue.try_pop(o);
}

template<class T, class QUEUE> inline
bool AtmStealQueue_T<T, QUEUE>::try_steal(T& o)
{
	return _queue.try_pop(o);
}

template<class T, class QUEUE> inline
typename AtmStealQueue_T<T, QUEUE>::SizeType 
AtmStealQueue_T<T, QUEUE>::size() const
{
	return _queue.size();
}

template<class T, class QUEUE> inline
bool AtmStealQueue_T<T, QUEUE>::is_empty() const
{
	return _queue.is_empty();
}

#endif

}
