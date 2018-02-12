#include <iostream>
#include "rshell.h"




void rshell::parseStrings() {
	string arguments;
	getline(cin, arguments); // ex. arguments = "ls -a; touch hello.cpp"

	int argSize = arguments.size();
	char * cstr = new char[argSize + 1];
	strcpy(cstr, arguments.c_str()); // cstr contains the c string of arguments string

	char * token = strtok(cstr, " ");

	// push arguments passed in separated by a space into cmds vector
	while (token != NULL) {
		//cmds.push_back(token);
		token = strtok(NULL, " ");
	}

	delete[] cstr;
}

void rshell::execute() {
	 // print "$ "
	parseStrings(); // fill cmds vector with tokenized argument strings
	stack<Base*> connectors;
	queue<Base*> output;

	// for (unsigned i = 0; i < cmds.size(); ++i) {
	// 	if (cmds.at(i) == "&&") {
	// 		connectors.push(new andConnect(cmds.at(i)));
	// 	}
	// 	else if (cmds.at(i) == "||") {
	// 		connectors.push(new orConnect(cmds.at(i)));
	// 	}
	// 	else if (cmds.at(i) == ";"){
	// 		connectors.push(new semicol(cmds.at(i)));
	// 	}
	// 	else {
	// 		output.push(new command(cmds.at(i)));
	// 	}
	// }

	for (unsigned i = 0; i < connectors.size(); ++i){
		output.push(connectors.top());
		connectors.pop(); 
	}


}