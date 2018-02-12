#include <iostream>
#include <string>
#include <cstring>
#include "command.h"
#include "rshell.h"

using namespace std;

void command::parseStrings() {
	string arguments;

	rshell::printPrompt(); // calls rshell's printPrompt()
	getline(cin, arguments); // ex. arguments = "ls -a; touch hello.cpp"

	int argSize = arguments.size();
	char * cstr = new char[argSize + 1];
	strcpy(cstr, arguments.c_str()); // cstr contains the c string of arguments string

	char * token = strtok(cstr, " ");

	// push arguments passed in separated by a space into cmds vector
	while (token != NULL) {
		cmds.push_back(token);
		token = strtok(NULL, " ");
	}

	delete[] cstr;
}
