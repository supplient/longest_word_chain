#include "pch.h"
#include "CoreSetting.h"

using namespace std;
using namespace cmdUI;

string w_c_set_error = "-w and -c cannot set at the same time.";
string w_c_follow_error = "When using -h or -t, you must specify a filepath followed.";
string h_t_follow_error = "When using -h or -t, you must specify one char followed.";
string set_again_error = "Any argument can only set by once.";

void CoreSetting::parseFromArgc(int argc, char * argv[])
{
	if (argc < 2){
		throw string("Too few arguments.");
	}

	bool wait_filename = false;
	bool wait_head = false, wait_tail = false;

	for (int i = 1; i < argc; i++){

		if (wait_filename) {
			filename = argv[i];
			wait_filename = false;
			continue;
		}

		if (wait_head) {
			string temp = argv[i];
			if (temp.length() != 1)
				throw h_t_follow_error;
			head = temp[0];
			wait_head = false;
		}
		if (wait_tail) {
			string temp = argv[i];
			if (temp.length() != 1)
				throw h_t_follow_error;
			tail = temp[0];
			wait_tail = false;
		}

		if (argv[i] == "-w") {
			if (max_char)
				throw w_c_set_error;
			if (max_word)
				throw set_again_error;
			max_word = true;
			wait_filename = true;
		}
		else if (argv[i] == "-c") {
			if (max_word)
				throw w_c_set_error;
			if (max_char)
				throw set_again_error;
			max_char = true;
			wait_filename = true;
		}
		else if (argv[i] == "-h") {
			if (head != 0)
				throw set_again_error;
			wait_head = true;
		}
		else if (argv[i] == "-t") {
			if (tail != 0)
				throw set_again_error;
			wait_tail = true;
		}
		else if (argv[i] == "-r") {
			if (enable_loop)
				throw set_again_error;
			enable_loop = true;
		}
		else
		{
			throw string("Invalid argument: " + string(argv[i]));
		}
	}

	if (wait_filename)
		throw w_c_follow_error;
	if (wait_head || wait_tail)
		throw h_t_follow_error;
}
