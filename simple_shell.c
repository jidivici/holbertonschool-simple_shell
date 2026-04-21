#include "simple_shell.h"
/**
 * handle_builtins - Executes built-in commands if matched
 * @tokens: Command arguments
 * @line: Input command line
 * @status: Last command exit status
 *
 * Return: 1 if built-in executed, 0 otherwise
 */
int handle_builtins(char **tokens, char *line, int status)
{
	if (!tokens || !tokens[0])
		return (0);
	if (strcmp(tokens[0], "exit") == 0)
		builtins_exit(tokens, line, status);
	else if (strcmp(tokens[0], "env") == 0)
		return (builtins_env());
	return (0);
}
/**
 * process_line - handles parsing, resolution and execution of one line
 * @line: input line
 * @av: program arguments
 * @line_count: current line number
 * @status: Last command exit status
 *
 * Return: exit status
 */
int process_line(char *line, char **av, int line_count, int status)
{
	char *cmd;
	char **tokens;

	tokens = parser(line);
	if (!tokens || !tokens[0])
	{
		free(tokens);
		return (0);
	}
	if (handle_builtins(tokens, line, status))
	{
		free(tokens);
		return (0);
	}
	cmd = tokens[0];
	tokens[0] = resolve_cmd_path(tokens[0]);
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
		status = process_line(line, av, line_count, status);
		if (interactive)
			write(1, "$ ", 2);
	}
	free(line);
	return (status);
}
