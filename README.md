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
```C++
/* prints 'a', 'b', and 'd' */
echo a && echo b || echo c && echo d

/* prints ONLY 'a' and 'b' */
(echo a && echo b) || (echo c && echo d)
```

Test commands (in the form of "test" or "[ ]") allow the user to check if a file/directory exists in the current directory.
* "-e" checks if the file/directory exists
* "-f" checks if the file/directory exists and is a regular file
* "-d" checks if the file/directory exists and is a directory
```C++
/* prints "(True)" if "src" exists in the current directory */
test -e src

/* or equivalently */
[ -e src ]
```

Piping and input/output redirectors are used to send input/output to/from a file or from one program to another.
* ">" takes a command and outputs the result into a file, overwriting it
* ">>" takes a command and appends the result into a file
* "<" takes a file and uses it as input for a command
* "|" sends data from one program to another
```C++
/* stores "hello" into the file "out.txt" */
echo hello > out.txt

/* appends "hi" to the file "out.txt" */
echo hi >> out.txt

/* counts the number of words, lines, and characters in "test.txt" */
wc < test.txt

/* counts the number of files in the current directory */
ls | wc -l
```


## Contributors/Task Distribution
* Eric Ong
  * Task 1: Github Setup (10%)
  * Task 4: Piping (25%)
  * Task 5: Construct Test Scripts (enough test cases) (15%)
  * **Total: 50%**
* Garret Lim
  * Task 2: Input redirection (For commands contain "<", 20%);
  * Task 3: Output redirection (For commands contain ">" and ">>", 20%);
  * Task 6: Construct json and README files, and git commit (that means, all the works meaned from the part "Submission" to "Coding Conventions" in assignment 4 description)(10%) 
  * **Total: 50%**
