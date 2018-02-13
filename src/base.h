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
		virtual bool evaluate() = 0;
		virtual string element() = 0;
		void setLeft(Base* node) {
			left = node;
		}
		void setRight(Base* node) {
			right = node;
		}
		Base* getLeft() {
			return left;
		}
		Base* getRight() {
			return right;
		}
};

#endif
