#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include <nmsp_os/atomic/nmspAtomic.h>

namespace nmsp {


class Test_Atomic : public UnitTest
{
public:
	void test()
	{
		{
			{ OsUtil::sleep_ms(10); auto n = OsTraits::logicalThreadCount(); NMSP_UNUSED(n); }
			{
				MutexProtected_T<Vector_T<int>> a;
				auto data = a.scopedULock();
			}

			{
				SMutexProtected_T<Vector_T<int>> a;
				auto data = a.scopedSLock();
			}

			{
				CondVarProtected_T<Vector_T<int>> s;
				auto data = s.scopedULock();
			}
			{
				SMtxCondVarProtected_T<Vector_T<int>> s;
				auto data = s.scopedSLock();
			}

			{
				class NT : public NativeThread_T
				{
				public:
					virtual ~NT() { join(); }
					virtual void* onRoutine() override
					{
						auto v = StrUtil::toTempStr((double)2450.0f);
						auto vw = StrUtil::toTempStrW((double)24560.0f);

						_NMSP_LOG("thread name: {}", v.data());

						return nullptr;
					}
				};
				NT nt;
				auto cd = NT::makeCDesc();
				//cd.name = "Render Thread";
				cd.affinityIdx = 10;
				nt.create(cd);
			}

			{
				AtmQueue_T<i64> q;
				q.push(10);

				enum class Prior
				{
					max = 0,
					high, mid, low,
					count = 4
				};

				AtmPrioityQueue_T<int, enumInt(Prior::count), Prior> apq;
				apq.push(10);

				int a;
				apq.try_pop(a);
				_NMSP_LOG("a: {}", a);
			}

			{
				OsUtil::sleep(1);

				Atm_T<int> a;
				_NMSP_DUMP_VAR(a.load());
			}
		}
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Atomic);


}


void test_Atomic()
{
	_NMSP_PROFILE_SECTION("test_Atomic");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Atomic, test());
}


#endif // NMSP_TEST_MODULE_STL



