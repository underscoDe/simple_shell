#include "minishell.h"

/**
 * memalloc_error - Memory allocation error
 *
 * Return: nothing
 */
void memalloc_error(void)
{
    char *err = strcat(strcat(name, ": "), MEM_ALLOCATION_ERROR);

    write(2, err, strlen(err));
    exit(EXIT_FAILURE);
}
