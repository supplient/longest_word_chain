// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "Core.h"
#include<algorithm>
#include<iterator>

int Core::CreateMap(std::string s) {
	if (s[0] == s[s.length() - 1])
		isSelfCircleUsed[s[0]]++;
	Edge edge = {s, 1, s[s.length() - 1] - 'a' };
	map[s[0] - 'a'].toLast.push_back(edge);
	return 0;
}

int Core::Recursion(std::vector<std::string>& path, int length, int point) {
	if (map[point].toLast.empty()) {
		if (length > maxLen) {
			maxLen = length;
			maxPath.swap(path);
		}
		else {
			path.pop_back();
		}
		return length;
	}
	for (auto iter : map[point].toLast) {
		path.push_back(iter.word);
		std::cout << point << " "<< iter.next << std::endl;
		if (iter.next == point) {
			if (isSelfCircleUsed[point] > 0)
				isSelfCircleUsed[point]--;
			else continue;
		}
		Recursion(path, ++length, iter.next);
		if(iter.next == point)
			isSelfCircleUsed[point]++;
	}
	return 0;
}

void Core::get_max_chain(std::vector<std::string>& input) {
	int i, maxDegree = 0;
	std::vector<std::string> path;
	for (i = 0; i < input.size(); i++) {
		CreateMap(input[i]);
	}
	for (i = 0; i < 26; i++) {
		Recursion(path, 0, i);
	}
	
	std::cout << maxPath.size() << std::endl;
	for (auto iter : maxPath) {
		std::cout << iter<<std::endl;
	}
}

int Core::gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	// TODO
	result[0] = (char*)"some";
	result[1] = (char*)"word";
	return 2;
}

int Core::gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	// TODO
	result[0] = (char*)"some";
	result[1] = (char*)"char";
	return 2;
}
