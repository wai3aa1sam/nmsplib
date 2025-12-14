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

		{
			/*{
			CondVar_T a; NMSP_UNUSED(a);
			a.broadcast();
			}*/


			{ auto ul = std::unique_lock<Mutex>{}; auto* mtx = ul.mutex(); NMSP_UNUSED(mtx); }

			MutexProtected_T<String> mp;
			{ auto mtx = mp.scopedLock(); NMSP_UNUSED(mtx); }
			{ auto mtx = mp.scopedLock(); NMSP_UNUSED(mtx);  mtx->size(); }

			{
				SharedMutexProtected_T<String> smp;
				{ auto mtx = smp.scopedLock(); NMSP_UNUSED(mtx); mtx->append(""); }
				{ auto mtx = smp.scopedReadLock(); NMSP_UNUSED(mtx); mtx->begin(); }
			}

			#if 1
			{
				CondMutexProtected_T<String, false> smp;
				{ auto mtx = smp.scopedLock(); NMSP_UNUSED(mtx); 
				mtx->append(""); }
				std::mutex m;
				std::unique_lock ul = std::unique_lock{m};
			}

			{
				CondMutexProtected_T<String, false> smp;
				{ smp.broadcast(); }
			}

			{
				CondMutexProtected_T<String, true> smp;
				{ smp.broadcast(); }
			}
			#endif // 1

			{
				using CondQueue = CondQueue_T<int, false, DefaultDeleter_T<int>, DefaultAllocator_T>;
				CondQueue cq;

				cq.append(makeUPtr<int>(1));
				cq.append(makeUPtr<int>(2));

				cq.insert(makeUPtr<int>(3));

				NMSP_DUMP_VAR(*cq.waitHead());
				NMSP_DUMP_VAR(*cq.timedWaitHead(5));

				cq.insert(makeUPtr<int>(4));
				NMSP_DUMP_VAR(*cq.timedWaitHead(5));
				NMSP_DUMP_VAR(*cq.timedWaitHead(5));
			}

			#if 0
			{
				CondQueue_T<int> a;
				a.append(nullptr);
			}
			#endif // 0
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



