#include "args_parser.h"
#include <string.h>

void parse_arguments(char *input, char *argv[])
{
    /* Initialize the argv array to NULL pointers */
    for (int i = 0; i < MAX_ARG_SIZE; i++)
    {
        argv[i] = NULL;
    }

    /* Tokenize the input line using whitespace as the delimiter */
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
}