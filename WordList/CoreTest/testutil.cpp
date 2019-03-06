#include "stdafx.h"
#include "CppUnitTest.h"

#include "testutil.h"
#include "../Core/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

void testRight(char* words[], int words_len, char* res[], int res_len, 
					char head, char tail, bool enable_loop) {
	char** ret_res = new char*[words_len];
	int ret_len = Core::gen_chain_word(words, words_len, ret_res, head, tail, enable_loop);

	Assert::AreEqual(ret_len, res_len);
	for (int i = 0; i < res_len; i++) {
		Assert::AreEqual(0, strcmp(ret_res[i], res[i]));
		delete[] ret_res[i];
	}
			
	delete[] ret_res;
}

void testRightMulti(char* words[], int words_len, vector<char**> res, int res_len,
						char head, char tail, bool enable_loop) {
	char** ret_res = new char*[words_len];
	int ret_len = Core::gen_chain_word(words, words_len, ret_res, head, tail, enable_loop);

	Assert::AreEqual(ret_len, res_len);

	bool success = false;
	for (auto sub_res: res) {
		try {
			for (int j = 0; j < res_len; j++)
				Assert::AreEqual(0, strcmp(ret_res[j], sub_res[j]));
		}
		catch (...) {
			continue;
		}

		// If all pass the assert
		success = true;
		break;
	}

	Assert::IsTrue(success);
}
