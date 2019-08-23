# twanshell

## Introduction

This is a Linux Shell implemented in C.


## Running

- run "make"

- execute by using "./twan"

- type "exit" to exit the shell

## Built-In Commands

- `ls [-l -a] [file]`

  * "ls" - lists all the files and directories in the current directory in alphabetical orders
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

  * Displays the arguments in the stdout.
  * "echo" - prints empty line
  * "echo "text"" - prints "text" (in double quotes)
  * "echo 'text' " - prints "text" (in single quotes)
  * "echo text" - prints the text as it is

- `pwd`

  * Show present working directory.
  * Takes no arguments

- `pinfo [pid]`

  * Display the information related to a process.
  * At most one argument can be provided
  * If no argument provided, takes pid of the current process ie the shell
  

- `exit`

  * Exit the shell.


For all the other commands the shell will fork the current process and create child process and execute the command.

The shell can also run commands in the background. To do so, type `&` argument at the end of the command. (_This feature does not work with built-in commands_)

The home directory of the shell is the directory where the executable file is stored.

## Explanation of Files

- `bgfg.c`
  * child_sig() - Called when child process dies
  * foregrnd() - For foreground processes
  * backgrnd() - For background processes

- `cd.c`
  * cd - Changes the directory

- `echo.c` 
  * echo() - Prints arguments onto stdout

- `headers.h`
  * Contains all the required header files, global variables and function declarations.

- `ls.c`
  * ls() - Initialises variables for listing directories
  * show() - Prints the files in directory

- `pinfo.c`
  * pinfo() - Prints the info of the process
  
- `pwd.c`
  * pwd() - Print the present working directory
  * tildconvertedpwd() - Print the command prompts
  * tildconverter() - Replaces absolute path of home directory with ~ symbol

- `twanshell.c`
  * main() - main function to initialise things and call the loop
  * twanloop() - The loop that keeps running throughout



