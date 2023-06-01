#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#include <nmsp_stl/string/nmspLexer.h>
#include <nmsp_os/file/nmspPath.h>
#include <nmsp_os/file/nmspFile.h>
#include <nmsp_os/file/nmspMemMapFile.h>

#include <nmsp_stl/allocator/nmspLinearAllocator.h>

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

class TestAlloc
{
public:
	TestAlloc()
	{
		_NMSP_LOG("TestAlloc");
	}

	TestAlloc(int i)
	{
		_NMSP_LOG("TestAlloc(int)");
	}

	~TestAlloc()
	{
		_NMSP_LOG("~TestAlloc()");
	}
};

struct Data
{
	size_t a = 0;
};

class Tes0 : public Allocator_Base<Tes0>
{
public:

};

class Tes1 : public Allocator_Base<Tes1>
{
public:

	Data d;
};

class Test_Lexer : public UnitTest
{
public:
	void test()
	{
		{
			#if 0
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
			#endif // 0

			{
				{
					TestAlloc* p = new TestAlloc;
					delete p;
				}
				{
					TestAlloc* p = new TestAlloc[4];
					size_t* ps = reinCast<size_t*>(p);
					_NMSP_DUMP_VAR(ps[-1]);
					delete[] p;
				}
			}
			{
				auto up = makeUPtr<int>(5);

				_NMSP_DUMP_VAR(sizeof(Tes0));
				_NMSP_DUMP_VAR(sizeof(Tes1));
				_NMSP_DUMP_VAR(sizeof(LinearAllocator_T));

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



