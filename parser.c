#include <simple_shell.h>
/**
 * parser - Tokenizations of stdin line
 * @line: The stdin
 *
 * Return: A tab of string pointers
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
		}
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (tokens);
}
