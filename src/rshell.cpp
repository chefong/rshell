#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stack>
#include "rshell.h"
#include "command.h"

void rshell::execute() {
	string arguments;
	vector<string> userArgs;
	stack<Base*> commands; // used for building tree
	stack<Base*> connectors; // used for building tree

	cout << "$ ";
	getline(cin, arguments); // ex. arguments = "ls -a; touch hello.cpp"

	int argSize = arguments.size();
	char * cstr = new char[argSize + 1];
	strcpy(cstr, arguments.c_str()); // cstr contains the c string of arguments string
	char * token = strtok(cstr, " ");

	// push arguments passed in separated by a space into tempArgs vector
	while (token != NULL) {
		userArgs.push_back(token);
		token = strtok(NULL, " ");
	}

	// if string contains ";" at end, then remove and insert ";" in new index directly after
	for (vector<string>::iterator it = userArgs.begin(); it != userArgs.end(); ++it) {
		if (it->at(it->size() - 1) == ';') {
			it->pop_back(); // remove appended ";"
			it = userArgs.insert(it + 1, ";"); // insert ";" directly after
		}
	}

	// CHECK IF VECTOR MODIFIED CORRECTLY
	for (unsigned i = 0; i < userArgs.size(); ++i) {
		cout << userArgs.at(i) << endl;
	}

	vector<string> temp; // used to construct command objects
	for (unsigned i = 0; i < userArgs.size(); ++i) {
		if (!isConnector(userArgs.at(i))) { // if not a connector, keep pushing into temp vector
			temp.push_back(userArgs.at(i));
		}
		else {
			if (userArgs.at(i) == "&&") {
				connectors.push(new andConnect());
			}
			else if (userArgs.at(i) == "||") {
				connectors.push(new orConnect());
			}
			else {
				connectors.push(new semicol());
			}
			temp.clear(); // reset temp vector
		}
	}
	// at end of loop, commands and connectors stacks contain respective items

	delete[] cstr;
}

bool rshell::isConnector(string argument) {
	if (argument == "&&" || argument == "||" || argument == ";") {
		return true;
	}
	return false;
}