#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

int execute_command(char *command);
void print_prompt(void);
int custom_getline(char *buffer, size_t size);

#endif /* HEADER_FILE_H */