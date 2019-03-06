#include "stdafx.h"
#include "PyramidGenerator.h"


PyramidGenerator::PyramidGenerator()
{
	m_worked = false;
}


PyramidGenerator::~PyramidGenerator()
{
}

void PyramidGenerator::work()
{
	words = new char*[2];
	words[0] = new char[3];
	words[1] = new char[3];
	words[0][0] = 'a';
	words[0][1] = 'b';
	words[0][2] = '\0';
	words[1][0] = 'b';
	words[1][1] = 'c';
	words[1][2] = '\0';

	word_len = 2;

	res = new char*[2];
	res[0] = new char[3];
	res[1] = new char[3];
	res[0][0] = 'a';
	res[0][1] = 'b';
	res[0][2] = '\0';
	res[1][0] = 'b';
	res[1][1] = 'c';
	res[1][2] = '\0';

	res_len = 2;

	m_worked = true;
}
