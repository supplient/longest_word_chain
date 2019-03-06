#pragma once
#include <string>

class PyramidGenerator
{
public:
	PyramidGenerator();
	~PyramidGenerator();

	void work();

	char** getWords() const {
		if (!m_worked)
			throw std::string("Not Worked.");
		return words;
	}

	int getWordLen() const{
		if (!m_worked)
			throw std::string("Not worked.");
		return word_len;
	}

	char** getRes() const {
		if (!m_worked)
			throw std::string("Not Worked.");
		return res;
	}

	int getResLen() const {
		if (!m_worked)
			throw std::string("Not worked.");
		return res_len;
	}

private:
	bool m_worked;

	char** words;
	int word_len;
	char** res;
	int res_len;
};

