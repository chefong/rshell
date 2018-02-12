#ifndef RSHELL_H
#define RSHELL_H
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include "command.h"
#include "rshell.h"
#include <iostream>
#include "base.h"
#include "connector.h"
using namespace std;

class rshell {
	public:
		void execute();
		bool isConnector(string);
};

#endif
