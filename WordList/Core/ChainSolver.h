#pragma once
#include<string>
#include<vector>

struct Edge {
	std::string word;
	int code=0;
	int weight=0;
	int next=0;
};
struct WordMap {
	std::vector<Edge> toLast;
	std::vector<Edge> toFirst;
};

class ChainSolver
{
	private:
		int edge_code;//give evey edge a code to record used edge.
		int maxLen = 0;
		int tail = -1;
		bool isUsedEdge[256] = { false };
		bool isUsedPoint[26] = { false };
		bool isEnableLoop = false;
		std::vector<std::string> maxPath;
		WordMap map[26];

		int CreateMap(char* s ,bool isGetMaxChar);
		int Recursion(std::vector<std::string>& path, int length, int point);

	public:
		ChainSolver();
		int get_max_chain(char* input[], int num, char* result[],char head, char tail, bool isGetMaxChar, bool enable_loop);
};

