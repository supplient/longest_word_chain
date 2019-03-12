#include "stdafx.h"
#include "ChainSolver.h"

#include <cstring>
#include<iostream>

using namespace std;
std::string w_c_h_t_ChainLoop = "words construct a loop";
std::string create_map_error = "get unreasonable input words";
std::string para_tail_error = "get unreasonable tail parameter";
std::string para_head_error = "get unreasonable head parameter";
std::string para_loop_error = "get unreasonable enable_loop parameter";
std::string para_res_error = "get unreasonable res parameter";
std::string para_input_error = "get unreasonable input & num parameter";
std::string illegal_test = "you are making trouble out of nothing";

int ChainSolver::CreateMap(char *c_s, bool isGetMaxChar) {
	try {
		std::string s(c_s);
		Edge edge;
		int code = edgeCode++;
		if (inputWord.find(s) != inputWord.end()) {
			return 0;
		}
		inputWord.insert(std::pair<std::string, int>(s, code));
		isUsedEdge[code] = false;
		if (!isGetMaxChar)
			edge = { s, code, 1, s[s.length() - 1] - 'a' };
		else
			edge = { s, code, (int)s.length(), s[s.length() - 1] - 'a' };
		if (s[s.length() - 1] == s[0]) {
			map[s[0] - 'a'].toLast.insert(map[s[0] - 'a'].toLast.begin(), edge);
		}
		else {
			map[s[0] - 'a'].toLast.push_back(edge);
		}
	}
	catch (...) {
		throw create_map_error;
	}
	return 0;
}

int ChainSolver::Recursion(std::vector<std::string> &path, int length, int point) {
	int len = length;
	for (auto iter : map[point].toLast) {
		if (isUsedEdge[iter.code])
			continue;
		path.push_back(iter.word);
		if (iter.next == point) {
			len+=iter.weight;
			continue;
		}
		if (isUsedPoint[iter.next] && !isEnableLoop && point != iter.next) {
			throw w_c_h_t_ChainLoop;
		}
		isUsedPoint[iter.next] = true;
		isUsedEdge[iter.code] = true;
		//NOTE: when needing max num: weight=1, when needing max char: weight = word's length.
		Recursion(path, len + iter.weight, iter.next);

		isUsedEdge[iter.code] = false;
		isUsedPoint[iter.next] = false;
		path.pop_back();
	}
	if (len > maxLen && (tail == -1 || point == tail)) {
		maxLen = length;
		maxPath.assign(path.begin(), path.end());
	}
	for (auto iter : map[point].toLast) {
		if (iter.next == point) {
			isUsedEdge[iter.code] = false;
			path.pop_back();
		}
		else {
			break;
		}
	}
	return 0;
}

int ChainSolver::get_max_chain(char *input[], int num, char *result[], char head_input, char tail_input, bool isGetMaxChar,
	bool enable_loop) {
	int i; // NOTE: maxDegree seems to be an useless remaining variable? ANS: yes, it has been deleted.
	std::vector<std::string> path;
	if (num > 10000) {
		throw illegal_test;
	}

	if (tail_input != 0 && (tail_input < 'a' || tail_input > 'z')) {
		throw para_tail_error;
	}

	if (head_input != 0 && (head_input <'a' || head_input > 'z')) {
		throw para_head_error;
	}

	if (tail_input != 0) {
		tail = tail_input - 'a';
	}

	try {
		isEnableLoop = enable_loop;
	}
	catch(...){
		throw para_loop_error;
	}

	for (i = 0; i < num; i++) {
		try {
			CreateMap(input[i], isGetMaxChar);
		}
		catch (...) {
			throw para_input_error;
		}
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
	try {
		for (auto iter : maxPath) {
			char *new_str = new char[iter.length() + 2];
			// std::cout << iter << " ";
			for (unsigned int j = 0; j < iter.length(); j++)
				new_str[j] = iter[j];
			new_str[iter.length()] = '\0';
			result[i] = new_str; // TODO release such memory
			i++;
		}
	}
	catch (...) {
		throw para_res_error;
	}

	return i;
}