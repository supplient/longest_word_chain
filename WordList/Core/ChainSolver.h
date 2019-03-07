#pragma once
#include<string>
#include<vector>
#include<unordered_map>

#define MAX_UNSIGNED_INT 4294967294

struct Edge {
	std::string word;
	unsigned int code;
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
		int maxLen = 0;
		int tail = -1;
		bool isUsedPoint[26] = { false };
		bool isEnableLoop = false;
		WordMap map[26];
		std::vector<std::string> maxPath;
		std::unordered_map<unsigned int, std::string> inputWord;
		std::unordered_map<unsigned int, bool> isUsedEdge;

		unsigned int APHash(std::string s);
		int CreateMap(char* s ,bool isGetMaxChar);
		int Recursion(std::vector<std::string>& path, int length, int point);

	public:
		ChainSolver();
		int get_max_chain(char* input[], int num, char* result[],char head, char tail, bool isGetMaxChar, bool enable_loop);
};

