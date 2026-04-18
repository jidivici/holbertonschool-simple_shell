#include "simple_shell.h"
/**
 * _getenv - Fetches an environment variable by name
 * @name: The variable name to search for
 *
 * Return: Pointer to the value, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len_name = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len_name) == 0)
		{
			if (environ[i][len_name] == '=')
			{
				return (environ[i] + len_name + 1);
			}
		}
		i++;
	}
	return (NULL);
}
/**
 * build_path - Search for a command in the PATH directories
 * @cmd: The command name to find
 *
 * Return: Full path of the command if found, NULL otherwise
 */
char *build_path(char *cmd)
{
	char *path = _getenv("PATH");
	char *path_cpy;
	char *dir;
	char full_path[1024];
	struct stat st;

	if (!path)
		return (NULL);

	path_cpy = strdup(path);

	if (!path_cpy)
		return (NULL);

	dir = strtok(path_cpy, ":");

	while (dir)
	{
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (stat(full_path, &st) == 0)
		{
			free(path_cpy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}
/**
 * resolve_command - Determines if a command exists and where
 * @cmd: The command
 * @prog_name: Program name
 * @line_count: The line counter
 *
 * Return: The path of the command or NULL
 */
char *resolve_command(char *cmd, char *prog_name, int line_count)
{
	char *path;

	if (cmd[0] == '/')
		return (strdup(cmd));
	path = build_path(cmd);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_count, cmd);
		return (NULL);
	}
	return (path);
}
