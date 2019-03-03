#pragma once
#include <string>

struct CoreSetting {
public:
	std::string filename;
	bool max_word = false, max_char = false;
	char head = 0, tail = 0;
	bool enable_loop = false;

	void parseFromArgc(int argc, char *argv[]);
};