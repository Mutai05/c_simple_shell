#include "header_file.h"
#include "args_parser.h"
#include <string.h>

void parse_arguments(char *input, char *argv[])
{
    int i = 0;
    char *start = input;

    /* Initialize the argv array to NULL pointers */
    for (i = 0; i < MAX_ARG_SIZE; i++)
    {
        argv[i] = NULL;
    }

    i = 0;
    while (*start != '\0' && i < MAX_ARG_SIZE)
    {
        /* Skip leading spaces */
        while (*start == ' ')
        {
            start++;
        }

        if (*start == '\0')
        {
            break;
        }

        /* Save the current argument */
        argv[i] = start;
        i++;

        /* Find the end of the current argument */
        while (*start != ' ' && *start != '\0')
        {
            start++;
        }

        if (*start != '\0')
        {
            *start = '\0'; /* Null-terminate the argument */
            start++;
        }
    }
}