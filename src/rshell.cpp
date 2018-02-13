#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stack>
#include <queue>
#include "rshell.h"
#include "Command.h"

void rshell::execute() {
	string arguments;
	vector<string> userArgs;
	// stack<Base*> commands; // used for building tree
	stack<string> connectors; // used for building tree
	queue<Base*> output;

	cout << "$ ";
	getline(cin, arguments); // ex. arguments = "ls -a; touch hello.cpp"

	int argSize = arguments.size();
	char * cstr = new char[argSize + 1];
	strcpy(cstr, arguments.c_str()); // cstr contains the c string of arguments string
	char * token = strtok(cstr, " ");

	// push arguments passed in separated by a space into userArgs vector
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
	// for (unsigned i = 0; i < userArgs.size(); ++i) {
	// 	cout << userArgs.at(i) << endl;
	// }
	// cout << endl;

	vector<string> temp; // used to instantiate command objects
	// SHUNTING YARD ALGORITHM??
	for (unsigned i = 0; i < userArgs.size(); ++i) {
		string element = userArgs.at(i);
		if (!isConnector(element)) { // if it's a command, keep pushing into temp vector
			temp.push_back(element);
		}
		else { // if connector, push to stack
			output.push(new Command(temp)); // construct new command object and push to output queue
			temp.clear(); // reset temp vector

			connectors.push(element);
		}
	}
	// account for the last set of commands in userArgs
	output.push(new Command(temp));
	temp.clear();

	while (!connectors.empty()) {
		output.push(chooseConnector(connectors.top()));
		connectors.pop();
	}

	// CHECK POSTFIX NOTATION (debugging purposes)
	printBaseQueue(output);

	delete[] cstr;
}

bool rshell::isConnector(string argument) {
	if (argument == "&&" || argument == "||" || argument == ";") {
		return true;
	}
	return false;
}

Base* rshell::chooseConnector(string symbol) {
	if (symbol == "&&") {
		return new andConnect();
	}
	else if (symbol == "||") {
		return new orConnect();
	}
	return new semicol();
}

void rshell::printBaseQueue(queue<Base*> q) {
	while (!q.empty()) {
		cout << q.front()->element() << endl;
		q.pop();
	}
}