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
        if (execlp(command, command, NULL) == -1)
            return -1; /* Command not found */
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
