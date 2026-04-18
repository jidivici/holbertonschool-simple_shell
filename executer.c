#include "simple_shell.h"
/**
 * execute - forks and executes a command
 * @tokens: NULL-terminated array of arguments
 * @prog_name: Name of the program
 *
 * Return: Nothing
 */
int execute(char **tokens, char *prog_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(tokens[0], tokens, environ);
		perror(prog_name);
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
