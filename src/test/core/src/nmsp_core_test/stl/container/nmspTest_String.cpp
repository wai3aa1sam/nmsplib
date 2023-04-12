#include "nmsp_core_test/common/nmsp_core_test_common.h"


#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#include <nmsp_stl.h>

namespace nmsp {

//template<class STR>
class Test_String : public UnitTest
{
public:
	void test()
	{
		//String_T<int, 123> vector;

		//auto msg = fmtAs<String_T<char>>("hello world {}, {}, {}", 1, 2, "sad");
		//std::cout << msg;
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
//NMSP_REGISTER_UNIT_TEST_CLASS(Test_String, /*String_T*/);

}

void test_String()
{
	using namespace nmsp;
	NMSP_TEST_CASE(Test_String, test());
}

#endif // NMSP_TEST_MODULE_STL

