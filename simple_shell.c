#include "simple_shell.h"
/**
 * main - Read the code
 * @ac: Argument count
 * @av: Argument value
 *
 * Return: status
 */
int main(int ac, char **av)
{
	char *line = NULL;
	int interactive = isatty(STDIN_FILENO), line_count = 0, status = 0;
	size_t len = 0;
	char **tokens;
	(void)ac;

	if (interactive)
		write(1, "$ ", 2);
	while (getline(&line, &len, stdin) != -1)
	{
		line_count += 1;
		tokens = parser(line);
		if (!tokens[0])
		{
			free(tokens);
			if (interactive)
				write(1, "$ ", 2);
			continue;
		}
		tokens[0] = resolve_command(tokens[0], av[0]);
		if (!tokens[0])
		{
			free(tokens);
			if (interactive)
				write(1, "$ ", 2);
			status = 127;
			continue;
		}
		status = execute(tokens, av[0], line_count);
		free(tokens[0]);
		free(tokens);
		if (interactive)
			write(1, "$ ", 2);
	}
	free(line);
	return (status);
}
