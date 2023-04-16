#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_MATH || NMSP_TEST_ALL_MODULE

#include <nmsp_math.h>

namespace nmsp {

class Test_Math : public UnitTest
{
public:
	void test()
	{
		//Vec3f a = Vec3f{};
		//a.x += 1;
		//_NMSP_LOG("a.x: {}", a.x);
		//Vec3f b;
		{
			Vec3f_T			a{1.1f, 1.2f, 1.3f};
			Glm_Vec3_T<f32> g{1.1f, 1.2f, 1.3f};

			_NMSP_DUMP_VAR(sizeof(Vec3f_T));
			_NMSP_LOG("sizeof {}", sizeof(Glm_Vec3_T<f32>));
			auto j = a.sqrMagnitude(); NMSP_UNUSED(j);
			
			Vec3d_T			d3{1.1, 1.2, 1.3};
			auto crs = d3.cross(d3); NMSP_UNUSED(crs);

			_NMSP_LOG("Vec3: {}", d3);

			#if 1
			auto ret = a.dot(a);
			_NMSP_LOG("auto ret = a.dot(a); ret: {}", ret);
			Vec3_Basic_Data_Glm<float> x;
			x.data;

			auto f3 = Vec3f_T::s_cast(d3);
			//auto f2 = f3.toVec2();

			//_NMSP_DUMP_VAR(f2);
			_NMSP_DUMP_VAR(f3);

			NMSP_TEST_CHECK(a.dot(a) == glm::dot(g, g));

			#else
			Vec3_Basic_T<float> aa;
			Vec3_Basic_T<float> bb;

			//glm::dot(static_cast<Glm_Vec3<float> >(aa), static_cast<Glm_Vec3<float> >(bb) );
				
			#endif // 0

			

			/*Vec3_Basic_T<float> aa;
			Glm_Vec3<float> b = aa;
			b.data;
			b.x += 1;
			b.x += 1;*/

		}
		{
			Vec2f_T f4;
			Vec2f_T f4_2{ 1.0, 2.0 };
			Vec2f_T f4_3{ Tuple2f_T {1.0, 2.0} };
			_NMSP_DUMP_VAR(f4_2);
		}

		{
			Vec4d_T d4_2{ 1.0, 2.0, 3.0, 4.0 };
			Vec4f_T f4_3{ Tuple4f_T {1.0, 2.0, 3.0, 4.0} };
			Vec4f_T f4 = Vec4f_T::s_cast(d4_2);

			_NMSP_DUMP_VAR(d4_2);
		}

		{
			Glm_Vec4_SIMD_T<f32> gv4;
			gv4[0];

			Vec4f_T v4t;
			v4t[0];
			auto v4t2 = v4t;
			NMSP_TEST_CHECK(v4t2 == v4t);
			NMSP_TEST_CHECK(Math::equals(v4t2, v4t));

			
			//auto s = Math::epsilon<float>()();
			//_NMSP_DUMP_VAR(Math::Epsilon<float>()());
		}

		//a.data
		//b = a + Vec3f{};
		nmsp::Tuple3_T<float> aa;

		nmsp::Tuple3_T<float> bb;

		aa.setAll(2.0);
		bb = aa;

		Tuple3f_T cc;
		cc.setAll(4);

		//_NMSP_LOG("sizeof Vec3f: {}", sizeof(a));
		//_NMSP_LOG("sizeof Vec3f_SSE: {}", sizeof(a));
		
		
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

void test_nmsp_vec3()
{
	Vec3f_T	a{1.1f, 1.2f, 1.3f};
	volatile auto ret = a.dot(a); NMSP_UNUSED(ret);
	
}

void test_glm_vec3()
{
	Glm_Vec3_T<f32> g{1.1f, 1.2f, 1.3f};
	volatile auto ret = glm::dot(g, g); NMSP_UNUSED(ret);
}

NMSP_REGISTER_UNIT_TEST(test_nmsp_vec3);
NMSP_REGISTER_UNIT_TEST(test_glm_vec3);


}

void test_Math()
{
	_NMSP_PROFILE_SECTION("test_Math");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Math, test());
}


#endif // NMSP_TEST_MODULE_STL



