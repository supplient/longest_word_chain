#pragma once
#include<iostream>

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

class CORE_API Core {
	public:
		static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
		static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};