#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_MATH || NMSP_TEST_ALL_MODULE

#include <nmsp_math.h>

namespace nmsp {

class Test_Math : public UnitTest
{
public:
	void test()
	{
		math::Vec3f a = math::Vec3f{};
		a.x += 1;
		_NMSP_LOG("a.x: {}", a.x);

		nmsp_free(nmsp_alloc(10));
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Math);


}


void test_Math()
{
	_NMSP_PROFILE_SECTION("test_Math");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Math, test());
}


#endif // NMSP_TEST_MODULE_STL



