#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "command.h"

class Connector : public Base {
	public:
		virtual bool evaluate() = 0;
		virtual string element() = 0;
		virtual void setLeft(Base*) = 0;
		virtual void setRight(Base*) = 0;
};

class andConnect : public Connector {
	private:
		Base* left;
		Base* right;
	public:
		andConnect() : left(0), right(0) {};
		bool evaluate();
		string element();
		void setLeft(Base*);
		void setRight(Base*);
};

class orConnect : public Connector {
	private:
		Base* left;
		Base* right;
	public:
		orConnect() : left(0), right(0) {};
		bool evaluate();
		string element();
		void setLeft(Base*);
		void setRight(Base*);
};

class semicol : public Connector {
	private:
		Base* left;
		Base* right;
	public:
		semicol() : left(0), right(0) {};
		bool evaluate();
		string element();
		void setLeft(Base*);
		void setRight(Base*);
};

#endif
