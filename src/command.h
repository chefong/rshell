#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>


#include "base.h"

class Command: public Base {
	private:
		string name;
		vector<string> cmds;
		string inputFile;
		string outputFile;
	public:
		Command():Base() {};
		Command(vector<string>);
		bool evaluate(int, int);
		string element();
		void setLeft(Base*);
		void setRight(Base*);
		bool isRedirector(string);
		void setInputFile(string);
		void setOutputFile(string);
};

#endif
