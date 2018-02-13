#ifndef RSHELL_H
#define RSHELL_H
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include "rshell.h"
#include "Base.h"
#include "Connector.h"
using namespace std;

class rshell {
	public:
		rshell() {};
		void execute();
		void printBaseQueue(queue<Base*>);
		bool isConnector(string);
		Base* chooseConnector(string);
};

#endif
