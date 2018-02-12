#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include "command.h"
#include "rshell.h"

using namespace std;

command::command(vector<string> v) {
	for (unsigned i = 0; i < v.size(); ++i) {
		cmds.push_back(v.at(i));
	}
}