#pragma once
#ifdef MY_DLL_API
#else
#define MY_DLL_API _declspec(dllimport)
#endif

#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define HEAD_CHAR_ERROR "Head char is not in a-z"
#define LOOP_ERROR "There exists loop in input, but we don't support -r"
#define TAIL_CHAR_ERROR "Tail char is not in a-z."
#define WORD_ILLEGAL "Some words in list has characters besides lower." 
#define MEMORY_ERROR "There occur some errors during visiting memory"

typedef struct {
	string word;
	int length;
}word_info;

class Core {

public://first step ,we need to remove same words
	int gen_chain_word(char *words[], int len, char *result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	// interface to mhx, return length of the final result list
	int max_chain_word(vector<string> word_list, vector<string> &result, char head, char tail, bool enable_loop);
	int max_chain_char(vector<string> word_list, vector<string> &result, char head, char tail, bool enable_loop);
	vector<string> array2string(char *words[], int len);
	int string2array(vector<string> string_list, char *words[]);
private:
	vector<word_info> word_list;// input word list
	vector<int> in_degree;
	vector<string> result_list_word;
	vector<string> result_list_char;
	map<int, vector<int>> digraph; //digraph
	map<char, vector<int>> head_char_list;// this word is head by char.
	map<char, vector<int>> tail_char_list;// this word is tail by char.

	void form_digraph(vector<string> word_list);// form a digraph to find max chain 
	bool has_loop();//judge this digraph has loop
	void dfs(int v_id, vector<bool> &visit, vector<int> &path, vector<int> &dist, bool longest_word);
	void remove_node(int v_id, vector<int > &degree);
	bool SPFA(char start_char, bool set_start, char end_set, bool set_end, bool longest_word);
	bool node_in_path(vector<int> path, int v_id, int now_id);
	void loop_max_chain(char start_char, bool set_start, char end_set, bool set_end, bool longest_word);
};
