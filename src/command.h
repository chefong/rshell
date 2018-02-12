#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

#include "base.h"

class command: public Base {
	private:
		string name;
		vector<string> cmds;
	public:
		command(vector<string>);
		void read();
		bool isConnector(string);
		bool evaluate();
};

#endif
