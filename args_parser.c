#include "header_file.h"
#include "args_parser.h"
#include <string.h>

void parse_arguments(char *input, char *argv[])
{
    int i;       /* Declare 'i' before the loop */
    char *token; /* Declare 'token' here */

    /* Initialize the argv array to NULL pointers */
    for (i = 0; i < MAX_ARG_SIZE; i++)
    {
        argv[i] = NULL;
    }

    token = strtok(input, " "); /* Initialize 'token' here */

    /* Reuse 'i' for the loop */
    i = 0;

    while (token != NULL)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
}