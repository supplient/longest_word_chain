#include "stdafx.h"
#include "CppUnitTest.h"

#include "testutil.h"
#include "../Core/Core.h"

#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace CoreTest
{		
	TEST_CLASS(only_w_normal) {
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



	TEST_CLASS(only_w_boundary)
	{
	public:
		TEST_METHOD(empty_words) {
			char* words[1];
			char* res[1];

			testRight(words, 0, res, 0);
		}

		TEST_METHOD(one_alpha) {
			char* words[3] = {
				"a",
				"acd",
				"d"
			};
			char* res[3] = {
				"a",
				"acd",
				"d"
			};

			testRight(words, 3, res, 3);
		}

		TEST_METHOD(no_chain) {
			char* words[3] = {
				"abcd",
				"bcde",
				"cdef"
			};
			vector<char**> res;

			testRightMulti(words, 3, res, 0);
		}

		TEST_METHOD(multi_occur) {
			char* words[] = {
				"apple",
				"apple",
				"apple",
				"egg",
				"egg",
				"egg",
				"egg",
				"egg",
				"green",
				"green",
				"egfc",
				"cakes",
				"cakes",
				"singl"
			};
			char* res[] = {
				"apple",
				"egfc",
				"cakes",
				"singl"
			};

			testRight(words, 14, res, 4);
		}

		TEST_METHOD(self_loop) {
			// NOTE this may be invalid, need concern
			char* words[] = {
				"hoh",
				"head",
				"dcad",
				"dhm",
				"dca",
				"a",
				"am",
				"mcmkm"
			};
			char* res[] = {
				"hoh",
				"head",
				"dcad",
				"dca",
				"a",
				"am",
				"mcmkm"
			};

			testRight(words, 8, res, 7);
		}

		TEST_METHOD(multi_chain) {
			char* words[] = {
				"abc",
				"acc",
				"cbd",
				"dak",
				"kf",
				"kg"
			};
			char* c_res[4][4] = {
			{"abc", "cbd", "dak", "kf"},
			{"acc", "cbd", "dak", "kf"},
			{"abc", "cbd", "dak", "kg"},
			{"acc", "cbd", "dak", "kg"},
			};
			vector<char**> res;
			for (int i = 0; i < 4; i++)
				res.push_back(c_res[i]);

			testRightMulti(words, 6, res, 4);
		}

	};
}