#include "simple_shell.h"
/**
 * main - Read the code
 * @ac: Argument count
 * @av: Argument value
 *
 * Return : O on sucess
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	char **tokens;
	(void)ac;
	(void)av;

	printf("$ ");

	while (getline(&line, &len, stdin) != -1)
	{
		tokens = parser(line);
		if (!tokens[0])
		{
			free(tokens);
			printf("$ ");
			continue;
		}
		if (tokens[0][0] != '/')
		{
			tokens[0] = build_path(tokens[0]);
			if (!tokens[0])
			{
				free(tokens);
				printf("$ ");
				continue;
			}
		}
		execute(tokens);
		free(tokens);
		printf("$ ");
	
	}
	free(line);
	return (0);
}
