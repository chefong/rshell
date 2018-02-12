#ifndef COMMAND_H
#define COMMAND_H

class command: public Base {
	private:
		vector<string> cmds;
	public:
		void parseStrings();
		void printPrompt();
		void read();
		bool evaluate();
};

#endif
