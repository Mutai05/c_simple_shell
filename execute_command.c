#include "header_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute_command(char *command)
{
    char *path = getenv("PATH");
    char path_copy[MAX_INPUT_SIZE];
    int command_found = 0; /* Flag to check if the command exists */
    char *token;
    char *cmd;
    int token_start = 0;

    if (path == NULL)
    {
        perror("Error getting PATH");
        return -1;
    }

    strncpy(path_copy, path, sizeof(path_copy));
    path_copy[sizeof(path_copy) - 1] = '\0';

    token = path_copy;

    while (path_copy[token_start] != '\0')
    {
        if (path_copy[token_start] == ':')
        {
            path_copy[token_start] = '\0'; /* Null-terminate the token */
            cmd = malloc(strlen(token) + strlen(command) + 2);

            if (cmd == NULL)
            {
                perror("Malloc failed");
                return -1;
            }

            sprintf(cmd, "%s/%s", token, command);

            if (access(cmd, X_OK) == 0)
            {
                /* Command is accessible, execute it */
                free(cmd);
                command_found = 1; /* Set the flag to indicate command existence */
                break;
            }

            free(cmd);
            token_start++;
            token = path_copy + token_start;
        }
        else
        {
            token_start++;
        }
    }

    if (command_found)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            return -1;
        }

        if (pid == 0)
        {
            /* Extract the command name */
            char *command_name = command;
            char *argv[MAX_ARG_SIZE]; /* An array to store command and arguments */
            int i = 0;

            while (*command_name != '\0')
            {
                /* Skip leading spaces */
                while (*command_name == ' ')
                {
                    command_name++;
                }

                if (*command_name == '\0')
                {
                    break;
                }

                /* Save the current argument */
                argv[i] = command_name;
                i++;

                /* Find the end of the current argument */
                while (*command_name != ' ' && *command_name != '\0')
                {
                    command_name++;
                }

                if (*command_name != '\0')
                {
                    *command_name = '\0'; /* Null-terminate the argument */
                    command_name++;
                }
            }

            argv[i] = NULL; /* Null-terminate the array */

            if (execvp(argv[0], argv) == -1)
            {
                perror("execvp failed");
                return -1; /* Command not found */
            }
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }
        return 0;
    }
    else
    {
        fprintf(stderr, "Command not found: %s\n", command);
        return -1;
    }
}