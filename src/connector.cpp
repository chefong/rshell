#include <iostream>
#include "connector.h"
using namespace std

bool connector::isConnector(String input){
	if (input == "&&" || input == "||"){
		return true;
	}
	return false;
}
bool andConnect::evaluate(){     //corresponds with "&&" symbol 
	if (left->evaluate()){
	 return right->evaluate();
	}
	return false;
}

bool orConnect::evaluate(){     //corresponds with "||" symbol
	if (!left->evaluate()){
	 return right->evaluate();
	}
	return true;
}

bool semicol::evaluate(){      //corresponds with ";" symbol
	return right->evaluate();
}

