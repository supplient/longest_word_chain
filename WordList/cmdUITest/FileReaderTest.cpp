#include "stdafx.h"
#include "CppUnitTest.h"
#include "../UIUtility/UIUtility.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace cmdUITest
{		
	TEST_CLASS(FileReaderTest)
	{
	public:
		TEST_METHOD(simple)
		{
			FileReader reader;
			char **word = reader.read("../testcase/simple.txt");
			unsigned int len = reader.getReadLen();
			Assert::AreEqual(len, (unsigned int)6);
			Assert::AreEqual(word[0], "hello");
			Assert::AreEqual(word[1], "world");
			Assert::AreEqual(word[2], "softw");
			Assert::AreEqual(word[3], "are");
			Assert::AreEqual(word[4], "eng");
			Assert::AreEqual(word[5], "neer");
		}

	};
}
