#include "stdafx.h"
#include "ChainSolver.h"

#include <cstring>

int ChainSolver::CreateMap(char* c_s, bool isGetMaxChar) {
	std::string s(c_s);
	Edge edge;
	if (s[0] == s[s.length() - 1])
		isSelfCircleUsed[s[0]]++;
	if(isGetMaxChar)
		edge = {s, 1, s[s.length() - 1] - 'a' };
	else
		edge = {s, (int)s.length(), s[s.length() - 1] - 'a' };
	map[s[0] - 'a'].toLast.push_back(edge);
	return 0;
}

int ChainSolver::Recursion(std::vector<std::string>& path, int length, int point) {
	if (map[point].toLast.empty()) {
		if (length > maxLen) {
			maxLen = length;
			maxPath.assign(path.begin(), path.end());
		}
		return 0; // NOTE this return value seems to be nonsense. ANS: change to 0
	}
	for (auto iter : map[point].toLast) {
		path.push_back(iter.word);
		// std::cout << point << " "<< iter.next << std::endl;
		if (iter.next == point) {
			if (isSelfCircleUsed[point] > 0)
				isSelfCircleUsed[point]--;
			else continue;
		}
		//NOTE: when needing max num: weight=1, when needing max char: weight = word's length.
		Recursion(path, length+iter.weight, iter.next);
		if(iter.next == point)
			isSelfCircleUsed[point]++;
		path.pop_back();
	}
	return 0;
}

int ChainSolver::get_max_chain(char* input[], int num, char* result[], bool isGetMaxChar) {
	int i; // NOTE: maxDegree seems to be an useless remaining variable? ANS: yes, it has been deleted.
	std::vector<std::string> path;

	for (i = 0; i < num; i++) {
		CreateMap(input[i], isGetMaxChar);
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
