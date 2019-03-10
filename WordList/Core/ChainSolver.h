#pragma once
#include<string>
#include<vector>
#include<unordered_map>

struct Edge {
	std::string word;
	int code;
	int weight;
	int next;
};
struct WordMap {
	std::vector<Edge> toLast;
	std::vector<Edge> toFirst;
};

class ChainSolver {
private:
	int edgeCode = 0;
	int maxLen = 0;
	int tail = -1;
	bool isUsedPoint[26] = { false };
	bool isEnableLoop = false;
	WordMap map[26];
	std::unordered_map<std::string, int> inputWord;
	std::vector<std::string> maxPath;
	bool isUsedEdge[10005];

	int CreateMap(char *s, bool isGetMaxChar);

	int Recursion(std::vector<std::string> &path, int length, int point);

public:
	int get_max_chain(char *input[], int num, char *result[], char head, char tail, bool isGetMaxChar, bool enable_loop);
};
