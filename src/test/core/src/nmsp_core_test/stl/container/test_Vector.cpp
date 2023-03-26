#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#if 0
#pragma mark --- EASTL-Impl ---
#endif // 0
#if 1

#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>

template<class T, size_t N, bool bEnableOverflow = true>
struct EASTL_Vector
{
	using Type = eastl::fixed_vector<T, N, bEnableOverflow>;
};

template<class T>
struct EASTL_Vector<T, 0, true>
{
	using Type = eastl::vector<T>;
};

//==== EASTL ====

#if !EASTL_DLL // If building a regular library and not building EASTL as a DLL...
// It is expected that the application define the following
// versions of operator new for the application. Either that or the
// user needs to override the implementation of the allocator class.
inline void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) { return malloc(size); }
inline void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
	#if NMSP_OS_WINDOWS
	return _aligned_malloc(size, alignment);
	#else
	return std::aligned_alloc(alignment, size);
	#endif
}
#endif

#endif // 1

struct Test_Vector_Func
{
	constexpr static size_t N = 16 * 10;
	constexpr static size_t RATIO = 1;
	constexpr static size_t N_S = N / RATIO;

	template<class T, class VECTOR>
	static void push_back(VECTOR& vector)
	{
		for (size_t i = 0; i < N_S; ++i)
		{
			vector.push_back(T(i));
		}
	}

	template<class T, class VECTOR>
	static void resize(VECTOR& vector)
	{
		vector.resize(N_S);
	}

	template<class T, class VECTOR>
	static void emplace_back(VECTOR& vector)
	{
		for (size_t i = 0; i < N_S; ++i)
		{
			vector.emplace_back(i);
		}
	}

	template<class T, class VECTOR>
	static void operate(VECTOR& vector)
	{
		vector.resize(N_S);
		for (size_t i = 0; i < N_S; ++i) { vector[i] += i; }
	}

	template<class T, class VECTOR>
	static void custom1(VECTOR& vector)
	{
		for (size_t i = 0; i < N_S; ++i) { vector.emplace_back(T(i)); }
		vector.resize(0);
		for (size_t i = 0; i < N_S; ++i) { vector.resize(i); }
	}

	template<class T, class VECTOR>
	static void _on_test_all(VECTOR& vector)
	{
		_NMSP_PROFILE_SCOPED();

		auto& v_ = vector;
		for (size_t i = 0; i < N_S; i++)
		{
			auto value = T(i);
			v_.insert(v_.begin(), 25, value);
		}

		auto erase_it = v_.erase_unsorted(v_.begin() + 5);
		for (size_t i = 0; i < 1; i++)
		{
			erase_it = v_.erase_unsorted(erase_it);
		}

		for (size_t i = 0; i < N_S; i++)
		{
			auto value = T(i);
			v_.insert(v_.begin() + i, 25, value);
		}
	}

	template<class T, class VECTOR>
	static void _on_temp_test0(VECTOR& vector)
	{
		_NMSP_PROFILE_SECTION("_on_temp_test0");

		static constexpr size_t factor = 100;
		auto& v_ = vector;
		for (size_t i = 0; i < 10 * factor; i++)
		{
			auto value = T(i);
 			v_.emplace_back(value);
		}

		#if 0
		auto erase_it = v_.erase_last_unsorted(T(5));
		if (erase_it == v_.rend())
			return;
		for (size_t i = 0; i < 2 * factor; i++)
		{
			erase_it = v_.erase_last_unsorted(*erase_it);
			if (erase_it == v_.rend())
				return;
		}
		#endif // 0


	}
};


namespace nmsp {


template<class T, class TEST_VECTOR, class TEST_REF_VECTOR>
struct Test_Vector_Helper
{
	using TestType = TEST_VECTOR;
	using TestRefType = TEST_REF_VECTOR;

	static void test()
	{
		#if 1  // NMSP_TEST_FUNC
		#define NMSP_TEST_FUNC(test_name, func1, func2, ...)						\
	{																				\
		_NMSP_LOG("Testing {}\n", #test_name);										\
		TestType test;																\
		TestRefType testRef;														\
		{																			\
			func1(test);															\
		}																			\
		{																			\
			func2(testRef);															\
		}																			\
		bool isSuccess = test_correctness(test, testRef);							\
		_NMSP_LOG("{}: {}\n", #test_name, (isSuccess) ? "[ OK ]" : "[ FAIL ]");		\
	}																				\
//------------------------------------
		#define NMSP_TEST_FUNC_SAME(func, lambda, ...)				NMSP_TEST_FUNC(func, lambda, lambda)
		//--------------
		#endif // 1  // NMSP_TEST_FUNC

		NMSP_TEST_FUNC_SAME(push_back, Test_Vector_Func::push_back<T>);
		NMSP_TEST_FUNC_SAME(resize, Test_Vector_Func::resize<T>);
		NMSP_TEST_FUNC_SAME(operate, Test_Vector_Func::operate<T>);
		NMSP_TEST_FUNC_SAME(custom1, Test_Vector_Func::custom1<T>);

		#if 0
		#undef NMSP_TEST_FUNC
		#undef NMSP_TEST_FUNC_SAME
		#endif // 0

	}

	static bool test_correctness(const TestType& src, const TestRefType& dst)
	{
		#if 1
		if (!NMSP_TEST_CHECK_SLIENT(src.size() == dst.size())) { return false; }
		{
			size_t i = 0;
			for (auto& it : dst)
			{
				if (!NMSP_TEST_CHECK_SLIENT(src.at(i) == it))
				{
					_NMSP_LOG("FAILED: index: {}", i);
					return false;
				}
				++i;
			}
		}
		{
			#if 1
			size_t i = 0;
			for (auto& rit : src.revEach())
			{
				if (!NMSP_TEST_CHECK_SLIENT(rit == *(dst.rbegin() + i)))
				{
					_NMSP_LOG("FAILED: index: {}", i);
					return false;
				}
				++i;
			}
			#endif // 0

		}
		#endif // 0
		return true;
	}

};

class Test_Vector : public UnitTest_Base
{
	template <class U> using Compare_STD					= Test_Vector_Helper<U, Vector_T<U, 0>, std::vector<U>>;
	//template <class U, size_t N> using Compare_EASTL_T		= Test_Vector_Helper<U, Vector_T<U, N>, eastl::vector<U>>;
	//template <class U, size_t N> using Compare_EASTL_N_T	= Test_Vector_Helper<U, Vector_T<U, N>, eastl::fixed_vector<U, N>>;

	//template <class U> using Compare_EASTL		= Compare_EASTL_T<U, 100>;
	//template <class U> using Compare_EASTL_N	= Compare_EASTL_N_T<U, 100>;
public:
	void test()
	{
		#if 0
		NMSP_TEST_CASE(Compare_STD<TestMovableType>, test());
		//NMSP_TEST_CASE(Compare_EASTL<TestMovableType>, test());
		//NMSP_TEST_CASE(Compare_EASTL_N<TestMovableType>, test());
		#else
		temp_test<TestMovableType<>>();
		//temp_test<int>();

		#endif // 0
	}

	template<class T, class VECTOR>
	static void _on_temp_test(VECTOR& v_)
	{
		constexpr static size_t N		=  16 * 1000000;
		constexpr static size_t RATIO	=  100000;
		constexpr static size_t N_S		=  N / RATIO;
		for (size_t i = 0; i < N_S; i++)
		{
			auto value = T(i);
			v_.insert(v_.begin(), 25, value);
		}

		for (size_t i = 0; i < 50; i++)
		{
			//v_.erase_last_unsorted(T(i));
		}

		for (size_t i = 0; i < N_S; i++)
		{
			auto value = T(i);
			v_.insert(v_.begin() + i, 25, value);
		}
	}

	template<class T>
	static void temp_test()
	{
		constexpr size_t LOCAL = 0;
		using TestType		= nmsp::Vector_T<T, LOCAL>;
		using TestRefType	= EASTL_Vector<T, LOCAL>::Type;
		//using TestRefType = std::vector<T>;

		TestType v0;
		TestRefType v1;

		#if 1
		Test_Vector_Func::_on_test_all<T>(v0);
		Test_Vector_Func::_on_test_all<T>(v1);
		#else
		Test_Vector_Func::_on_temp_test0<T>(v0);
		Test_Vector_Func::_on_temp_test0<T>(v1);
		#endif // 0

		
		#if 1
		bool isSuccess = Test_Vector_Helper<T, TestType, TestRefType>::test_correctness(v0, v1);
		_NMSP_LOG("{}: {}\n", "temp_test", (isSuccess) ? "[ OK ]" : "[ FAIL ]");
		#endif // 0

	}

private:

};

}

void test_Vector()
{
	_NMSP_PROFILE_SECTION("test_Vector");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Vector, test());

	//using Type = int;
	//VectorAllocator_T<Type, 4> allocator;
	//auto* p = allocator.alloc(40);
	//allocator.free(p, 40);
	//_NMSP_LOG("allocator.s_kLocalSize: {}, allocator.s_kAlign: {}", allocator.s_kLocalSize, allocator.s_kAlign);


	_NMSP_PROFILE_FRAME();
}

#endif // NMSP_TEST_MODULE_STL

