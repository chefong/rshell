#ifndef RSHELL_H
#define RSHELL_H
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include "rshell.h"
#include "base.h"
#include "connector.h"
using namespace std;

class rshell {
	public:
		rshell() {};
		void begin();
		void execute();
		void printStringVector(vector<string>);
		void printBaseQueue(queue<Base*>);
		void printPreorder(Base*);
		void printInorder(Base*);
		void printPostorder(Base*);
		bool isConnector(string);
		bool isBalanced(vector<string>);
		bool isLeftBracket(string);
		bool isRightBracket(string);
		Base* chooseConnector(string);
		Base* buildTree();
};

#endif
