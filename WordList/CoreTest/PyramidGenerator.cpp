#include "stdafx.h"
#include "PyramidGenerator.h"

#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

PyramidGenerator::PyramidGenerator(unsigned int word_num, int target_depth)
	:word_num(word_num), target_depth(target_depth)
{
	words = NULL;
	word_len = 0;
	res = NULL;
	res_len = 0;

	worked = false;

	if (target_depth < 1)
		throw string("target_depth should larget than 0");
	if (target_depth > 20)
		throw string("target_depth should be less than 20");
	if ((int)word_num < target_depth)
		throw string("word_num should be larger than target_depth");
}


PyramidGenerator::~PyramidGenerator()
{
}

// TODO make the longest word chain with a very long word

typedef struct s_Node {
	struct s_Node(char alpha, struct s_Node* prev=NULL) :alpha(alpha), prev(prev) { ; }
	char alpha;
	struct s_Node* prev;
	vector<struct s_Node*> next;
} Node;

char* genRandomStr(default_random_engine &rand_eng, char head, char tail) {
	uniform_int_distribution<int> alpha_dist('a', 'z');
	uniform_int_distribution<int> len_dist(1, 10);

	int len = len_dist(rand_eng);
	char* res = new char[1 + len + 1 + 1];
	res[0] = head;
	for (int i = 1; i < len+1; i++) {
		char alpha = alpha_dist(rand_eng);
		res[i] = alpha;
	}
	res[len + 1] = tail;
	res[len + 2] = '\0';

	return res;
}

void PyramidGenerator::work()
{
	auto rand_seed = chrono::system_clock::now().time_since_epoch().count();
	ofstream seed_out("../testcase/seed_temp.txt");
	seed_out << rand_seed;
	seed_out.close();
	default_random_engine rand_eng((unsigned int)rand_seed);

	// Build alpha tree
	bool alpha_table[26] = { false };
	int level_expect_node_num = (26 - target_depth) / (target_depth - 1);

	uniform_int_distribution<int> sel_alpha_dist(0, 25);
	uniform_int_distribution<int> level_node_dist(1, level_expect_node_num);
	Node* root = new Node(0);

	vector<Node*> fate_nodes;
	vector<Node*> prev_nodes;
	
	fate_nodes.push_back(root);
	prev_nodes.push_back(root);
	for (int level = 0; level < target_depth; level++) {
		vector<Node*> now_nodes;
		int node_num = level_node_dist(rand_eng);
		
		// select alphas as the nodes in this level
		for (int i = 0; i < node_num; i++) {
			char sel_alpha = sel_alpha_dist(rand_eng);
			while (alpha_table[sel_alpha])
				sel_alpha = sel_alpha_dist(rand_eng);
			alpha_table[sel_alpha] = true;

			Node* node = new Node(sel_alpha + 'a');
			now_nodes.push_back(node);
		}

		// select one node as the fate node
		uniform_int_distribution<int> sel_fate_dist(0, node_num-1);
		int fate_index = sel_fate_dist(rand_eng);
		Node* prev_fate = fate_nodes.back();
		Node* now_fate = now_nodes[fate_index];
		now_fate->prev = prev_fate;
		prev_fate->next.push_back(now_fate);
		fate_nodes.push_back(now_fate);

		// randomly attach the rest nodes to the prev level's nodes
		uniform_int_distribution<int> sel_prev_dist(0, prev_nodes.size()-1);
		for (Node* node : now_nodes) {
			if (node->prev != NULL) 
				continue; // ignore fate node

			int prev_index = sel_prev_dist(rand_eng);
			Node* prev_node = prev_nodes[prev_index];

			prev_node->next.push_back(node);
			node->prev = prev_node;
		}

		// update prev_nodes
		prev_nodes.swap(now_nodes);
	}

	// Make the last level's fate node
	char final_alpha = sel_alpha_dist(rand_eng);
	while (alpha_table[final_alpha])
		final_alpha = sel_alpha_dist(rand_eng);
	Node* final_node = new Node(final_alpha + 'a');
	final_node->prev = fate_nodes.back();
	fate_nodes.back()->next.push_back(final_node);
	fate_nodes.push_back(final_node);

	// Generate words
	vector<char*> v_words;
	vector<char*> v_res;

	unsigned int node_expect_word_num = (word_num - target_depth) / ( 26 - target_depth );
	unsigned int min_node_expect_word_num = 1;
	if (node_expect_word_num / 2 > 1)
		min_node_expect_word_num = node_expect_word_num / 2;
	uniform_int_distribution<unsigned int> node_word_dist(min_node_expect_word_num, node_expect_word_num);

	vector<Node*> zero_nodes = root->next;
	vector<Node*> now_nodes;
	for (Node* node : zero_nodes)
		now_nodes.insert(now_nodes.end(), node->next.begin(), node->next.end());

	while (now_nodes.size() > 0) {
		for (Node* node : now_nodes) {
			char head_alpha = node->prev->alpha;
			char tail_alpha = node->alpha;

			auto iter = find(fate_nodes.begin(), fate_nodes.end(), node);
			if (iter != fate_nodes.end()) {
				// is a fate node
				char* str = genRandomStr(rand_eng, head_alpha, tail_alpha);
				v_words.push_back(str);
				v_res.push_back(str);
				continue;
			}

			// is not a fate node
			unsigned int word_num = node_word_dist(rand_eng);
			for (unsigned int i = 0; i < word_num; i++) {
				char* str = genRandomStr(rand_eng, head_alpha, tail_alpha);
				v_words.push_back(str);
			}
		}

		vector<Node*> prev_nodes;
		prev_nodes.swap(now_nodes);
		for(Node* node: prev_nodes)
			now_nodes.insert(now_nodes.end(), node->next.begin(), node->next.end());
	}

	words = new char*[v_words.size()+1];
	for (unsigned int i = 0; i < v_words.size(); i++)
		words[i] = v_words[i];
	word_len = v_words.size();
	
	res = new char*[v_res.size()+1];
	for (unsigned int i = 0; i < v_res.size(); i++)
		res[i] = v_res[i];
	res_len = target_depth;

	worked = true;

	// TODO Release memory
}
