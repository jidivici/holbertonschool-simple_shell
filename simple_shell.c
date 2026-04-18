#include "simple_shell.h"
/**
 * main - Read the code
 * @ac: Argument count
 * @av: Argument value
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	int interactive = isatty(STDIN_FILENO), status = 0;
	size_t len = 0;
	char **tokens;
	(void)ac;

	if (interactive)
		printf("$ ");
	
	while(getline(&line, &len, stdin) != -1)
	{
		tokens = parser(line);
		if (!tokens[0])
		{
			free(tokens);
			if (interactive)
        			write(1, "$ ", 2);
    			continue;
		}
		status = execute(tokens, av[0]);
		free(tokens);
		if (interactive)
			printf("$ ");
	}
	free(line);
	return (status);
}
