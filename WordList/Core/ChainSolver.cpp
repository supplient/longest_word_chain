#include "stdafx.h"
#include "ChainSolver.h"

#include <cstring>
#include<iterator>

ChainSolver::ChainSolver(void) {
}

unsigned int ChainSolver::APHash(std::string s) {
	unsigned int hash = 0;
	int i,k;
	for (i = 0,k=0; k<s.length(); i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (s[k++]) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (s[k++]) ^ (hash >> 5)));
		}
	}
	return (hash & 0x7FFFFFFF);
}

int ChainSolver::CreateMap(char* c_s, bool isGetMaxChar) {
	std::string s(c_s);
	Edge edge;
	unsigned int code = APHash(s);
	if (inputWord.find(code) != inputWord.end()) {// Repeat Word!
		// TODO: When Hash Collisions happen, code need change and insert.
		return 0;
	}
	inputWord.insert(std::pair<unsigned int, std::string>(code,s));
	isUsedEdge.insert(std::pair<unsigned int, bool>(code, false));
	if(!isGetMaxChar)
		edge = {s, code, 1, s[s.length() - 1] - 'a' };
	else
		edge = {s, code, (int)s.length(), s[s.length() - 1] - 'a' };
	map[s[0] - 'a'].toLast.push_back(edge);
	return 0;
}

int ChainSolver::Recursion(std::vector<std::string>& path, int length, int point) {
	for (auto iter : map[point].toLast) {
		if (isUsedEdge.find(iter.code)->second == true)
			continue;
		path.push_back(iter.word);
		if (isUsedPoint[iter.next] == true && !isEnableLoop && point != iter.next) {
			//TODO: throw an EXCEPTION "words construct a loop!"
		}
		isUsedPoint[iter.next] = true;
		isUsedEdge.find(iter.code)->second = true;
		//NOTE: when needing max num: weight=1, when needing max char: weight = word's length.
		Recursion(path, length+iter.weight, iter.next);
		isUsedEdge.find(iter.code)->second = false;
		isUsedPoint[iter.next] = false;
		path.pop_back();
	}
	if (length > maxLen && (tail == -1 || point == tail)) {
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

	isEnableLoop = enable_loop;

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

	if (maxPath.size() == 1) {
		maxPath.clear();
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