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
	return "&&";
}

void andConnect::setLeft(Base* node) {
	left = node;
}

void andConnect::setRight(Base* node) {
	right = node;
}

bool orConnect::evaluate() {     //corresponds with "||" symbol
	if (!left->evaluate()) {
		return right->evaluate();
	}
	return true;
}

string orConnect::element() {
	return "||";
}

void orConnect::setLeft(Base* node) {
	left = node;
}

void orConnect::setRight(Base* node) {
	right = node;
}

bool semicol::evaluate() {      //corresponds with ";" symbol
	return right->evaluate();
}

string semicol::element() {
	return ";";
}

void semicol::setLeft(Base* node) {
	left = node;
}

void semicol::setRight(Base* node) {
	right = node;
}