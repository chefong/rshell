#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <vector>
#include "Command.h"

using namespace std;

Command::Command(vector<string> v) {
	for (unsigned i = 0; i < v.size(); ++i) {
		cmds.push_back(v.at(i));
	}
}

bool Command::evaluate() {
	return true;
}

string Command::element() {
	string total;
	for (unsigned i = 0; i < cmds.size(); ++i) {
		total = total + cmds.at(i) + " ";
	}
	return total;
}