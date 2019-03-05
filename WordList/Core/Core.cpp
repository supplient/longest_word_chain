// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "Core.h"
#include "ChainSolver.h"

int Core::gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	ChainSolver solver;
	return solver.get_max_chain(words, len, result); // TODO more setting for head, tail, enable_loop
}

int Core::gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	// TODO
	result[0] = (char*)"some";
	result[1] = (char*)"char";
	return 2;
}
