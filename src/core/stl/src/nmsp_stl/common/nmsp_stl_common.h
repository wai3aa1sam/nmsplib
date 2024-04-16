#pragma once

#include <nmsp_core_base.h>

#include "nmsp_stl-config.h"
#include "nmsp_stl_traits.h"

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif

#if 0

	#if !EASTL_DLL // If building a regular library and not building EASTL as a DLL...
	// It is expected that the application define the following
	// versions of operator new for the application. Either that or the
	// user needs to override the implementation of the allocator class.
	inline void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) { return malloc(size); }
	inline void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
	{
		#if NMSP_OS_WINDOWS
		return _aligned_malloc(size, alignment);
		#else
		return std::aligned_alloc(alignment, size);
		#endif
	}
	#endif

#endif // 0

		#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	namespace nmsp {

	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	namespace nmsp {

	}

#elif NMSP_STL_BUILD_CONTAINER_EASTL


	namespace nmsp {
	
	template <class T>
	class InitList_Nmsp : public std::initializer_list<T>
	{
	public:
		using value_type      = T;
		using reference       = const T&;
		using const_reference = const T&;
		using size_type       = size_t;

		using iterator       = const T*;
		using const_iterator = const T*;

		using Base = std::initializer_list<T>;

	public:
		constexpr InitList_Nmsp() noexcept : Base() {}

		constexpr InitList_Nmsp(const Base& stdInitList) noexcept
			: Base(stdInitList)
		{}

	public:
		// std::initializer_list only has const ref
		//		value_type& operator[](std::size_t i)			{ checkBoundary(i); return *(begin() + i); }
		const	value_type& operator[](std::size_t i) const		{ checkBoundary(i); return *(begin() + i); }

	protected:
		void checkBoundary(std::size_t i) const
		{
			NMSP_CORE_ASSERT(i < size());
		}
	};
	
	template<class T>	using InitList_Impl = InitList_Nmsp<T>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif
    
namespace nmsp
{
	template<class T> using InitList_T = InitList_Impl<T>;
}