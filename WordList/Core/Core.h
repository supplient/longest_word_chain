#pragma once
#include<iostream>
#include<string>
#include<vector>

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

namespace GET_CHAIN{
	struct Edge {
		std::string word;
		int weight;
		int next;
	};
	struct WordMap {
		std::vector<Edge> toLast;
		std::vector<Edge> toFirst;
	};

	class CORE_API Core {
		private:
			int MaxLen=0;
			bool isSelfCircleUsed[26] = { 0 };
			std::vector<std::string> MaxPath;
			WordMap map[26];
			int CreateMap(std::string s, int *degree);
			int Recursion(std::vector<std::string>& path, int length, int point);
		public:
			void get_max_chain(std::vector<std::string>& input);
			static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
			static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	};
}