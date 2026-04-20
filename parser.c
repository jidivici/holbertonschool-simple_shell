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
	int i = 0, j = 0;
	char **tokens_tab = malloc(sizeof(char *) * capacity);
	char **new_tokens_tab;
	char *new_token;

	if (!tokens_tab)
		return (NULL);

	new_token = strtok(line, " \n");

	while (new_token)
	{
		if (i >= capacity - 1)
		{
			capacity *= 2;
			new_tokens_tab = malloc(sizeof(char *) * capacity);
			if (!new_tokens_tab)
			{
				free(tokens_tab);
				return (NULL);
			}
            for (j = 0; j < i; j++)
				new_tokens_tab[j] = tokens_tab[j];
            free(tokens_tab);
            tokens_tab = new_tokens_tab;
		}
		tokens_tab[i] = new_token;
		i++;
		new_token = strtok(NULL, " \n");
	}
	tokens_tab[i] = NULL;
	return (tokens_tab);
}
