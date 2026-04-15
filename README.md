# SIMPLE_SHELL

## NAME
simple_shell - minimal UNIX command interpreter

---

## DESCRIPTION
simple_shell is a minimal UNIX command interpreter developed as part of the Holberton School curriculum.

The project aims to reproduce core shell behavior by implementing command execution, process creation, and environment handling using low-level UNIX system calls.

---

## SYNOPSIS
./simple_shell

---

## OPERATION
The shell operates in a loop:

- display a prompt (interactive mode only)
- read user input
- tokenize input into arguments
- resolve command path using PATH if necessary
- create a child process using fork()
- execute command using execve()
- wait for process termination using wait()

---

## FEATURES (BASE PROJECT 0.1 → 1.0)

### command execution
The shell executes programs such as:
- ls
- pwd
- echo

Execution is performed using fork(), execve(), and wait().

---

### path resolution
If a command is not an absolute path, the shell searches it in PATH.

PATH is a colon-separated list of directories used to locate executables.

Examples:
- ls → /bin/ls
- /bin/ls → direct execution

---

### interactive mode
The shell displays a prompt and waits for user input in a loop.

---

### non-interactive mode
The shell reads commands from pipes or files.

Example:
echo "ls -l" | ./simple_shell

---

### built-in commands
exit
- exits the shell

env
- prints environment variables

---

## ENVIRONMENT
The shell inherits the environment from the parent process.

PATH is required for command resolution.

---

## RETURN VALUE
0    success
126  command found but not executable
127  command not found

---

## LIMITATIONS (BASE PROJECT ONLY)

The base implementation does not support:

- pipes (|)
- redirections (>, <, >>)
- logical operators (&&, ||)
- quoting and escaping
- environment variable expansion ($HOME)
- job control

---

## ADVANCED FEATURES (SEPARATE TASKS)

The following features are implemented in advanced stages:

- command separators (;)
- logical operators (&&, ||)
- cd builtin
- setenv / unsetenv
- aliases
- comments (#)
- command history
- file input execution

---

## FILES

simple_shell.c  main loop
parser.c        input parsing
executor.c      command execution
path.c          PATH resolution
builtins.c      built-in commands

---

## EXAMPLES

interactive mode:
./simple_shell

non-interactive mode:
echo "ls -l" | ./simple_shell

built-ins:
exit
env

---

## SIGNALS

SIGINT (Ctrl+C)
does not terminate the shell
prints a new prompt

---

## AUTHORS
Brice Fontaine
Vadim Gavet

---

## NOTES
This project demonstrates:

- process creation (fork)
- program execution (execve)
- command parsing
- environment handling
- memory management