#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "command.h"

class connector : public Base {
	public:
		virtual bool evaluate() = 0;
};

class andConnect : public connector {
	private:
		Base* left;
		Base* right;
	public:
		andConnect() : left(0), right(0) {}
		bool evaluate();
};

class orConnect : public connector {
	private:
		Base* left;
		Base* right;
	public:
		orConnect() : left(0), right(0) {}
		bool evaluate();
};

class semicol : public connector {
	private:
		Base* left;
		Base* right;
	public:
		semicol() : left(0), right(0) {}
		bool evaluate();
};

#endif
