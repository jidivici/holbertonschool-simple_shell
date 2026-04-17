#include "simple_shell.h"

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
