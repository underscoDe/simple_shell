#include "minishell.h"

/**
 * readline_error - User input reading error
 *
 * Return: nothing
 */
void readline_error(void)
{
	char *err = strcat(strcat(name, ": "), READLINE_ERROR);

	write(2, err, strlen(err));
	exit(EXIT_FAILURE);
}
