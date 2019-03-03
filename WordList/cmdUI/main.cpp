#include "pch.h"
#include <iostream>
#include <string>
#include <cctype>

#include "CoreSetting.h"
#include "FileReader.h"

using namespace std;
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
	FileReader reader;
	try {
		char **words = reader.read(setting.getFilename());
		unsigned int len = reader.getReadLen();
	}
	catch (string e) {
		cerr << e << endl;
		return -1;
	}

	// TODO check file validity

	return 0;
}
