	#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stack>
#include <queue>
#include "rshell.h"
#include "command.h"

// This will be the function that main will run
void rshell::begin() {
	bool status = true;
	while (status) {
		execute();
	}
}

void rshell::execute() {
	string arguments;
	vector<string> userArgs;
	stack<string> connectors; // used for building tree
	queue<Base*> output;

	cout << "$ ";
	getline(cin, arguments); // ex. arguments = "ls -a; touch hello.cpp"

	// if arguments has '#' then cut it out
	if (arguments.find('#') != string::npos) {
		arguments = arguments.substr(0, arguments.find('#'));
		// cout << arguments << endl;
	}
	if (arguments.empty()) { // if string empty, do nothing
		return;
	}


	int argSize = arguments.size();
	char * cstr = new char[argSize + 1];
	strcpy(cstr, arguments.c_str()); // cstr contains the c string of arguments string
	char * token = strtok(cstr, " ");

	// push arguments passed in separated by a space into userArgs vector
	while (token != NULL) {
		userArgs.push_back(token);
		token = strtok(NULL, " ");
	}

	// printStringVector(userArgs);
	// cout << endl;

	// if string contains ";" at end, then remove and insert ";" in new index directly after
	for (vector<string>::iterator it = userArgs.begin(); it != userArgs.end(); ++it) {
		// cout << "Current word is " << *it << endl;
		// if (it->find("\"") != string::npos) {
		// 	cout << "found it" << endl;
		// }
		while (it->find("\"") != string::npos) {
			it->erase(it->find("\""), 1);
		}
		if (*it == "(" || *it == ")" || *it == "[" || *it == "]" || *it == "<" || *it == ">" || *it == ">>" || *it == "|") {
			// cout << "1" << endl;
			continue;
		}
		else if (it->at(it->size() - 1) == ';') {
			// cout << "2" << endl;
			it->pop_back(); // remove appended ";"
			it = userArgs.insert(it + 1, ";"); // insert ";" directly after
		}
		else if (it->at(0) == '(') {
			// cout << "3" << endl;
			// remove the '(' and insert it in vector index right before
			string sub = it->substr(1, it->size() - 1);
			*it = "(";
			it = userArgs.insert(it + 1, sub) - 1;
		}
		else if (it->find(")") != string::npos) {
			// cout << "4" << endl;
			// if (*it == ")") {
			// 	// cout << "continuing" << endl;
			// 	continue;
			// }
			// it->pop_back(); // remove appended ";"
			// it = userArgs.insert(it + 1, ")"); // insert ";" directly after
			// string sub = it->substr(0, it->size() - 1);
			int count = 0;
			for (unsigned i = 0; i < it->size(); ++i) { // count how many ')' there are
				if (it->at(i) == ')') {
					++count;
				}
			}

			*it = it->substr(0, it->find(")")); // substring until the first instance of ')'
			
			for (unsigned i = 0; i < count; ++i) {
				it = userArgs.insert(it + 1, ")");
			}
			// cout << "Index now contains " << *it << endl;
			// it = userArgs.insert(it + 1, ")") - 1;
		}
		else if (it->at(0) == '[') {
			// cout << "5" << endl;
			// remove the '(' and insert it in vector index right before
			string sub = it->substr(1, it->size() - 1);
			*it = "[";
			it = userArgs.insert(it + 1, sub) - 1;
		}
		else if (it->at(it->size() - 1) == ']') {
			// cout << "6" << endl;
			// if (*it == "]") {
			// 	// cout << "continuing" << endl;
			// 	continue;
			// }
			// it->pop_back(); // remove appended ";"
			// it = userArgs.insert(it + 1, ")"); // insert ";" directly after
			// string sub = it->substr(0, it->size() - 1);
			*it = it->substr(0, it->size() - 1);
			// cout << "Index now contains " << *it << endl;
			it = userArgs.insert(it + 1, "]") - 1;
		}
		// string word = *it;
		// for (unsigned i = 0; i < word.size(); ++i) {
		// 	if (word.at(i) == '(') {
		// 		string sub = word.substr(1, word.size() - 1);
		// 		*it = "(";
		// 		it = userArgs.insert(it + 1, sub);
		// 	}
		// }
	}
	// cout << "Here" << endl;
	// for (vector<string>::iterator it = userArgs.begin(); it != userArgs.end(); ++it) {
	// 	cout << *it << endl;
	// 	if (it->at(it->size() - 1) == ')') {
	// 		cout << "Doing something" << endl;
	// 		it->pop_back(); // remove appended ")"
	// 		it = userArgs.insert(it + 1, ")"); // insert ")" directly after
	// 	}
	// }
	// for (vector<string>::iterator it = userArgs.begin(); it != userArgs.end(); ++it) {
	// 	if (*it == "(") {
	// 		break;
	// 	}
	// 	else if (it->at(0) == '(') {
	// 		// remove the '(' and insert it in vector index right before
	// 		string sub = it->substr(1, it->size() - 1);
	// 		*it = "(";
	// 		it = userArgs.insert(it + 1, sub);
	// 	}
	// }
	if (isConnector(userArgs.at(userArgs.size() - 1))) {
		userArgs.pop_back(); // ls; -> ls
	}

	// CHECK IF VECTOR MODIFIED CORRECTLY
	printStringVector(userArgs);
	cout << endl;

	if (!isBalanced(userArgs)) {
		cout << "Parantheses not balanced" << endl;
		return;
	}
	// cout << "Expression is balanced" << endl;

	vector<string> temp;
	// SHUNTING YARD ALGORITHM??
	for (unsigned i = 0; i < userArgs.size(); ++i) {
		string element = userArgs.at(i);
		// cout << "Current element is '" << element << "'" << endl;
		if (!isConnector(element) && !isLeftBracket(element) && !isRightBracket(element)) { // if it's a command, keep pushing into temp vector
			// cout << "Pushing back '" << element << "' into temp vector" << endl;
			temp.push_back(element);
		}
		else if (isConnector(element)) { // if connector, push to stack
			if (!temp.empty()) {
				// cout << "Element is a connector (making new command object and pushing onto output queue)" << endl;
				output.push(new Command(temp)); // construct new command object and push to output queue
				temp.clear(); // reset temp vector
			}

			if (!connectors.empty()) {
				while ( !connectors.empty() && !isLeftBracket(connectors.top())) {
					// cout << "Checking special" << endl;
					output.push(chooseConnector(connectors.top()));
					connectors.pop();
				}
			}

			connectors.push(element);
		}
		else if (isLeftBracket(element)) {
			// cout << "Pushing '(' onto connectors stack" << endl;
			connectors.push(element);
		}
		else { // element is a right bracket
			// cout << "Element is a ')' (making new command object and pushing onto output queue)" << endl;
			if (!temp.empty()) {
				output.push(new Command(temp));
				temp.clear();
			}

			while (!isLeftBracket(connectors.top())) {
				// cout << "Pushing " << connectors.top() << " onto output queue" << endl;
				output.push(chooseConnector(connectors.top()));
				connectors.pop();
			}
			connectors.pop(); // pop the left bracket and discard it
		}
		// cout << endl;
	}

	// cout << "Printing queue before last commands" << endl;
 // 	printBaseQueue(output);

	// account for the last set of commands in userArgs
	if (!isRightBracket(userArgs.at(userArgs.size() - 1))) {
		// cout << "Making and pushing last command onto output queue" << endl;
		output.push(new Command(temp));
		temp.clear();
	}

	while (!connectors.empty()) {
		// cout << "Pushing " << connectors.top() << "onto output queue" << endl;
		output.push(chooseConnector(connectors.top()));
		connectors.pop();
	}

	// CHECK POSTFIX NOTATION (debugging purposes)
	// printBaseQueue(output);
	// cout << endl;

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
			// cout << "Pushing " << output.front()->element() << " to tree stack" << endl;
			tree.push(output.front());
		}
		output.pop();
	}
	Base *root = tree.top(); // get root of tree
	// cout << root->element() << endl;
	// cout << root->getLeft()->element() << endl;
	// cout << root->getRight()->element() << endl;

	// cout << endl;
	if (root->evaluate()) {
		//cout << "Success" << endl;
	}

	// CHECK IF TREE IS BUILT CORRECTLY
	// cout << "Preorder traversal: ";
	// printPreorder(root);
	// cout << endl;
	// cout << "Inorder traversal: ";
	// printInorder(root);
	// cout << endl;
	// cout << "Postorder traversal: ";
	// printPostorder(root);
	// cout << endl;

	delete[] cstr;
}

bool rshell::isBalanced(vector<string> v) {
	stack<string> par;

	for (unsigned i = 0; i < v.size(); ++i) {
		// cout << "Current item is " << v.at(i) << endl;
		if (isLeftBracket(v.at(i))) {
			// cout << "Pushing to stack" << endl;
			par.push(v.at(i));
		}
		else if (isRightBracket(v.at(i))) {
			if (par.empty()) {
				return false;
			}
			else {
				string temp = par.top();
				par.pop();

				if (isLeftBracket(temp)) {
					continue;
				}
				else {
					return false;
				}
			}
		}
	}

	return par.empty();
}

bool rshell::isConnector(string argument) {
	if (argument == "&&" || argument == "||" || argument == ";") {
		return true;
	}
	return false;
}

bool rshell::isLeftBracket(string argument) {
	if (argument == "(") {
		// cout << "Element is left bracket" << endl;
		return true;
	}
	return false;
}

bool rshell::isRightBracket(string argument) {
	if (argument == ")") {
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

void rshell::printStringVector(vector<string> v) {
	for (unsigned i = 0; i < v.size(); ++i) {
		cout << v.at(i) << endl;
	}
}

void rshell::printBaseQueue(queue<Base*> q) {
	while (!q.empty()) {
		cout << q.front()->element() << endl;
		q.pop();
		// cout << "Printed element" << endl;
	}
	// cout << "Done printing queue" << endl;
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