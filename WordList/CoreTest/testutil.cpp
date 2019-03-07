#include "stdafx.h"
#include "CppUnitTest.h"

#include "testutil.h"
#include "../Core/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

bool occur_in(char* str, char* target[], int tar_len) {
	for (int j = 0; j < tar_len; j++) {
		if (strcmp(str, target[j]) == 0)
			return true;
	}
	return false;
}

void testRight(char* words[], int words_len, char* res[], int res_len, 
					bool is_max_char,
					char head, char tail, bool enable_loop) {
	char** ret_res = new char*[words_len];
	int ret_len;

	if (is_max_char)
		ret_len = Core::gen_chain_char(words, words_len, ret_res, head, tail, enable_loop);
	else
		ret_len = Core::gen_chain_word(words, words_len, ret_res, head, tail, enable_loop);

	Assert::AreEqual(ret_len, res_len);
	
	for (int i = 0; i < res_len; i++) {
		if (enable_loop) {
			Assert::IsTrue(occur_in(ret_res[i], res, res_len));
		}
		else {
			Assert::AreEqual(0, strcmp(ret_res[i], res[i]));
		}
		delete[] ret_res[i];
	}
			
	delete[] ret_res;
}

void testRightMulti(char* words[], int words_len, vector<char**> res, vector<int> res_len,
						bool is_max_char,
						char head, char tail, bool enable_loop) {
	if (res.size() != res_len.size())
		throw string("res's size should equal with res_len's size");

	char** ret_res = new char*[words_len];
	int ret_len;

	if (is_max_char)
		ret_len = Core::gen_chain_char(words, words_len, ret_res, head, tail, enable_loop);
	else
		ret_len = Core::gen_chain_word(words, words_len, ret_res, head, tail, enable_loop);


	bool success = false;
	for (unsigned int i = 0; i < res.size(); i++) {
		if (ret_len != res_len[i])
			continue;

		char** sub_res = res[i];
		try {
			for (int j = 0; j < res_len[i]; j++) {
				if (enable_loop) {
					Assert::IsTrue(occur_in(ret_res[j], sub_res, res_len[i]));
				}
				else {
					Assert::AreEqual(0, strcmp(ret_res[j], sub_res[j]));
				}
			}
		}
		catch (...) {
			continue;
		}

		// If all pass the assert
		success = true;
		break;
	}


	Assert::IsTrue(success);

	for (int i = 0; i < ret_len; i++)
		delete[] ret_res[i];
	delete[] ret_res;
}
