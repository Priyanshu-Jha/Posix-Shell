Name: Priyanshu Jha


## README for POSIX Shell Implementation )

Task Overview: The assignment involves building a custom POSIX shell in C/C++ that supports basic shell functionalities such as command executions. The shell must handle both built-in and system commands, along with special commands like cd, echo, and pwd. Additional features include history.

## Key Features:

1. Shell Prompt: Displays in the format <username>@<system_name>:<current_directory>.
2. Built-in Commands: Implements cd, echo, pwd, clear and exit without using execvp().
3. ls Command: Supports flags -a and -l, including combinations of both.
4. Search: Search for files, directories and files inside directories.
5. History: Stores up to 20 commands across sessions and supports history <num>.


## Compilation: Use the provided Makefile to compile the shell:

Open the target file location, and give command to remove any pre-existing executables
by typing in (rm \*.o).

Below is run commands:
make
g++ -o main main.o cd.o echo.o ls.o pwd.o username.o history.o upKey.o search.o pinfo.o historyreturn.o back_forg.o io.o pipe.o
./main

## Note::

I have taken this "/home/priyanshu/Desktop/2024201062_Assignment2" as a root address for shell.
I haven't implemented pip with I/O Redirection, signals, Autocomplete and partial ls.
