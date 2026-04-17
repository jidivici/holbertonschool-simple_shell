#include "simple_shell.h"
/**
 * execute - forks and executes a command
 * @tokens: NULL-terminated array of arguments
 * @prog_name: name of the shell program for error messages
 *
 * Return: Nothing
 */
void execute(char **tokens)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		execve(tokens[0], tokens, environ);
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}
