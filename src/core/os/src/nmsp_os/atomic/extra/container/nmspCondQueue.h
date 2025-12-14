#pragma once

#include "nmsp_os/common/nmsp_os_common.h"
#include "nmsp_os/atomic/nmspMutex.h"
#include "nmsp_os/atomic/nmspCondMutex.h"
#include "nmsp_stl/container/nmspSList.h"

namespace nmsp {

#if 0
#pragma mark --- nmspCondQueue_T-Decl ---
#endif // 0
#if 1

template<class T, bool IsBroadcast = false, class T_Deleter = DefaultDeleter<T>, class T_Allocator = DefaultAllocator>
class CondQueue_T : public NonCopyable 
{
public:
	using Int = i64;

	using UPtr	= UPtr_T<T, T_Deleter>;
	using Ptr	= T*;
	using List	= Vector_T<UPtr, 0, T_Allocator>;		// temp: workaround

public:
	struct MData 
	{
		Int			_maxSize = NumLimit<Int>::max();
		List		_list;
		//SList_T<T>	_list; // cannot use DList, because DListNode::removeFromList() may cause race condition
	};
	using ProtectedData = CondMutexProtected_T<MData, IsBroadcast>;
	using ScopedLock	= typename ProtectedData::ScopedLock;

	void	clear() {
		auto md = _mdata.scopedLock();
		md->_list.clear();
	}

	void insert(UPtr p)	{
		auto md = _mdata.scopedLock();
		while (sCast<Int>(md->_list.size()) >= md->_maxSize) {
			md.wait();
		}
		//md->_list.insert(p);
		_insert(md->_list, nmsp::move(p));
	}

	void append(UPtr p)	{
		auto md = _mdata.scopedLock();
		while (sCast<Int>(md->_list.size()) >= md->_maxSize) {
			md.wait();
		}
		//md->_list.append(p);
		_append(md->_list, nmsp::move(p));
	}

	//void	insert	(UPtr&& p)	{ insert(p.ptr()); p.detach(); }
	//void	append	(UPtr&& p)	{ append(p.ptr()); p.detach(); }

	void	setMaxSize(Int n) { _mdata.scopedLock()->_maxSize = n; }

	UPtr	popHead	()	{ return _popHead(_mdata.scopedLock()->_list); }
	UPtr	popTail	()	{ return _popTail(_mdata.scopedLock()->_list); }

	UPtr	waitHead() {
		auto md = _mdata.scopedLock();
		for(;;) {
			auto p = _popHead(md->_list);
			if (p) return p;
			md.wait();
		}
	}

	UPtr	timedWaitHead(Int milliseconds) {
		auto md = _mdata.scopedLock();
		for(;;) {
			auto p = _popHead(md->_list);
			if (p) return p;
			if (!md.timed_wait(milliseconds))
				return nullptr;
		}
	}

	Int size() {
		auto md = _mdata.scopedLock();
		return md->_list.size();
	}

	bool isEmpty() { return size() == 0; }

private:
	void _insert	(List& list, UPtr p)	
	{
		list.emplace(list.begin(), nmsp::move(p));
	}

	void _append(List& list, UPtr p)	
	{
		list.emplace_back(nmsp::move(p));
	}

	UPtr _popHead(List& list)	
	{
		return list.is_empty() ? nullptr : list.moveFront(); 
	}

	UPtr _popTail(List& list)	
	{
		return list.is_empty() ? nullptr : list.moveBack(); 
	}

private:
	ProtectedData _mdata;
};

#endif

}
