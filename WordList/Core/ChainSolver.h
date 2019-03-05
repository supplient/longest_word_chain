#pragma once
#include<string>
#include<vector>

struct Edge {
	std::string word;
	int weight;
	int next;
};
struct WordMap {
	std::vector<Edge> toLast;
	std::vector<Edge> toFirst;
};

class ChainSolver
{
	private:
		int maxLen=0;
		int isSelfCircleUsed[26] = { 0 };
		std::vector<std::string> maxPath;
		WordMap map[26];

		int CreateMap(char* s ,bool isGetMaxChar);
		int Recursion(std::vector<std::string>& path, int length, int point);

	public:
		int get_max_chain(char* input[], int num, char* result[], bool isGetMaxChar);
};

