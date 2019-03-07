#pragma once

#include <vector>
#include <string>

void testRight(char* words[], int words_len, char* res[], int res_len, 
	bool is_max_char = false,
	char head = 0, char tail = 0, bool enable_loop = false);
void testRightMulti(char* words[], int words_len, std::vector<char**> res, std::vector<int> res_len,
	bool is_max_char = false,
	char head = 0, char tail = 0, bool enable_loop = false);
