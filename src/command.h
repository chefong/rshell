#ifndef COMMAND_H
#define COMMAND_H

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
