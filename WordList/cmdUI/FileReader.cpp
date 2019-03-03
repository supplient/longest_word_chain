#include "pch.h"
#include "FileReader.h"

#include <fstream>

using namespace std;
using namespace cmdUI;

FileReader::FileReader()
{
}

char** FileReader::read(string filename) {
	ifstream ifs;
	ifs.open(filename, ifstream::in);
	if (!ifs.is_open()) {
		throw string("Open " + filename + " failed.");
	}

	char **words = new char*[MAX_WORD_NUM];
	unsigned int wi = 0;
	char *temp = new char[MAX_WORD_LEN];
	unsigned int ti = 0;
	while (ifs.good()) {
		char c = ifs.get();

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

	ifs.close();

	read_len = wi;
	return words;
}
