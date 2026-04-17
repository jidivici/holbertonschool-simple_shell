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
        int interactive = isatty(STDIN_FILENO);
	size_t len = 0;
        int line_get;
	char **tokens;
	(void)ac;
	(void)av;

        if (interactive)
		printf("$ ");
	while ((line_get = (getline(&line, &len, stdin)) != -1))
	{
		tokens = parser(line);
		if (!tokens[0])
		{
			free(tokens);
                        if (interactive)
				printf("$ ");
			continue;
		}
		if (tokens[0][0] != '/')
		{
			tokens[0] = build_path(tokens[0]);
			if (!tokens[0])
			{
				free(tokens);
                                if (interactive)
                                	printf("$ ");
				continue;
			}
		}
		execute(tokens);
		free(tokens);
                if (interactive)
			printf("$ ");
	}
	if (line_get == -1 && !interactive)
		printf("\n");
	free(line);
	return (0);
}
