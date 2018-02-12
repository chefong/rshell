#include <iostream>
#include "Connector.h"
using namespace std;

bool andConnect::evaluate() {     //corresponds with "&&" symbol 
	if (left->evaluate()) {
		return right->evaluate();
	}
	return false;
}

bool orConnect::evaluate() {     //corresponds with "||" symbol
	if (!left->evaluate()) {
		return right->evaluate();
	}
	return true;
}

bool semicol::evaluate(){      //corresponds with ";" symbol
	return right->evaluate();
}

	