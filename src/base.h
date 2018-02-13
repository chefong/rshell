#ifndef BASE_H
#define BASE_H

#include <iostream>
using namespace std;

class Base {
	public:
		Base() {}
		virtual bool evaluate() = 0;
		virtual string element() = 0;
};

#endif
