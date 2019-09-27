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

- `history [number]`

  * Displays the last 'number' commands upto 10
  * If 'number'>10 still prints last 10 commands
  * Accepts upto one argument
  * If no arguments it prints last 10 commands
  * If the same command is executed multiple times it is printed only once

- `quit`

  * Exit the shell.

- `exit`

  * Exit the shell.

- `setenv [var] [value]`

  * Sets value of environment variable 'var' to 'value'
  * If 'value' is not given sets value to empty string
  * Accepts either one or two arguments only

- `unsetenv [var1] [var2] ...`
 
  * Destroys all the environment variables 'var1','var2' etc given as arguments
  * Must have at least one argument

- `fg [jobnumber]`
  * Brings a running or a stopped background job with given job number to foreground

- `bg [jobnumber]`
  * Changes a stopped background job to a running background job

- `overkill`
  * Kills all background process at once

- `jobs`
  * ​ Prints a list of all currently running jobs along with their pid, in particular, background jobs, in order of their creation along with their state - Running or Stopped.

- `kjob [jobnumber] [signalnumber]`
  * Takes the job id of a running job and sends a signal value to that process

- `CTRL-Z`
  * It should change the status of currently running job to stop, and push it in background process.

- ​`CTRL-C` ​
  * It should cause a SIGINT signal to be sent to the current foreground job of the shell​ 

For all the other commands the shell will fork the current process and create child process and execute the command.

The shell can also run commands in the background. To do so, type `&` argument at the end of the command. (_This feature does not work with built-in commands_)

The home directory of the shell is the directory where the executable file is stored.

## Explanation of Files

- `bgfg.c`
  * child_sig() - Called when child process dies
  * foregrnd() - For foreground processes
  * backgrnd() - For background processes

- `cd.c`
  * cd() - Changes the directory

- `echo.c` 
  * echo() - Prints arguments onto stdout

- `headers.h`
  * Contains all the required header files, global variables and function declarations.

- `hist.txt`
  * File to store the past commands, stores upto 20 commands

- `history.c`
  * historyinit() - Reads hist.txt and stores into array
  * historyadd() - Adds each command to array if not repeat of the last entry
  * historydisp() - Prints the history according to arguments
  * historyexit() - Stores last 20 commands in hist.txt

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

- `env.c`
   * senv() - Changes value of environment variable
   * unsenv() - Detroys the environment variables