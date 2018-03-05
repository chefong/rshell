# rshell

rshell is a command shell emulator written in C++.
The user is able to execute a single command and multiple commands (conditionally) using,
* ;
* &&
* ||

**;** means the next command is always executed. **&&** means the next command is executed ONLY IF the previous command succeeds. **||** means the next command is executed ONLY IF the previous command fails.

A single command would be:
```
ls -a
```

Multiple commands would be:
```
ls -a; echo hello world && rm hello.h
```

To run rshell, execute the following command:
```
./bin/rshell
```

Aside from normal commands, the user is able to use the precedence operators '(' and ')'.
```
echo a && echo b || echo c && echo d #prints 'a', 'b', and 'd'
(echo a && echo b) || (echo c && echo d) #prints ONLY 'a' and 'b'
```

Test commands (in the form of "test" or "[ ]") allow the user to check if a file/directory exists in the current directory.
* -e checks if the file/directory exists
* -f checks if the file/directory exists and is a regular file
* -d checks if the file/directory exists and is a directory
```
test -e src #prints "(True)" if "src" exists in the current directory

# or equivalently
[ -e src ]
```

## Contributors/Task Distribution
* Eric Ong
  * Task 1: Github Setup (10%)
  * Task 4: The Precedence Operators (30%)
  * Task 6: Construct json and README files, and git commit (10%)
  * **Total: 50%**
* Garret Lim
  * Task 2: "Test" command 1 (for the case "test -e test/file/path") (20%)
  * Task 3: "Test" command 2 (for the case "[ -e test/file/path ]") (15%)
  * Task 5: Construct test scripts (enough test cases) (15%)
  * **Total: 50%**
