#include <simple_shell.h>
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
		cmd = parser(line);
		printf("%s", cmd[1]);
		printf("$ ");
	}

	free (line);
	return (0);
}
