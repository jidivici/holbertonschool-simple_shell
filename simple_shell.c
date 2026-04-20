#include "simple_shell.h"
/**
 * process_line - handles parsing, resolution and execution of one line
 * @line: input line
 * @av: program arguments
 * @line_count: current line number
 *
 * Return: exit status
 */
int process_line(char *line, char **av, int line_count)
{
	char *cmd;
	char **tokens;
	int status;

	tokens = parser(line);
	if (!tokens || !tokens[0])
	{
		free(tokens);
		return (0);
	}
	cmd = tokens[0];
	tokens[0] = build_path(tokens[0]);
	if (!tokens[0])
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			av[0], line_count, cmd);
		free(tokens);
		return (127);
	}
	status = execute(tokens, av[0], line_count);
	free(tokens[0]);
	free(tokens);
	return (status);
}
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
	(void)ac;

	if (interactive)
		write(1, "$ ", 2);
	while (getline(&line, &len, stdin) != -1)
	{
		line_count += 1;
		status = process_line(line, av, line_count);
		if (interactive)
			write(1, "$ ", 2);
	}
	free(line);
	return (status);
}
