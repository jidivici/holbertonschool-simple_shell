#include "simple_shell.h"
/**
 * split_line - Tokenizations of stdin line
 * @line: The stdin
 * 
 * Return : A pointer to the newline
 */
char **split_line(char* line)
{
	int capacity = 16;
	int i = 0;
	char **tokens = malloc(sizeof(char*) * capacity);
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \n");

	while(token)
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
/**
 * main: Read the code
 * @ac: Argument count
 * @av: Argument value
 * 
 * Return : O on sucess
 */
int main(int ac, char **av)
{
	int i = 0, j = 0;
	pid_t my_pid;
	pid_t my_ppid;
	char *line = NULL;
	size_t len = 0;
	char **cmd;

	printf("----------------------------------------\n");

	while (av[i])
	{
		printf("[argv %d] : %s\n", i, av[i]);
		i++;
	}
	printf("----------------------------------------\n");
	printf("$ ");

	while (getline(&line, &len, stdin) != -1)
	{
		cmd = split_line(line);
		printf("%s", cmd[1]);
		printf("$ ");
	}

	free (line);
	return (0);
}
