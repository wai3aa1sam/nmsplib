#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

namespace nmsp {

class Test_String : public UnitTest_Base
{
public:
	void test()
	{
		//String_T<int, 123> vector;

		//auto msg = fmtAs<String_T<char>>("hello world {}, {}, {}", 1, 2, "sad");
		//std::cout << msg;
	}


private:

};

}

void test_String()
{
	using namespace nmsp;
	NMSP_TEST_CASE(Test_String, test());
}

#endif // NMSP_TEST_MODULE_STL

