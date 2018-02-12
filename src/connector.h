#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "command.h"
class connector : public base {
	public:
		virtual bool evaluate() = 0;
		bool isConnector(String);
};

class andConnect : public connector {
	private:
		string name
		Base* left;
		Base* right;
	public:
		andConnect(string name) : name(name) {}
		bool evaluate();
		
};

class orConnect : public connector {
	private:
		string name;
		Base* left;
		Base* right;
	public:
		orConnect(string name) : name(name) {}
		bool evaluate();
};

class semicol : public connector {
	private:
		Base* left;
		Base* right;
	public:
		bool evaluate();
};

#endif
