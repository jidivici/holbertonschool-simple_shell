#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
extern char **environ;

char **parser(char *line);
char *resolve_cmd_path(char *cmd);
char *_getenv(const char *name);
int execute(char **tokens, char *prog_name, int line_count);
int process_line(char *line, char **av, int line_count);
char *find_exec_path(char *path, char *cmd);

#endif
