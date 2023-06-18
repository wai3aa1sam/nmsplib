#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#include <EASTL/version.h>

namespace nmsp {

#if 0
#pragma mark --- AllocatorBase_Eastl-Decl ---
#endif // 0
#if 1

template<class ALLOC> class AllocatorBase_Nmsp;

template<class ALLOC_NMSP>
class AllocatorBase_Eastl : public AllocatorBase_Nmsp<ALLOC_NMSP>
{
    //using Base = ALLOC_NMSP;
public:
    using Allocator_Nmsp = ALLOC_NMSP;
public:
    AllocatorBase_Eastl(const char* pName = EASTL_NAME_VAL(EASTL_ALLOCATOR_DEFAULT_NAME));
    AllocatorBase_Eastl(const AllocatorBase_Eastl& x);
    AllocatorBase_Eastl(const AllocatorBase_Eastl& x, const char* pName);

    AllocatorBase_Eastl& operator=(const AllocatorBase_Eastl& x);

    void* allocate(size_t n, int flags = 0);
    void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0);
    void  deallocate(void* p, size_t n);

    const char* get_name() const;
    void        set_name(const char* pName);

protected:
    #if EASTL_NAME_ENABLED
    const char* mpName; // Debug name, used to track memory.
    #endif
protected:
    //using Base::alloc;
    ////using Base::alloc_all;
    //using Base::free;
    ////using Base::free_all;
    //using Base::is_owning;
};

#endif


#if 0
#pragma mark --- AllocatorBase_Eastl-Impl ---
#endif // 0
#if 1

template<class ALLOC_NMSP> inline
AllocatorBase_Eastl<ALLOC_NMSP>::AllocatorBase_Eastl(const char* pName)
    //: Base(pName)
{
    #if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
    #endif
}

template<class ALLOC_NMSP> inline
AllocatorBase_Eastl<ALLOC_NMSP>::AllocatorBase_Eastl(const AllocatorBase_Eastl& x)
    //: Base(x)
{
    #if EASTL_NAME_ENABLED
    mpName = x.mpName;
    #endif
}

template<class ALLOC_NMSP> inline
AllocatorBase_Eastl<ALLOC_NMSP>::AllocatorBase_Eastl(const AllocatorBase_Eastl& x, const char* pName)
   // : Base(x, pName)
{
    #if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
    #endif
}

template<class ALLOC_NMSP> inline
AllocatorBase_Eastl<ALLOC_NMSP>& AllocatorBase_Eastl<ALLOC_NMSP>::operator=(const AllocatorBase_Eastl& x)
{
    #if EASTL_NAME_ENABLED
    mpName = x.mpName;
    #endif
    return *this;
}

template<class ALLOC_NMSP> inline
void*       AllocatorBase_Eastl<ALLOC_NMSP>::allocate(size_t n, int flags)
{
    return sCast<Allocator_Nmsp&>(*this).alloc(n);
}

template<class ALLOC_NMSP> inline
void*       AllocatorBase_Eastl<ALLOC_NMSP>::allocate(size_t n, size_t alignment, size_t offset, int flags)
{
    return sCast<Allocator_Nmsp&>(*this).alloc(n, alignment, offset);
}

template<class ALLOC_NMSP> inline
void        AllocatorBase_Eastl<ALLOC_NMSP>::deallocate(void* p, size_t n)
{
    return sCast<Allocator_Nmsp&>(*this).free(p, n);
}

template<class ALLOC_NMSP> inline
const char* AllocatorBase_Eastl<ALLOC_NMSP>::get_name() const
{
    return mpName;
}

template<class ALLOC_NMSP> inline
void        AllocatorBase_Eastl<ALLOC_NMSP>::set_name(const char* pName)
{
    #if EASTL_NAME_ENABLED
    mpName = pName;
    #endif
}

template<class ALLOC_NMSP> inline
bool operator==(const AllocatorBase_Eastl<ALLOC_NMSP>&, const AllocatorBase_Eastl<ALLOC_NMSP>&)
{
    return true; // All allocators are considered equal, as they merely use global new/delete.
}

template<class ALLOC_NMSP> inline
bool operator!=(const AllocatorBase_Eastl<ALLOC_NMSP>&, const AllocatorBase_Eastl<ALLOC_NMSP>&)
{
    return false; // All allocators are considered equal, as they merely use global new/delete.
}

#endif


}