#ifndef CONNECTOR_H
#define CONNECTOR_H

class connector : public base {
	public:
		virtual bool evaluate() = 0;
};

class andConnect : public connector {
	private:
		base* parent;
		base* left;
		base* right;
	public:
		bool evaluate();
};

class orConnect : public connector {
	private:
		base* parent;
		base* left;
		base* right;
	public:
		bool evaluate();
};

class semicol : public connector {
	private:
		base* parent;
		base* left;
		base* right;
	public:
		bool evaluate();
};

#endif