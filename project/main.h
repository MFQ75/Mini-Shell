#ifndef MAIN_H
#define MAIN_H

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define INT_CMD 0
#define EXT_CMD 1
#define CMD_NOT_FOUND 2

int check_command_type(char *input);
int execute_external_command(char *input);
int execute_internal_command(char *input);
void signal_handler(int signum);
#endif
