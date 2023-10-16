#include "args_parser.h"
#include <string.h>

void parse_arguments(char *input, char *argv[])
{
    int i; /* Declare 'i' before the loop */

    /* Initialize the argv array to NULL pointers */
    for (i = 0; i < MAX_ARG_SIZE; i++)
    {
        argv[i] = NULL;
    }

    /* Tokenize the input line using whitespace as the delimiter */
    char *token = strtok(input, " ");
    i = 0; /* Reuse 'i' for the loop */

    while (token != NULL)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
}