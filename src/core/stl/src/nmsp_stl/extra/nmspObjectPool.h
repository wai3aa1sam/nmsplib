#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"
#include "nmsp_stl/allocator/nmspLinearAllocator.h"
#include "nmsp_stl/container/nmspVector.h"

namespace nmsp {


#if 0
#pragma mark --- nmspObjectPool_T-Impl ---
#endif // 0
#if 1

template<class T>
class ObjectPool_T : public NonCopyable
{
public:
	~ObjectPool_T();

public:
	void clear();

	template<class... T_Args>
	T* newObject(T_Args&&... args);

	void deleteObject(T* obj);

private:
	LinearAllocator_T	_alloc;
	Vector_T<T*>		_freedObjs;
};

#endif

#if 0
#pragma mark --- nmspObjectPool_T-Impl ---
#endif // 0
#if 1

template<class T> inline
ObjectPool_T<T>::~ObjectPool_T()
{
	clear();
}

template<class T> inline
void
ObjectPool_T<T>::clear()
{
	_freedObjs.clear();
	_alloc.destructAndClear<T>(_alloc.s_kDefaultAlign);

}

template<class T> 
template<class... T_Args> inline
T* 
ObjectPool_T<T>::newObject(T_Args&&... args)
{
	if (!_freedObjs.is_empty())
	{
		auto obj = _freedObjs.moveBack();
		obj = new(obj) T();
		return obj;
	}
	else
	{
		auto* buf		= _alloc.alloc(sizeof(T));;
		auto* newObj	= new(buf) T(nmsp::forward(args)...);
		//_objs.emplace_back(newObj);
		return newObj;
	}
}

template<class T> inline
void 
ObjectPool_T<T>::deleteObject(T* obj)
{
	obj->~T();
	_freedObjs.emplace_back(obj);
}

#endif

}