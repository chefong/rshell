# assignment2

rshell is a command shell emulator written in C++.
The user is able to execute a single command and multiple commands (conditionally) using,
* ; (next command is always executed)
* && (next command is executed ONLY IF the previous command succeeds)
* || (next command is executed ONLY IF the previous command fails)

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
##### Contributors: Eric Ong and Garret Lim
