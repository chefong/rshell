#include <iostream>
#include <unistd.h>
#include "connector.h"
using namespace std;

bool andConnect::evaluate(int in, int out) { //corresponds with "&&" symbol 
	// cout << "calling AND evaluate" << endl;
	if (left->evaluate(0, 1)) {
		return right->evaluate(0, 1);
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

bool orConnect::evaluate(int in, int out) { //corresponds with "||" symbol
	// cout << "calling OR evaluate" << endl;
	if (!left->evaluate(0, 1)) {
		return right->evaluate(0, 1);
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

bool semicol::evaluate(int in, int out) { //corresponds with ";" symbol
	// cout << "Calling SEMICOL evaluate" << endl;
	left->evaluate(0, 1);
	// cout << right->element() << endl;
	return right->evaluate(0, 1);
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

bool pipeConnect::evaluate(int in, int out) { //corresponds with "|" symbol
	int fds[2];
	pipe(fds);

	left->evaluate(in, fds[1]);
	right->evaluate(fds[0], out);

	close(fds[0]);
	close(fds[0]);

	return true;
}

string pipeConnect::element() {
	return "|";
}

void pipeConnect::setLeft(Base* node) {
	left = node;
}

void pipeConnect::setRight(Base* node) {
	right = node;
}