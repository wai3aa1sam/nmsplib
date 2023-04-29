#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#include <nmsp_stl.h>

#include <nmsp_stl/utility/nmspFunctional.h>
#include <nmsp_stl/string/nmspStrUtil.h>

//template <> 
//struct eastl::equal_to<nmsp::TestType>
//{ bool operator()(const nmsp::TestType& a, const nmsp::TestType& b) const { return &a == &b; } };
//
//
//template <> 
//struct eastl::hash<nmsp::TestType>
//{ size_t operator()(nmsp::TestType val) const { return reinterpret_cast<intptr_t>(&val); } };

template <> 
struct ::nmsp::EqualTo<::nmsp::TestType>
{ bool operator()(const ::nmsp::TestType& a, const ::nmsp::TestType& b) const { return &a == &b; } };

template <> 
struct ::nmsp::Hash<::nmsp::TestType>
{ size_t operator()(::nmsp::TestType val) const { return reinterpret_cast<intptr_t>(&val); } };


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
			#if 0
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

class Test_Vector : public UnitTest
{
	template <class U> using Compare_STD = Test_Vector_Helper<U, Vector_T<U, 0>, std::vector<U>>;
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
		//temp_test<TestMovableType<>>();
		//temp_test<int>();

		Vector_T<int>		vec = { {1, 2, 3} };
		Vector_T<int>		vec2 = vec;

		for (auto& v : vec2)
		{
			_NMSP_LOG("{}", v);
		}

		StringT str;
		str.append("asdasdas");
		_NMSP_LOG("{}", str.data());

		{ Set_T<int> a; a.emplace(1); }
		{ Map_T<int, float> a; a.emplace(1, 5.0f); }

		{ VectorMap_T<int, int> a; a.insert({1, 1}); }
		//{ Map_T<int, int> a; a.emplace(Pair<int, int>{1, 1}); }
		{ UnorderedMap_T<int, const char*> a; a.insert(makePair(1, "1")); }
		{ int i = 0; const char* ch = "1"; UnorderedMap_T< const char*, int> a; a.insert(makePair(ch, i)); }
		{ auto tt = TestType(); UnorderedMap_T<TestType, const char*> a; a.emplace(move(tt), "1"); }
		{ auto tt = TestType(); UnorderedMap_T<TestType, const char*> a; a.emplace(move(tt), "1"); }
		{ auto tt = TestType(); UnorderedMap_T<TestType, const char*> a; a.emplace(move(tt), "1"); }

		{ auto tt = TestType(); StringMap_T<TestType> a; a.insert("123", move(tt)); }
		//{ auto tt = TestType(); StringMap_T<TestType> a; a.emplace("123", move(tt)); }
		//{ auto tt = TestType(); eastl::string_map<TestType> a; a.insert("123", move(tt)); }
		//_NMSP_LOG("n: {}", sizeof(StringA_T<0, DefaultAllocator>));
		{ StringA_T<12> tmp; tmp.append("!23"); }
		{ TempStringA_T<> tmp; tmp.append("!23"); }
		
		{ Opt_T<int> a; a.has_value(); }

		//{ Span_T<int> sv; Vector_T<int, 10> vect{sv};  }
		{ StrViewA_T sv; StringA_T<> strs = sv;  }

		{ UPtr_T<int> up; up.reset(nmsp_new<int>()); }
		{ class TestRef : public RefCount_Base {}; SPtr_T<TestRef> sp; sp.reset(nmsp_new<TestRef>()); }

		{
			int* p = NMSP_NEW(p);
			NMSP_FREE(p);
			p = nullptr;
			p = new int;
			delete p;
		}

		{
			//std::string a;
			//std::string_view fmt = "Hello World {}";
			//fmt::vformat_to(std::back_inserter(a), fmt, fmt::make_format_args(123));
			//std::cout << a << "\n";
		}

		{
			constexpr int n = 2;
			using Type = int;
			Type buf[n];
			Type buf2[n];
			Type buf3[n];
			Type buf4[n];

			const Type* a = new Type;
			Type* b = new Type;
			*b = move(*a);

			Type* p	 = buf;	 NMSP_UNUSED(p);
			Type* p2 = buf2; NMSP_UNUSED(p2);
			Type* p3 = buf3; NMSP_UNUSED(p3);
			Type* p4 = buf4; NMSP_UNUSED(p4);

			memory_set(p, n, 1);
			//memset(p, 1, n * sizeof(Type));

			memory_copy(p2, p, n);
			memory_move(p3, p, n);

			Type* p3123 = p; NMSP_UNUSED(p3123);
		}

		#endif // 0
	}


	template<class T, class VECTOR>
	static void _on_temp_test(VECTOR& v_)
	{
		constexpr static size_t N = 16 * 1000000;
		constexpr static size_t RATIO = 100000;
		constexpr static size_t N_S = N / RATIO;
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
		using TestType = nmsp::Vector_T<T, LOCAL>;
		using TestRefType = EASTL_Vector<T, LOCAL>::Type;
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

	virtual void onSetup() override
	{
	}

	virtual void onTest() override
	{

	}

	virtual void onBenchmark() override
	{
		
	}

private:

};
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Vector);


//void test_memory_copy()
//{
//	using Type = size_t;
//	int n = 100;
//	Type* p;	NMSP_ALLOC_T(p,	 n);
//	Type* p1;	NMSP_ALLOC_T(p1, n);
//	memory_copy(p, p1, n);
//}
//NMSP_REGISTER_UNIT_TEST(test_memory_copy);
//
//void test_memcpy()
//{
//	using Type = size_t;
//	int n = 100;
//	Type* p;	NMSP_ALLOC_T(p,	 n);
//	Type* p1;	NMSP_ALLOC_T(p1, n);
//	memcpy(p, p1, n * sizeof(Type));
//}
//NMSP_REGISTER_UNIT_TEST(test_memcpy);

}


void test_Vector()
{
	_NMSP_PROFILE_SECTION("test_Vector");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Vector, test());


}


#endif // NMSP_TEST_MODULE_STL



