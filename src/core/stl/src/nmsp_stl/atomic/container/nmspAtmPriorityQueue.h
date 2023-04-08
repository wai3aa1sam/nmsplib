#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include "nmspAtmStealQueue.h"

namespace nmsp {

#if 0
#pragma mark --- AtmPrioityQueue_T-Decl ---
#endif // 0
#if 1

template<class T, size_t N_PRIORITY, class PRIORITY, class QUEUE = AtmStealQueue_T<T> >
class AtmPrioityQueue_T
{
public:
	static constexpr size_t s_kPriorityCount = N_PRIORITY;
	using Priority = PRIORITY;

	void push(const T& val, Priority pri = static_cast<Priority>(0) );
	bool try_pop(T& o);

private:
	QUEUE _queues[s_kPriorityCount];
};

#endif

#if 0
#pragma mark --- AtmPrioityQueue_T-Decl ---
#endif // 0
#if 1

template<class T, size_t N_PRIORITY, class PRIORITY, class QUEUE> inline
void AtmPrioityQueue_T<T, N_PRIORITY, PRIORITY, QUEUE>::push(const T& val, Priority pri)
{
	NMSP_ASSERT(enumInt(pri) >= 0 && enumInt(pri) < s_kPriorityCount, "PrioityQueues<T>: invalid priority");
	_queues[enumInt(pri)].push(val);
}

template<class T, size_t N_PRIORITY, class PRIORITY, class QUEUE> inline
bool AtmPrioityQueue_T<T, N_PRIORITY, PRIORITY, QUEUE>::try_pop(T& o)
{
	for (size_t i = 0; i < s_kPriorityCount; i++)
	{
		if (_queues[i].try_pop(o))
			return true;
	}
	return false;
}

#endif
}
