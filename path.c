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
 * search_in_path - Searches for a command in the PATH directories
 * @path: The PATH environment variable string
 * @cmd: The command to search for
 *
 * Return: Full path of the command if found, NULL otherwise
 */
char *search_in_path(char *path, char *cmd)
{
	char *path_cpy = strdup(path);
	char *dir;
	char full_path[1024];
	struct stat st;

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
* build_path - Resolves a command using the PATH environment variable
 * @cmd: The command name to resolve
 *
 * Return: Full path of the command if found, NULL otherwise
 */
char *build_path(char *cmd)
{
	char *path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (strchr(cmd, '/'))
		return (strdup(cmd));
	path = _getenv("PATH");
	if (!path)
		return (NULL);
	return (search_in_path(path, cmd));
}
/**
 * resolve_command - Determines if a command exists and where
 * @cmd: The command
 * @prog_name: Program name
 *
 * Return: The path of the command or NULL
 */
char *resolve_command(char *cmd, char *prog_name, int line_count)
{
	char *path;

	if (!cmd)
		return (NULL);
	if (strchr(cmd, '/'))
		return (strdup(cmd));
	path = build_path(cmd);
	return (path);
}
