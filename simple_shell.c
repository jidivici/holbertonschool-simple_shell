#include "simple_shell.h"
/**
 * main - Read the code
 * @ac: Argument count
 * @av: Argument value
 *
 * Return: O on sucess
 */
int main(int ac, char **av)
{
	char *line = NULL, *cmd_name;
	int interactive = isatty(STDIN_FILENO), line_count = 0;
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
		if (tokens[0][0] != '/')
		{
			cmd_name = strdup(tokens[0]);
			tokens[0] = build_path(tokens[0]);
			if (!tokens[0])
			{
				dprintf(STDERR_FILENO, "%s: line %d: %s: command not found\n",
					av[0], line_count, cmd_name);
				free(tokens);
				free(cmd_name);
				if (interactive)
					write(1, "$ ", 2);
				continue;
			}
		}
		execute(tokens, av[0], line_count);
		free(tokens);
		if (interactive)
			write(1, "$ ", 2);
	}
	free(line);
	return (0);
}
