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
		dprintf(STDERR_FILENO, "%s: line %d: %s: No such file or directory\n",
			prog_name, line_count, tokens[0]);
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}
