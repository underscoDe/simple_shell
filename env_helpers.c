#include "minishell.h"
#include <stdlib.h>
#include <string.h>

/**
 * getenvcopy - creates a copy of the environment
 *
 * Return: a double pointer to the created copy
 *         or NULL if any error occurs
 */
char **getenvcopy(void)
{
    char **envcopy;
    size_t envsize = 0;
    int i = 0;

    /* get the environment size */
    for (; environ[envsize]; envsize++);

    /* try to give envcopy the same dimensions as environ */
    /* if any malloc fails, we free the memory and return NULL */
    envcopy = malloc(sizeof(char *) * (envsize + 1));

    if (!envcopy)
        return NULL;

    for (; i < envsize; i++)
    {
        envcopy[i] = malloc(strlen(environ) + 1);

        if (!envcopy[i])
        {
            for (i--; i >= 0; i--)
                free(envcopy[i]);
            free(envcopy);
            return (NULL);
        }
        strcpy(envcopy[i], environ[i]);
    }

    envcopy[i] = NULL;

    return (envcopy);
}
