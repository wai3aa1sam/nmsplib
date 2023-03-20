#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

namespace nmsp {

class Test_Vector : public UnitTest_Base
{
public:
	void test()
	{
		Vector_T<int, 123> vector;

		int i = 10;
		float f = sCast<float>(i); (void)f;


	}


private:

};

}

void test_Vector()
{
	using namespace nmsp;
	NMSP_TEST_CASE(Test_Vector, test());

	using Type = int;
	VectorAllocator_T<Type, 4> allocator;
	auto* p = allocator.alloc(40);
	allocator.free(p, 40);
	_NMSP_LOG("allocator.s_kLocalSize: {}, allocator.s_kAlign: {}", allocator.s_kLocalSize, allocator.s_kAlign);

}

#endif // NMSP_TEST_MODULE_STL

