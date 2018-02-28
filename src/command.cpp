#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include "command.h"
#include "fstream" 

using namespace std;

Command::Command(vector<string> v) {
	for (unsigned i = 0; i < v.size(); ++i) {
		cmds.push_back(v.at(i));
	}
}

bool Command::evaluate() {
	// cout << "Running COMMAND evaluate" << endl;
	if (cmds.at(0) == "exit"){
		exit(0);
	}
	//check if its a test command
	if (cmds.at(0) == "test" || cmds.at(0) == "["){
		if (cmds.at(0) == "["){
			//check if brackets are valid
			if (cmds.at(cmds.size()-1) != "]"){
				cout << "invalid bracket" << endl;
				return false;
			}
		}
		//the different test commands
		if (cmds.at(1) == "-e"){
					struct stat info;
					//check if file/directory is accessible
					if(stat(const_cast<char*>(cmds.at(2).c_str()), &info) != 0){
						cout << "cannot access %s\n " << cmds.at(2) << endl;
						cout << "(False)" << endl;
						return false;
					}
					else{
						cout << "(True)" << endl;
						return true;
					}
			}
		else if (cmds.at(1) == "-f"){
					struct stat info;
					if(stat(const_cast<char*>(cmds.at(2).c_str()), &info) != 0){
						cout << "cannot access %s\n " << cmds.at(2) << endl;
						cout << "(False)" << endl;
						return false;
					}
					else if (info.st_mode & S_IFREG){
						cout << "(True)" << endl;
						return true;
					}
					else{
						cout << "(False)" << endl;
						return false;
					}
		}
		else if (cmds.at(1) == "-d"){
					struct stat info;
					if(stat(const_cast<char*>(cmds.at(2).c_str()), &info) != 0){
						cout << "cannot access %s\n " << cmds.at(2) << endl;
						cout << "(False)" << endl;
						return false;
					}
					else if (info.st_mode & S_IFDIR){
						cout << "(True)" << endl;
						return true;
					}
					else{
						cout << "(False)" << endl;
						return false;
					}
		}
		
	}
	else{
	unsigned arrSize = cmds.size() + 1;
	char * args[arrSize]; // make a char pointer array of the same size as cmds vector
    int status = 0;
	// populate args array with commands in cmds vector
	for (unsigned i = 0; i < arrSize - 1; ++i) {
		args[i] = const_cast<char*>(cmds.at(i).c_str());
	}
	args[arrSize - 1] = NULL; // make last index NULL

	pid_t pid = fork();
	pid_t w;

	if (pid < 0) { // if pid returns a negative value, then error
		cout << "Forking child failed" << endl;
		exit(1);
	}
	else if (pid == 0) {
		if (execvp(*args, args) < 0) { // if execvp returns, then error
			cout << "Execution failed" << endl;
            exit(1);
		}
	}
	else {
		w = waitpid(pid, &status, 0);
		if (w == -1){
			cout << "Issue with waitpid" << endl;
			exit(EXIT_FAILURE);
		}
		if (WEXITSTATUS(status) == 0){
			return true;
		}
	}
}

	return false;
}


string Command::element() {
	string total;
	for (unsigned i = 0; i < cmds.size() - 1; ++i) {
		total = total + cmds.at(i) + " ";
	}
	total = total + cmds.at(cmds.size() - 1);
	return total;
}

void Command::setLeft(Base* node) {}
void Command::setRight(Base* node) {}