#include "stdafx.h"
#include "CppUnitTest.h"
#include "../cmdUI/CoreSetting.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace cmdUITest
{		
	TEST_CLASS(CoreSettingTest)
	{
	public:
		char *filename = "somefile.txt";
		
		TEST_METHOD(right_w)
		{
			CoreSetting setting;
			char* argv[3] = { "name", "-w", filename };
			setting.parseFromArgc(3, argv);
			Assert::IsTrue(setting.isMaxWord());
			Assert::AreEqual(setting.getFilename(), string(filename));
		}

	};
}