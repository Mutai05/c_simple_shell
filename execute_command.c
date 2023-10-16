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
    char *token, *cmd;
    char path_copy[MAX_INPUT_SIZE];
    int command_found = 0; /* Flag to check if the command exists */

    if (path == NULL)
    {
        perror("Error getting PATH");
        return -1;
    }

    strncpy(path_copy, path, sizeof(path_copy));
    path_copy[sizeof(path_copy) - 1] = '\0';

    token = strtok(path_copy, ":");

    while (token != NULL)
    {
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
        token = strtok(NULL, ":");
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
            char *command_name = strtok(command, " "); /* Extract the command name */
            char *argv[MAX_ARG_SIZE];                  /* An array to store command and arguments */
            int i = 0;

            while (command_name != NULL)
            {
                argv[i] = command_name;
                i++;
                command_name = strtok(NULL, " ");
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