#include "pch.h"
#include <iostream>
#include <string>
#include <cctype>

#include "CoreSetting.h"
#include "FileReader.h"

#include "../Core/Core.h"

using namespace std;
using namespace cmdUI;

int main(int argc, char *argv[])
{
	// Parse Input
	CoreSetting setting;
	try {
		setting.parseFromArgc(argc, argv);
	}
	catch (string e) {
		cerr << e << endl;
		return -1;
	}

	// Read File
	char **words;
	unsigned int len;
	FileReader reader;
	try {
		words = reader.read(setting.getFilename());
		len = reader.getReadLen();
	}
	catch (string e) {
		cerr << e << endl;
		return -1;
	}

	// TODO check file validity

	// Call Core
	char* res[MAX_WORD_NUM];
	int res_len;
	if (setting.isMaxChar()) {
		res_len = Core::gen_chain_char(words, len, res, setting.getHead(), setting.getTail(), setting.isLoopEnable());
	}
	else if (setting.isMaxWord()) {
		res_len = Core::gen_chain_word(words, len, res, setting.getHead(), setting.getTail(), setting.isLoopEnable());
	}
	else {
		cerr << "Something wrong with setting." << endl;
		return -1;
	}

	// TODO Output result

	return 0;
}
