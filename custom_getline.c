#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    char *buffer = NULL;
    size_t size = 0;
    size_t len = 0;
    int c;
    char *new_buffer = NULL;

    if (lineptr == NULL || n == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    while (1)
    {
        c = fgetc(stream);

        if (c == EOF || c == '\n')
        {
            if (c == EOF && (!buffer || len == 0))
            {
                return -1; /* No more data to read */
            }

            if (len + 1 >= size)
            {
                size = (len + 1) * 2;
                new_buffer = (char *)realloc(buffer, size);

                if (!new_buffer)
                {
                    free(buffer);
                    return -1; /* Allocation error */
                }

                buffer = new_buffer;
            }

            if (c == EOF)
            {
                buffer[len] = '\0';
                break;
            }

            buffer[len] = '\n';
            buffer[len + 1] = '\0';
            break;
        }

        if (len + 1 >= size)
        {
            size = (len + 1) * 2;
            new_buffer = (char *)realloc(buffer, size);

            if (!new_buffer)
            {
                free(buffer);
                return -1; /* Allocation error */
            }

            buffer = new_buffer;
        }

        buffer[len] = (char)c;
        buffer[len + 1] = '\0';
        len++;
    }

    *lineptr = buffer;
    *n = size;

    return len;
}