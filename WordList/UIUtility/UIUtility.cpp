// UIUtility.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "UIUtility.h"

#include <fstream>

using namespace std;

FileReader::FileReader()
{
}

char** FileReader::read(string filename) {
	ifstream ifs;
	ifs.open(filename, ifstream::in);
	if (!ifs.is_open()) {
		throw string("Open " + filename + " failed.");
	}
	
	StreamReader stream_reader;
	char** words = stream_reader.read(ifs);
	read_len = stream_reader.getReadLen();

	ifs.close();
	return words;
}

char ** StreamReader::read(istream & in)
{
	char **words = new char*[MAX_WORD_NUM];
	unsigned int wi = 0;
	char *temp = new char[MAX_WORD_LEN];
	unsigned int ti = 0;
	while (in.good()) {
		char c = in.get();

		if (isalpha(c)) {
			temp[ti] = tolower(c);
			ti++;
			if (ti >= MAX_WORD_LEN) {
				throw string("Too long word, longer than " + to_string(MAX_WORD_LEN));
			}
		}
		else {
			if (ti < 1) {
				// has no word
				continue;
			}

			// reach one word's end
			temp[ti] = '\0';
			words[wi] = temp;
			wi++;
			temp = new char[MAX_WORD_LEN];
			ti = 0;
			if (wi >= MAX_WORD_NUM) {
				throw string("Too many words, more than " + to_string(MAX_WORD_NUM));
			}
		}
	}
	if (ti >= 1) {
		// remain a word
		temp[ti] = '\0';
		words[wi] = temp;
		wi++;
	}

	read_len = wi;

	return words;
}
