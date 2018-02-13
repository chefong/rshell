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

	vector<string> temp;
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
	// printBaseQueue(output);

	//BUILD THE TREE
	stack<Base*> tree; 
	Base* child1 = 0;
	Base* child2 = 0;
	while (!output.empty()) {
		if (isConnector(output.front()->element())) {
			child1 = tree.top();
			tree.pop();
			child2 = tree.top();
			tree.pop();
			output.front()->setLeft(child2);
			output.front()->setRight(child1);
			tree.push(output.front());
		}
		else {
			tree.push(output.front());
		}
		output.pop();
	}
	Base *root = tree.top();
	// cout << root->element() << endl;

	// CHECK IF TREE IS BUILT CORRECTLY
	cout << "Preorder traversal: ";
	printPreorder(root);
	cout << endl;
	cout << "Inorder traversal: ";
	printInorder(root);
	cout << endl;
	cout << "Postorder traversal: ";
	printPostorder(root);
	cout << endl;

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

void rshell::printPreorder(Base* current) {
	if (current == 0) {
		return;
	}
	cout << current->element() << " ";
	printPreorder(current->getLeft());
	printPreorder(current->getRight());
}

void rshell::printInorder(Base* current) {
	if (current == 0) {
		return;
	}
	printInorder(current->getLeft());
	cout << current->element() << " ";
	printInorder(current->getRight());
}

void rshell::printPostorder(Base* current) {
	if (current == 0) {
		return;
	}
	printPostorder(current->getLeft());
	printPostorder(current->getRight());
	cout << current->element() << " ";
}