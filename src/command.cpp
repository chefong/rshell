#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <vector>
#include "command.h"

using namespace std;

Command::Command(vector<string> v) {
	for (unsigned i = 0; i < v.size(); ++i) {
		cmds.push_back(v.at(i));
	}
}

bool Command::evaluate() {
	unsigned arrSize = cmds.size() + 1;
	char * args[arrSize]; // make a char pointer array of the same size as cmds vector

	// populate args array with commands in cmds vector
	for (unsigned i = 0; i < arrSize - 1; ++i) {
		args[i] = const_cast<char*>(cmds.at(i).c_str());
	}
	
	args[arrSize - 1] = NULL; // make last index NULL

	return true;
}

string Command::element() {
	string total;
	for (unsigned i = 0; i < cmds.size() - 1; ++i) {
		total = total + cmds.at(i) + " ";
	}
	total = total + cmds.at(cmds.size() - 1);
	return total;
}