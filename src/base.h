#ifndef BASE_H
#define BASE_H

#include <iostream>
using namespace std;

class Base {
	private:
		Base* left;
		Base* right;
	public:
		Base() : left(0), right(0) {};
		virtual bool evaluate(int, int) = 0;
		virtual string element() = 0;
		Base* getLeft() {
			return left;
		}
		Base* getRight() {
			return right;
		}
		virtual void setLeft(Base*) = 0;
		virtual void setRight(Base*) = 0;
};

#endif
