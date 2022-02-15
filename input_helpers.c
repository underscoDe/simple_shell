#include "minishell.h"


/**
 * get_user_input - read user input from stdin
 *
 * Return: the user input string
 */
char *get_user_input()
{
    int bufsize = BUFFER_SIZE, pos = 0, c;
    char *input = malloc(bufsize * sizeof(char));

    if (!input) return (NULL);

    while (true)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            input[pos] = '\0';

            return (input);
        }
        else
        {
            input[pos] = c;
        }
        pos++;

        if (pos >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            input = realloc(input, bufsize);

            if (!input) return (NULL);
        }
    }

}