#include "header_file.h"
#include "args_parser.h"

int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        print_prompt(); /* Display the prompt */
        if (custom_getline(input, MAX_INPUT_SIZE) == -1)
        { /* Use custom_getline */
            printf("\n");
            break; /* Handle Ctrl+D (end of file) */
        }

        /* Remove the trailing newline */
        input[strcspn(input, "\n")] = '\0';

        if (execute_command(input) == -1)
            perror(input); /* Print an error message */
    }

    return EXIT_SUCCESS;
}