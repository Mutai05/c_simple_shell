#include "header_file.h"

int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        print_prompt(); /* Display the prompt */
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        {
            printf("\n");
            break; /* Handle Ctrl+D (end of file) */
        }

        input[strcspn(input, "\n")] = '\0'; /* Remove the trailing newline */

        if (execute_command(input) == -1)
            perror(input); /* Print an error message */

        /* Handle other error conditions as needed */
    }

    return EXIT_SUCCESS;
}
