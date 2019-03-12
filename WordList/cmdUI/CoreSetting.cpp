#include "pch.h"
#include "CoreSetting.h"

using namespace std;
using namespace cmdUI;

string w_c_set_error = "-w and -c cannot set at the same time.";
string w_c_follow_error = "When using -w or -c, you must specify a filepath followed.";
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
		string strarg(argv[i]);

		if (wait_filename) {
			filename = strarg;
			wait_filename = false;
			continue;
		}

		if (wait_head) {
			string temp = strarg;
			if (temp.length() != 1)
				throw h_t_follow_error;
			head = temp[0];
			if (head >= 'A' && head <= 'Z')
				head = head - ('A' - 'a');
			else if (head >= 'a' && head <= 'z')
				;
			else
				throw string("Invalid head: " + string(head, 1));
			wait_head = false;
			continue;
		}
		if (wait_tail) {
			string temp = strarg;
			if (temp.length() != 1)
				throw h_t_follow_error;
			tail = temp[0];
			if (tail >= 'A' && tail <= 'Z')
				tail = tail - ('A' - 'a');
			else if (tail >= 'a' && tail <= 'z')
				;
			else
				throw string("Invalid tail: " + string(tail, 1));
			wait_tail = false;
			continue;
		}

		if (strarg == "-w") {
			if (max_char)
				throw w_c_set_error;
			if (max_word)
				throw set_again_error;
			max_word = true;
			wait_filename = true;
		}
		else if (strarg == "-c") {
			if (max_word)
				throw w_c_set_error;
			if (max_char)
				throw set_again_error;
			max_char = true;
			wait_filename = true;
		}
		else if (strarg == "-h") {
			if (head != 0)
				throw set_again_error;
			wait_head = true;
		}
		else if (strarg == "-t") {
			if (tail != 0)
				throw set_again_error;
			wait_tail = true;
		}
		else if (strarg == "-r") {
			if (enable_loop)
				throw set_again_error;
			enable_loop = true;
		}
		else
		{
			throw string("Invalid argument: " + strarg);
		}
	}

	if (wait_filename)
		throw w_c_follow_error;
	if (wait_head || wait_tail)
		throw h_t_follow_error;

	if (!max_char && !max_word)
		throw string("Either -w or -c must be set.");
}
