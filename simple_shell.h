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
char *build_path(char *cmd);
char *_getenv(const char *name);
void execute(char **tokens, char *prog_name);
char *resolve_command(char *cmd, char *prog_name, int line_count);

#endif
