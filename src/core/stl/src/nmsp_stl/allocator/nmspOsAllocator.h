#pragma once

#include "nmsp_stl/allocator/nmspAllocator_Common.h"

namespace nmsp {


#if 0
#pragma mark --- OsAllocator_T-Decl ---
#endif // 0
#if 1

class OsAllocator_T : public Allocator_Base<OsAllocator_T>
{
public:
	OsAllocator_T(const char* name = "OsAllocator_T");
	~OsAllocator_T()	= default;

	void* alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign, SizeType offset = 0);
	
	void free(void* p, SizeType n = 0);
	
private:

};


#endif

//#if 0
//#pragma mark --- OsAllocator_T-Decl ---
//#endif // 0
//#if 1
//
//inline void* 
//OsAllocator_T::alloc(SizeType n, SizeType align, SizeType offset)
//{
//	return nullptr;
//	//return nmsp_alloc(n, align, offset);
//}
//
//void OsAllocator_T::free(void* p, SizeType n = 0)
//{
//	_notyetSupport();
//	//nmsp_free(p, n);
//}
//
//#endif


}