#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Command.h"

class Connector : public Base {
	public:
		virtual bool evaluate() = 0;
};

class andConnect : public Connector {
	private:
		Base* left;
		Base* right;
	public:
		andConnect() : left(0), right(0) {}
		bool evaluate();
};

class orConnect : public Connector {
	private:
		Base* left;
		Base* right;
	public:
		orConnect() : left(0), right(0) {}
		bool evaluate();
};

class semicol : public Connector {
	private:
		Base* left;
		Base* right;
	public:
		semicol() : left(0), right(0) {}
		bool evaluate();
};

#endif
