#pragma once

#ifdef UIUTILITY_EXPORTS
#define UIUTILITY_API __declspec(dllexport)
#else
#define UIUTILITY_API __declspec(dllimport)
#endif

#include <string>

const unsigned int MAX_WORD_NUM = 10005;
const unsigned int MAX_WORD_LEN = 200;

class UIUTILITY_API StreamReader
{
public:
	char** read(std::istream & in);
	unsigned int getReadLen()const { return read_len; }

private:
	unsigned int read_len = 0;
};

class UIUTILITY_API FileReader
{
public:
	FileReader();
	char** read(std::string filename);
	unsigned int getReadLen()const { return read_len; }

private:
	unsigned int read_len = 0;
};
