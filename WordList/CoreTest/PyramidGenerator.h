#pragma once
#include <string>

class PyramidGenerator
{
public:
	PyramidGenerator(unsigned int word_num, int target_depth=5);
	~PyramidGenerator();

	void work();

	char** getWords() const {
		if (!worked)
			throw std::string("Not Worked.");
		return words;
	}

	int getWordLen() const{
		if (!worked)
			throw std::string("Not worked.");
		return word_len;
	}

	char** getRes() const {
		if (!worked)
			throw std::string("Not Worked.");
		return res;
	}

	int getResLen() const {
		if (!worked)
			throw std::string("Not worked.");
		return res_len;
	}

private:
	bool worked;

	char** words;
	int word_len;
	char** res;
	int res_len;

	unsigned int word_num;
	int target_depth;
};

