#include "simple_shell.h"

/**
 * free_argv - Frees a NULL-terminated argv array
 * @argv: array of strings
 * @i: last valid index
 */
void free_argv(char **argv, int i)
{
	while (i >= 0)
	{
		free(argv[i]);
		i--;
	}
	free(argv);
}

/**
 * parser - Splits a command line into argv array
 * @line: input string
 *
 * Return: NULL-terminated argv array or NULL on failure
 */
char **parser(char *line)
{
	int capacity = 16;
	int i = 0;
	char **argv = malloc(sizeof(char *) * capacity);
	char **new_argv;
	char *current_token;

	if (!argv)
		return (NULL);
	current_token = strtok(line, " \n");
	while (current_token)
	{
		if (i >= capacity - 1)
		{
			capacity *= 2;
			new_argv = realloc(argv, sizeof(char *) * capacity);
			if (!new_argv)
			{
				free_argv(argv, i - 1);
				return (NULL);
			}
			argv = new_argv;
		}
		argv[i] = strdup(current_token);
		if (!argv[i])
		{
			free_argv(argv, i - 1);
			return (NULL);
		}
		i++;
		current_token = strtok(NULL, " \n");
	}
	argv[i] = NULL;
	return (argv);
}
