# twanshell

## Introduction

This is a Linux Shell implemented in C.

The Shell has been tested on **Linux** based OS.

## Structure and Features

The application implements a basic Shell which can perform basic Shell operations.

###The Built-in commands of the shell include

- `ls [-l -a] [file]`

  - The ls command to list all the files and directories in the specified directory.
  - Similarities with conventional ls and prints the contents in the alphabetically sorted order.

- `cd [file]`

  - The cd command changes directory to the directory specified in the given path.

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