#include "header_file.h"

int execute_command(char *command)
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
            return -1; /* Command not found */
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}