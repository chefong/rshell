#include <iostream>
#include "Connector.h"
using namespace std;

bool andConnect::evaluate() {     //corresponds with "&&" symbol 
	if (left->evaluate()) {
		return right->evaluate();
	}
	return false;
}

string andConnect::element() {
	return "&& ";
}

bool orConnect::evaluate() {     //corresponds with "||" symbol
	if (!left->evaluate()) {
		return right->evaluate();
	}
	return true;
}

string orConnect::element() {
	return "|| ";
}

bool semicol::evaluate() {      //corresponds with ";" symbol
	return right->evaluate();
}

string semicol::element() {
	return "; ";
}