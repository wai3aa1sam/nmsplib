#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

namespace nmsp {

class Test_Vector : public UnitTestBase
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

}

#endif // NMSP_TEST_MODULE_STL

