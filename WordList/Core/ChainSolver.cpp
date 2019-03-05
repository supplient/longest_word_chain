#include "stdafx.h"
#include "ChainSolver.h"

#include <cstring>

int ChainSolver::CreateMap(char* c_s) {
	std::string s(c_s);
	if (s[0] == s[s.length() - 1])
		isSelfCircleUsed[s[0]]++;
	Edge edge = {s, 1, s[s.length() - 1] - 'a' };
	map[s[0] - 'a'].toLast.push_back(edge);
	return 0;
}

int ChainSolver::Recursion(std::vector<std::string>& path, int length, int point) {
	if (map[point].toLast.empty()) {
		if (length > maxLen) {
			maxLen = length;
			maxPath.assign(path.begin(), path.end());
		}
		return length; // NOTE this return value seems to be nonsense.
	}
	for (auto iter : map[point].toLast) {
		path.push_back(iter.word);
		// std::cout << point << " "<< iter.next << std::endl;
		if (iter.next == point) {
			if (isSelfCircleUsed[point] > 0)
				isSelfCircleUsed[point]--;
			else continue;
		}
		Recursion(path, length+1, iter.next);
		if(iter.next == point)
			isSelfCircleUsed[point]++;
		path.pop_back();
	}
	return 0;
}

int ChainSolver::get_max_chain(char* input[], int num, char* result[]) {
	int i, maxDegree = 0; // NOTE: maxDegree seems to be an useless remaining variable?
	std::vector<std::string> path;

	for (i = 0; i < num; i++) {
		CreateMap(input[i]);
	}
	for (i = 0; i < 26; i++) {
		Recursion(path, 0, i);
	}
	
	i = 0;
	for (auto iter : maxPath) {
		char* new_str = new char[iter.length()+2];
		for (int j = 0; j < iter.length(); j++)
			new_str[j] = iter[j];
		new_str[iter.length()] = '\0';
		result[i] = new_str; // TODO release such memory
		i++;
	}

	return i;
}
