#include "stdafx.h"
#include "CppUnitTest.h"

#include "testutil.h"
#include "PyramidGenerator.h"
#include "../Core/Core.h"

#include <fstream>
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

		TEST_METHOD(large) {
			PyramidGenerator gen(30, 5);
			gen.work();

			char** words = gen.getWords();
			int word_len = gen.getWordLen();
			char** res = gen.getRes();
			int res_len = gen.getResLen();

			// save the words and res into temp files for recurring.
			ofstream words_out("../testcase/words_temp.txt");
			for (int i = 0; i < word_len; i++) {
				words_out << words[i] << endl;
			}
			words_out.close();
			ofstream res_out("../testcase/res_temp.txt");
			for (int i = 0; i < res_len; i++) {
				res_out << res[i] << endl;
			}

			testRight(words, word_len, res, res_len);

			for (int i = 0; i < word_len; i++)
				delete[] words[i];
			delete[] words;
			delete[] res;
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
			vector<int> res_len;

			testRightMulti(words, 3, res, res_len);
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
			vector<int> res_len;
			for (int i = 0; i < 4; i++) {
				res.push_back(c_res[i]);
				res_len.push_back(4);
			}
			

			testRightMulti(words, 6, res, res_len);
		}

	};

	TEST_CLASS(only_c_normal) {
	public:
		TEST_METHOD(both_word_and_char_max) {
			char* words[] = {
				"ab",
				"bc",
				"ck",
				"cds",
				"slm"
			};
			char* res[] = {
				"ab",
				"bc",
				"cds",
				"slm"
			};

			testRight(words, 5, res, 4, true);
		}

		TEST_METHOD(with_same_word_num) {
			char* words[] = {
				"ab",
				"bffc",
				"cmd",
				"ef",
				"fg",
				"gh",
				"ij",
				"jk",
				"kl"
			};
			char* res[] = {
				"ab",
				"bffc",
				"cmd"
			};

			testRight(words, 9, res, 3, true);
		}

		TEST_METHOD(not_max_word_num) {
			char* words[] = {
				"destiny",
				"yellowandgreenandrez",
				"yb",
				"bc",
				"cz",
				"ze"
			};
			char* res[] = {
				"destiny",
				"yellowandgreenandrez",
				"ze"
			};

			testRight(words, 6, res, 3, true);
		}

		TEST_METHOD(multi_chain) {
			char* words[] = {
				"ab",
				"bkm",
				"bkn",
				"mz",
				"zt",
				"ncct",
				"tfd"
			};
			char* c_res[2][5] = {
			{"ab", "bkm", "mz", "zt", "tfd"},
			{"ab", "bkn", "ncct", "tfd"}
			};
			vector<char**> res;
			for (int i = 0; i < 2; i++) {
				res.push_back(c_res[i]);
			}
			vector<int> res_len;
			res_len.push_back(5);
			res_len.push_back(4);

			testRightMulti(words, 7, res, res_len, true);
		}
	};

	TEST_CLASS(mix_w_h_t) {
	public:
		TEST_METHOD(max_without_assign) {
			char* words[] = {
				"abc",
				"ckl",
				"lmj",
				"lme",
				"jhk"
			};
			char* res[] = {
				"abc",
				"ckl",
				"lmj",
				"jhk"
			};

			testRight(words, 5, res, 4, false, 'a', 'k');
		}

		TEST_METHOD(part_of_max) {
			char* words[] = {
				"abc",
				"ckl",
				"lmj",
				"lme",
				"jhk"
			};
			char* res[] = {
				"ckl",
				"lmj"
			};

			testRight(words, 5, res, 2, false, 'c', 'j');
		}

		TEST_METHOD(not_max_without_assign) {
			char* words[] = {
				"abc",
				"ckl",
				"lmj",
				"lme",
				"jhk"
			};
			char* res[] = {
				"ckl",
				"lme"
			};

			testRight(words, 5, res, 2, false, 'c', 'e');
		}

		TEST_METHOD(multi_after_assign) {
			char* words[] = {
				"ab",
				"bmk",
				"bnk",
				"kf"
			};
			char* c_res[2][3] = {
				{"ab", "bmk"},
				{"ab", "bnk"}
			};
			vector<char**> res;
			vector<int> res_len;
			for (int i = 0; i < 2; i++) {
				res_len.push_back(2);
				res.push_back(c_res[i]);
			}

			testRightMulti(words, 4, res, res_len, false, 'a', 'k');
		}
	};

	TEST_CLASS(mix_c_h_t) {
		TEST_METHOD(max_without_assign) {
			char* words[] = {
				"ab",
				"bc",
				"cd",
				"de",
				"ef",
				"bzzzzzzzzzzzzzzzzk",
				"kmt"
			};
			char* res[] = {
				"ab",
				"bzzzzzzzzzzzzzzzzk",
				"kmt"
			};

			testRight(words, 6, res, 3, true, 'a', 't');
		}

		TEST_METHOD(part_of_max) {
			char* words[] = {
				"ab",
				"bc",
				"cd",
				"de",
				"ef",
				"bzzzzzzzzzzzzzzzzk",
				"kmt"
			};
			char* res[] = {
				"bzzzzzzzzzzzzzzzzk",
				"kmt"
			};

			testRight(words, 6, res, 2, true, 'b', 't');
		}

		TEST_METHOD(not_max_without_assign) {
			char* words[] = {
				"ab",
				"zfjidjifewb",
				"bf"
			};
			char* res[] = {
				"ab",
				"bf"
			};

			testRight(words, 3, res, 2, true, 'a', 'f');
		}

		TEST_METHOD(multi_after_assign) {
			char* words[] = {
				"az",
				"zffffb",
				"zm",
				"mffb",
				"bf"
			};
			char* c_res[2][4] = {
				{"zffffb", "bf"},
				{"zm", "mffb", "bf"}
			};
			vector<char**> res;
			res.push_back(c_res[0]);
			res.push_back(c_res[1]);
			vector<int> res_len;
			res_len.push_back(2);
			res_len.push_back(3);

			testRightMulti(words, 4, res, res_len, true, 'z', 'f');
		}
	};
}