#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

#include "Base.h"

class Command: public Base {
	private:
		string name;
		vector<string> cmds;
	public:
		Command():Base() {};
		Command(vector<string>);
		bool evaluate();
		string element();
};

#endif
