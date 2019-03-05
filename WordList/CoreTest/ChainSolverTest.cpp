#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Core/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace CoreTest
{		
	TEST_CLASS(ChainSolverTest)
	{
	public:
		
		TEST_METHOD(simple)
		{
			char* words[] = {
				"hello",
				"world",
				"ofk",
				"kw"
			};
			char* res[4];

			int res_len = Core::gen_chain_word(words, 4, res, 0, 0, 0);

			Assert::AreEqual(res_len, 4);
			Assert::AreEqual(res[0], "hello");
			Assert::AreEqual(res[1], "ofk");
			Assert::AreEqual(res[2], "kw");
			Assert::AreEqual(res[3], "world");
		}

	};
}