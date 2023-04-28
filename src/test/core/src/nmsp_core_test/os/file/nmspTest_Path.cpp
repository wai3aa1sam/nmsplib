#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include "nmsp_os/file/nmspPath.h"
#include "nmsp_os/file/nmspDirectory.h"
#include "nmsp_os/file/nmspFile.h"


namespace nmsp {

class Test_Path : public UnitTest
{
public:
	void test()
	{
		{
			auto curdir = Path::getCurrentDir();
			_NMSP_DUMP_VAR(curdir);

			auto realpath = Path::realpath(".././../Text.h");
			_NMSP_DUMP_VAR(realpath);

			auto base = Path::basename(realpath);
			_NMSP_DUMP_VAR(base);

			#define NMSP_TEST_PATH_STATUS(path_) \
				{ \
					auto status = [](StrViewA_T path) -> StringT \
					{ \
						return \
							Path::isExist(path) ? \
							(Path::isDirectory(path) ? "dir" \
								: Path::isFile(path) ? "file" : "error") \
							: "not exist"; \
					}; \
					_NMSP_LOG("{} is {}", path_, status(path_)); \
				} \
				//---

			NMSP_TEST_PATH_STATUS("Release");
			NMSP_TEST_PATH_STATUS("ALL_BUILD.vcxproj.filters");
			NMSP_TEST_PATH_STATUS("xxx");

			File::rename("testFs.txt", "on9");
			File::rename("testFx.txt", "on9");
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Path);


}


void test_Path()
{
	_NMSP_PROFILE_SECTION("test_Path");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Path, test());
}


#endif // NMSP_TEST_MODULE_STL



