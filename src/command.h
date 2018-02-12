#ifndef COMMAND_H
#define COMMAND_H
#include "base.h"
#include <string>
#include <vector>

class command: public Base {
	private:
		string name;
		vector<string> cmds;
	public:
		command(string name) : name(name) {}
		void parseStrings();
		void printPrompt();
		void read();
		bool isConnector(string);
		bool evaluate();
};

#endif
