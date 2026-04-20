#include "simple_shell.h"
/**
 * execute - forks and executes a command
 * @tokens: NULL-terminated array of arguments
 * @prog_name: Name of the program
 * @line_count: The line counter
 *
 * Return: Nothing
 */
int execute(char **tokens, char *prog_name, int line_count)
{
	pid_t pid;
	int status, saved_errno;

	pid = fork();
	if (pid == 0)
	{
		execve(tokens[0], tokens, environ);
		saved_errno = errno;
		fprintf(stderr, "%s: line %d: %s: %s\n",
			prog_name, line_count, tokens[0], strerror(saved_errno));
		if (saved_errno == EACCES || saved_errno == EISDIR)
			exit(126);
		exit(127);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
}
