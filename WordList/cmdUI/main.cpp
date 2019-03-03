#include "pch.h"
#include <iostream>
#include <string>

#include "CoreSetting.h"

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

	return 0;
}
