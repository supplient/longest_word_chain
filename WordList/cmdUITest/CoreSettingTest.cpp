#include "stdafx.h"
#include "CppUnitTest.h"
#include "../cmdUI/CoreSetting.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace cmdUI;

namespace cmdUITest
{		
	TEST_CLASS(CoreSettingTest)
	{
	public:
		char *filename = "somefile.txt";
		
		TEST_METHOD(right_standard)
		{
			CoreSetting setting;
			char* argv[] = { 
				"name", 
				"-w", filename,
				"-r",
				"-h", "a",
				"-t", "g"
			};
			setting.parseFromArgc(8, argv);
			Assert::IsTrue(setting.isMaxWord());
			Assert::AreEqual(setting.getFilename(), string(filename));
			Assert::AreEqual(setting.getHead(), 'a');
			Assert::AreEqual(setting.getTail(), 'g');
			Assert::IsTrue(setting.isLoopEnable());
		}

		void testError(int argn, char* argv[]) {
			CoreSetting setting;

			bool has_error = false;
			try {
				setting.parseFromArgc(argn, argv);
			}
			catch (string e) {
				has_error = true;
			}

			Assert::IsTrue(has_error);
		}

		TEST_METHOD(error_no_wc) {
			char* argv[] = { "name" , "-h", "a", "-t", "c" };
			testError(5, argv);
		}

		TEST_METHOD(error_both_wc) {
			char* argv[] = { "name", "-w", filename, "-c", filename };
			testError(5, argv);
		}

		TEST_METHOD(error_wc_not_set) {
			char* argv[] = { "name", "-w" };
			testError(2, argv);
		}

		TEST_METHOD(error_h_not_set) {
			char* argv[] = { "name", "-h", "-w", filename };
			testError(4, argv);
		}

		TEST_METHOD(error_t_not_set) {
			char* argv[] = { "name", "-t", "-w", filename };
			testError(4, argv);
		}

		TEST_METHOD(error_multi_w) {
			char* argv[] = { "name", "-w", filename, "-w", filename };
			testError(5, argv);
		}

		TEST_METHOD(error_multi_h) {
			char* argv[] = { "name", "-h", "a", "-h", "b", "-w", filename };
			testError(7, argv);
		}

		TEST_METHOD(error_invalid_arg) {
			char* argv[] = { "name", "-g", "surprise" };
			testError(3, argv);
		}

	};
}