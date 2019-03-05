// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "Core.h"
#include "ChainSolver.h"

int Core::gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	ChainSolver solver;
	return solver.get_max_chain(words, len, result, false); // TODO more setting for head, tail, enable_loop
}

int Core::gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	ChainSolver solver;
	return solver.get_max_chain(words, len, result, true); // TODO more setting for head, tail, enable_loop
}
