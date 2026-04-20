#include "simple_shell.h"
/**
 * parser - Splits a string into an array of tokens
 * @line: The input string to tokenize
 *
 * Return: NULL-terminated array of strings, or NULL on failure
 */
char **parser(char *line)
{
	int capacity = 16;
	int i = 0;
	char **tokens = malloc(sizeof(char *) * capacity);
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \n");

	while (token)
	{
		if (i >= capacity - 1)
		{
			capacity *= 2;
			tokens = realloc(tokens, sizeof(char *) * capacity);
			if (!tokens)
			{
				free(tokens);
				return (NULL);
			}
		}
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (tokens);
}
