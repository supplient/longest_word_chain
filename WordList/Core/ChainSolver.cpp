#include "stdafx.h"
#include "ChainSolver.h"

#include <cstring>

ChainSolver::ChainSolver(void) {
	edge_code = 0;
}

int ChainSolver::CreateMap(char* c_s, bool isGetMaxChar) {
	std::string s(c_s);
	Edge edge;
	if(isGetMaxChar)
		edge = {s, edge_code++, 1, s[s.length() - 1] - 'a' };
	else
		edge = {s, edge_code++, (int)s.length(), s[s.length() - 1] - 'a' };
	map[s[0] - 'a'].toLast.push_back(edge);
	return 0;
}

int ChainSolver::Recursion(std::vector<std::string>& path, int length, int point) {
	if (map[point].toLast.empty()) {
		if (length > maxLen && (tail==-1 || point==tail)) {
			maxLen = length;
			maxPath.assign(path.begin(), path.end());
		}
		return 0; // NOTE this return value seems to be nonsense. ANS: changed to 0
	}
	for (auto iter : map[point].toLast) {
		path.push_back(iter.word);
		if (isUsedPoint[iter.next] == true && !isEnableLoop && point != iter.next) {
			//TODO: throw an EXCEPTION "words construct a loop!"
		}
		if (isUsedEdge[iter.code] == true) {
			path.pop_back();
			continue;
		}
		isUsedPoint[iter.next] = true;
		isUsedEdge[iter.code] = true;
		//NOTE: when needing max num: weight=1, when needing max char: weight = word's length.
		Recursion(path, length+iter.weight, iter.next);
		isUsedEdge[iter.code] = false;
		isUsedPoint[iter.next] = false;
		path.pop_back();
	}
	if (tail != -1 && point == tail && length > maxLen) {// When tail is requested, maxPath may appear when toLast is not null.
		maxLen = length;
		maxPath.assign(path.begin(), path.end());
	}
	return 0;
}

int ChainSolver::get_max_chain(char* input[], int num, char* result[], char head_input, char tail_input, bool isGetMaxChar,bool enable_loop) {
	int i; // NOTE: maxDegree seems to be an useless remaining variable? ANS: yes, it has been deleted.
	std::vector<std::string> path;
	
	if (tail_input != 0) {
		tail = tail_input - 'a';
	}

	isEnableLoop = enable_loop；

	for (i = 0; i < num; i++) {
		CreateMap(input[i], isGetMaxChar);
	}

	if (head_input != 0) {//Just DFS the request head char.
		isUsedPoint[head_input - 'a'] = true;
		Recursion(path, 0, head_input - 'a');
		isUsedPoint[head_input - 'a'] = false;
	}
	else {
		for (i = 0; i < 26; i++) {
			isUsedPoint[i] = true;
			Recursion(path, 0, i);
			isUsedPoint[i] = false;
		}
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
