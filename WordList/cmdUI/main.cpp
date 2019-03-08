#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "CoreSetting.h"
#include "../UIUtility/UIUtility.h"

#include "../Core/Core.h"

using namespace std;
using namespace cmdUI;

int main(int argc, char * argv[]) {
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
	cout << "Input: " << endl;
	for (unsigned int i = 0; i < len; i++)
		cout << words[i] << '\t';
	cout << endl;

	// TODO check file validity

	// Call Core
	char** res = new char*[MAX_WORD_NUM+1];
	int res_len;
	if (setting.isMaxChar()) {
		res_len = Core::gen_chain_char(
			words, len, res, 
			setting.getHead(), setting.getTail(), 
			setting.isLoopEnable());
	}
	else if (setting.isMaxWord()) {
		res_len = Core::gen_chain_word(
			words, len, res,
			setting.getHead(), setting.getTail(),
			setting.isLoopEnable());
	}
	else {
		cerr << "Something wrong with setting." << endl;
		return -1;
	}

	// Output result
	string output_path = "../BIN/solution.txt";
	ofstream ofs(output_path);
	if (!ofs.is_open()) {
		cerr << "Open " + output_path + " failed." << endl;
		return -1;
	}
	cout << "Output: " << endl;
	for (int i = 0; i < res_len; i++) {
		ofs << res[i] << endl;
		cout << res[i] << '\t';
	}
	ofs.close();
	cout << endl;

	delete[] res;
	return 0;
}
