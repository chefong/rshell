#include <iostream>
#include <algorithm>
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
#include <fcntl.h>

using namespace std;

Command::Command(vector<string> v) {
	for (unsigned i = 0; i < v.size(); ++i) {
		cmds.push_back(v.at(i));
	}
}

bool Command::evaluate(int inPipe, int outPipe) {
	// cout << "Running COMMAND evaluate" << endl;
	if (cmds.at(0) == "exit") {
		exit(0);
	}
	//check if its a test command
	if (cmds.at(0) == "test" || cmds.at(0) == "[") {
		if (cmds.at(0) == "[") {
			//check if brackets are valid
			if (cmds.at(cmds.size()-1) != "]") {
				cout << "Invalid brackets" << endl;
				return false;
			}
		}
		//the different test commands
		if (cmds.at(1) == "-e") {
			struct stat info;
			//check if file/directory is accessible
			if (stat(const_cast<char*>(cmds.at(2).c_str()), &info) != 0) {
				cout << "Cannot access " << cmds.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
			else {
				cout << "(True)" << endl;
				return true;
			}
		}
		else if (cmds.at(1) == "-f"){
			struct stat info;
			if (stat(const_cast<char*>(cmds.at(2).c_str()), &info) != 0){
				cout << "Cannot access " << cmds.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
			else if (info.st_mode & S_IFREG) {
				cout << "(True)" << endl;
				return true;
			}
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		else if (cmds.at(1) == "-d"){
			struct stat info;
			if (stat(const_cast<char*>(cmds.at(2).c_str()), &info) != 0){
				cout << "Cannot access " << cmds.at(2) << endl;
				cout << "(False)" << endl;
				return false;
			}
			else if (info.st_mode & S_IFDIR){
				cout << "(True)" << endl;
				return true;
			}
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		else {
			struct stat info;
			if (stat(const_cast<char*>(cmds.at(1).c_str()), &info) != 0){
				cout << "cannot access " << cmds.at(1) << endl;
				cout << "(False)" << endl;
				return false;
			}
			else {
				cout << "(True)" << endl;
				return true;
			}
		}
		
	}
	else {
		int status = 0;
		pid_t pid = fork();
		pid_t w;

		if (pid < 0) { // if pid returns a negative value, then error
			cout << "*** ERROR: forking child process failed\n" << endl;
			exit(1);
		}
		else if (pid == 0) {
			// ex. user enters "wc -l < scores >> out"
			// Then, cmds vector contains ["wc", "<", "scores", ">>", "out"]
			// At the end of the following loop, cmdsTemp would contain ["wc", "-l"]
			vector<string> cmdsTemp;
			for (unsigned i = 0; i < cmds.size(); ++i) {
				if (!isRedirector(cmds.at(i))) {
					cmdsTemp.push_back(cmds.at(i));
				}
				else {
					break;
				}
			}

			// At the end of the loop, inputFile = "scores" and outputFile = "out"
			for (unsigned i = 0; i < cmds.size(); ++i) {
				if (isRedirector(cmds.at(i))) {
					if (cmds.at(i) == "<") {
						setInputFile(cmds.at(i + 1));
					}
					else if (cmds.at(i) == ">" || cmds.at(i) == ">>") {
						setOutputFile(cmds.at(i + 1));
					}
				}
			}

			cout << "Input file is: " << inputFile << endl;
			cout << "Output file is: " << outputFile << endl;

			unsigned arrSizeIO = cmdsTemp.size() + 1;
			char * argsIO[arrSizeIO]; // make a char pointer array of the same size as left vector
			// populate argsIO array with commands in left vector
			for (unsigned i = 0; i < arrSizeIO - 1; ++i) {
				argsIO[i] = const_cast<char*>(cmdsTemp.at(i).c_str());
			}
			argsIO[arrSizeIO - 1] = NULL; // make last index NULL

			// If both inputFile and outputFile are not empty,
			// then both input and output redirectors are being used
			if (!inputFile.empty() && !outputFile.empty()) {
				// If the output redirector is ">" execute this branch
				if (find(cmds.begin(), cmds.end(), ">") != cmds.end()) {
					cout << "Contains < and >" << endl;


					int in_descriptor = open(inputFile.c_str(), O_RDONLY);
					int out_descriptor = open(outputFile.c_str(), O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);

					if (in_descriptor < 0 || out_descriptor < 0) {
						cout << "Error opening the file" << endl;
						return false;
					}

					dup2(in_descriptor, STDIN_FILENO);
					dup2(out_descriptor, STDOUT_FILENO);

					close(in_descriptor);
					close(out_descriptor);

					dup2(inPipe, 0);
					dup2(outPipe, 1);
					
					if (in != 0) {
						close(inPipe);
					}
					else if (out != 1) {
						close(outPipe);
					}

					if (execvp(*argsIO, argsIO) < 0) { // if execvp returns, then error
						cout << "*** ERROR: exec failed\n" << endl;
				        exit(1);
					}
				}
				else { // This means the output redirector HAS to be a ">>"
					cout << "Contains < and >>" << endl;

					int in_descriptor = open(inputFile.c_str(), O_RDONLY);
					int out_descriptor = open(outputFile.c_str(), O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG);

					if (in_descriptor < 0 || out_descriptor < 0) {
						cout << "Error opening the file" << endl;
						return false;
					}

					dup2(in_descriptor, STDIN_FILENO);
					dup2(out_descriptor, STDOUT_FILENO);

					close(in_descriptor);
					close(out_descriptor);

					dup2(inPipe, 0);
					dup2(outPipe, 1);

					if (in != 0) {
						close(inPipe);
					}
					else if (out != 1) {
						close(outPipe);
					}

					if (execvp(*argsIO, argsIO) < 0) { // if execvp returns, then error
						cout << "*** ERROR: exec failed\n" << endl;
				        exit(1);
					}
				}
			}
			// 
			else if (!inputFile.empty()) {
				cout << "Contains <" << endl;

				int f_descriptor = open(inputFile.c_str(), O_RDONLY);
				if (f_descriptor < 0) {
						cout << "Error opening the file" << endl;
						return false;
					}

				dup2(f_descriptor, STDIN_FILENO);
				close(f_descriptor);

				dup2(in, 0);
				dup2(out, 1);

				if (in != 0) {
					close(in);
				}
				else if (out != 1) {
					close(out);
				}	

				if (execvp(*argsIO, argsIO) < 0) { // if execvp returns, then error
					cout << "*** ERROR: exec failed\n" << endl;
			        exit(1);
				}
			}
			//handles > and >> operator
			else if (!outputFile.empty()) {
				if (find(cmds.begin(), cmds.end(), ">") != cmds.end()) {

					cout << "Contains >" << endl;

					for (unsigned i = 0; i < cmdsTemp.size(); ++i) {
						cout << cmdsTemp.at(i) << endl;
					}


					// open the file
					int f_descriptor = open(outputFile.c_str(), O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
					if (f_descriptor < 0) {
						cout << "Error opening the file" << endl;
						return false;
					}
					
					dup2(f_descriptor, STDOUT_FILENO);
					close(f_descriptor);

					dup2(in, 0);
					dup2(out, 1);

					if (in != 0) {
						close(in);
					}
					else if (out != 1) {
						close(out);
					}

					if (execvp(*argsIO, argsIO) < 0) { // if execvp returns, then error
						cout << "*** ERROR: exec failed\n" << endl;
			            exit(1);
					}
				}
				else {
					cout << "Contains >>" << endl;

					// open the file
					// O_RDWR | O_CREAT, S_IRUSR | S_IWUSR
					int f_descriptor = open(outputFile.c_str(), O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG);

					if (f_descriptor < 0) {
						cout << "Error opening the file" << endl;
						return false;
					}
					
					dup2(f_descriptor, STDOUT_FILENO);
					close(f_descriptor);

					dup2(in, 0);
					dup2(out, 1);

					if (in != 0) {
						close(in);
					}
					else if (out != 1) {
						close(out);
					}

					if (execvp(*argsIO, argsIO) < 0) { // if execvp returns, then error
						cout << "*** ERROR: exec failed\n" << endl;
			            exit(1);
					}
				}
			}
			else { // user enters a regular command without any redirectors
				unsigned arrSize = cmds.size() + 1;
				char * args[arrSize]; // make a char pointer array of the same size as cmds vector
				// populate args array with commands in cmds vector
				for (unsigned i = 0; i < arrSize - 1; ++i) {
					args[i] = const_cast<char*>(cmds.at(i).c_str());
				}
				args[arrSize - 1] = NULL; // make last index NULL

				dup2(in, 0);
				dup2(out, 1);

				if (in != 0) {
					close(in);
				}
				else if (out != 1) {
					close(out);
				}

				if (execvp(*args, args) < 0) { // if execvp returns, then error
					cout << "*** ERROR: exec failed\n" << endl;
		            exit(1);
				}
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

bool Command::isRedirector(string input){
	if (input == "<" || input == ">" || input == ">>"){
		return true;
	}
	return false;
}

void Command::setInputFile(string file){
	inputFile = file;
}

void Command::setOutputFile(string file){
	outputFile = file;
}