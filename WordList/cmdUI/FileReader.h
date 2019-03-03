#pragma once
#include <string>

namespace cmdUI {
	const unsigned int MAX_WORD_NUM = 10005;
	const unsigned int MAX_WORD_LEN = 100;

	class FileReader
	{
	public:
		FileReader();
		char** read(std::string filename);
		unsigned int getReadLen()const { return read_len; }

	private:
		unsigned int read_len = 0;
	};
}
