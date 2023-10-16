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
        char *argv[MAX_ARG_SIZE];       /* An array to store command and arguments */
        parse_arguments(command, argv); /* Implement a function to parse arguments */
        if (execve(argv[0], argv, NULL) == -1)
            return -1; /* Command not found */
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}