#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#include <nmsp_stl/string/nmspLexer.h>
#include <nmsp_os/file/nmspPath.h>
#include <nmsp_os/file/nmspFile.h>
#include <nmsp_os/file/nmspMemMapFile.h>

namespace nmsp {

template<class FUNC>
void testFunc(FUNC&& func, char ch)
{
	//func(ch);
	nmsp::invoke(func, ch);
}

class TestFunc
{
public:
	static bool isAlpha(char ch)
	{
		return ch == '0';
	}

	bool isAlpha2(char ch)
	{
		return ch == '0';
	}

	template<class FUNC>
	void test(FUNC&& func, char ch)
	{
		nmsp::invoke(func, *this, ch);
	}
};

class Test_Lexer : public UnitTest
{
public:
	void test()
	{
		{
			MemMapFile_T mmf;
			mmf.open("line.shader");

			Lexer_T lexer;
			lexer.reset(mmf, StrViewA_T{ "line.shader" });
			{
				auto ret = true;
				do	
				{
					auto str = lexer.token().value();
					_NMSP_LOG("{}", lexer.token());
					ret = lexer.nextToken();
				} while (ret);

			}
			{
				char ch = 0;
				TestFunc tf;
				testFunc(TestFunc::isAlpha, ch);
				//testFunc(&TestFunc::isAlpha2, ch);
				tf.test(&TestFunc::isAlpha2, ch);
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Lexer);


}


void test_Lexer()
{
	_NMSP_PROFILE_SECTION("test_Lexer");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Lexer, test());
}


#endif // NMSP_TEST_MODULE_STL



