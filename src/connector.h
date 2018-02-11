#ifndef CONNECTOR_H
#define CONNECTOR_H

class connector : public base {
	public:
		virtual bool evaluate() = 0;
};

class andConnect : public connector {
	private:
		Base* left;
		Base* right;
	public:
		bool evaluate();
};

class orConnect : public connector {
	private:
		Base* left;
		Base* right;
	public:
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
