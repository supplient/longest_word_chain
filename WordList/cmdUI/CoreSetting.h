#pragma once
#include <string>

class CoreSetting {
private:
	std::string filename;
	bool max_word = false, max_char = false;
	char head = 0, tail = 0;
	bool enable_loop = false;

public:
	void parseFromArgc(int argc, char *argv[]);

	std::string getFilename()const { return filename; }
	bool isMaxWord()const { return max_word; }
	bool isMaxChar()const { return max_char; }
	char getHead()const { return head; }
	char getTail()const { return tail; }
	bool isLoopEnable()const { return enable_loop; }
};