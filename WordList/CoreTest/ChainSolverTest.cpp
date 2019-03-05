#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Core/Core.h"
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace CoreTest
{		
	TEST_CLASS(ChainSolverTest)
	{
	private:
		void testRight(char* words[], int words_len, char* res[], int res_len, 
							char head=0, char tail=0, bool enable_loop=false) {
			char** ret_res = new char*[words_len];
			int ret_len = Core::gen_chain_word(words, words_len, ret_res, head, tail, enable_loop);

			Assert::AreEqual(ret_len, res_len);
			for (int i = 0; i < res_len; i++)
				Assert::AreEqual(0, strcmp(ret_res[i], res[i]));
		}

	public:
		
		TEST_METHOD(simple)
		{
			char* words[] = {
				"hello",
				"world",
				"ofk",
				"kw"
			};
			char* res[] = {
				"hello",
				"ofk",
				"kw",
				"world"
			};

			testRight(words, 4, res, 4);
		}

	};
}