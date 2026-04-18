#include "simple_shell.h"
/**
 * execute - forks and executes a command
 * @tokens: NULL-terminated array of arguments
 * @prog_name: Name of the program
 * @line_count: The line the error is located
 *
 * Return: Nothing
 */
void execute(char **tokens, char *prog_name, int line_count)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		execve(tokens[0], tokens, environ);
		perror(prog_name);
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}
