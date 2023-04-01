#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp {

#if 0
#pragma mark --- Allocator_Eastl-Decl ---
#endif // 0
#if 1

template<class ALLOC_NMSP>
class Allocator_Eastl : public ALLOC_NMSP
{
public:
    using Base = ALLOC_NMSP;
public:
    EASTL_ALLOCATOR_EXPLICIT Allocator_Eastl(const char* pName = EASTL_NAME_VAL(EASTL_ALLOCATOR_DEFAULT_NAME));
    Allocator_Eastl(const Allocator_Eastl& x);
    Allocator_Eastl(const Allocator_Eastl& x, const char* pName);

    Allocator_Eastl& operator=(const Allocator_Eastl& x);

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
    using Base::alloc;
    //using Base::alloc_all;
    using Base::free;
    //using Base::free_all;
    using Base::is_owning;
};

#endif


#if 0
#pragma mark --- Allocator_Eastl-Impl ---
#endif // 0
#if 1

template<class ALLOC_NMSP> inline
Allocator_Eastl<ALLOC_NMSP>::Allocator_Eastl(const char* pName)
{
    #if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
    #endif
}

template<class ALLOC_NMSP> inline
Allocator_Eastl<ALLOC_NMSP>::Allocator_Eastl(const Allocator_Eastl& x)
{
    #if EASTL_NAME_ENABLED
    mpName = x.mpName;
    #endif
}

template<class ALLOC_NMSP> inline
Allocator_Eastl<ALLOC_NMSP>::Allocator_Eastl(const Allocator_Eastl& x, const char* pName)
{
    #if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
    #endif
}

template<class ALLOC_NMSP> inline
Allocator_Eastl<ALLOC_NMSP>& Allocator_Eastl<ALLOC_NMSP>::operator=(const Allocator_Eastl& x)
{
    #if EASTL_NAME_ENABLED
    mpName = x.mpName;
    #endif
    return *this;
}

template<class ALLOC_NMSP> inline
void*       Allocator_Eastl<ALLOC_NMSP>::allocate(size_t n, int flags)
{
    return alloc(n);
}

template<class ALLOC_NMSP> inline
void*       Allocator_Eastl<ALLOC_NMSP>::allocate(size_t n, size_t alignment, size_t offset, int flags)
{
    return alloc(n, alignment, offset);
}

template<class ALLOC_NMSP> inline
void        Allocator_Eastl<ALLOC_NMSP>::deallocate(void* p, size_t n)
{
    return free(p, n);
}

template<class ALLOC_NMSP> inline
const char* Allocator_Eastl<ALLOC_NMSP>::get_name() const
{
    return mpName;
}

template<class ALLOC_NMSP> inline
void        Allocator_Eastl<ALLOC_NMSP>::set_name(const char* pName)
{
    mpName = pName;
}

template<class ALLOC_NMSP> inline
bool operator==(const Allocator_Eastl<ALLOC_NMSP>&, const Allocator_Eastl<ALLOC_NMSP>&)
{
    return true; // All allocators are considered equal, as they merely use global new/delete.
}

template<class ALLOC_NMSP> inline
bool operator!=(const Allocator_Eastl<ALLOC_NMSP>&, const Allocator_Eastl<ALLOC_NMSP>&)
{
    return false; // All allocators are considered equal, as they merely use global new/delete.
}

#endif


}