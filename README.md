# twanshell

## Introduction

This is a Linux Shell implemented in C.

The home directory of the shell is the directory where the executable file is stored.

## Running

- run "make"

- execute by using "./twan"

- type "exit" to exit the shell

## Built-In Commands

- `ls [-l -a] [file]`

  * "ls" - lists all the files and directories in the current directory
  * "ls -a" - display hidden files
  * "ls -l" - long list
  * "ls -al"/"ls -la"/"ls -l -a"/"ls -a -l" - long list including hidden files
  * The ls command can also be provided with multiple arguments in the same command
  * The order of the flags and files can also be arbitrary after ls


- `cd [file]`

  * The cd command changes directory to the directory specified in the given path.
  * Path can be relative or absolute
  * "cd .." - goes to previous directory
  * "cd ." - goes to same directory  
  * "cd" - goes to ~/
  * The command can take at most one argument

- `echo [arguments]`

  - Displays the arguments in the stdout.

- `exit`

  - Exit the shell.

- `pwd`

  - Show present working directory.

- `pinfo [pid]`

  - Display the information related to a process.

For all the other commands the shell will fork the current process and create child process and execute the command.

The shell can also run commands in the background. To do so, type `&` argument at the end of the command. (_This feature does not work with inbuilt commands_)

## Running the Shell

1. Run the Makefile
   - `make all`
2. Run the executable
   - `./twan`