#ifndef COMMAND_H
#define COMMAND_H

class command: public Base {
	private:
		vector<string> cmds;
	public:
		void printPrompt();
		void read();
};

#endif
