#include "minishell.h"


/**
 * get_user_input - read user input from stdin
 *
 * Return: the user input string
 */
char *get_user_input()
{
	char *input = NULL;
	size_t len = 0;

	if (getline(&input, &len, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			(*handle_error[READLINE])();
		}
	}

	return (input);

}
