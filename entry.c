#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils/headers.h"
#include "utils/builtins.h"

/**
 * main - Entry point
 *
 * Return: returns 0
 *
 */
int	main(int argc, char **argv, char **envp)
{
	char *buffer = NULL;
	size_t buf_size = 2048;
	char **cmd = NULL;
	char **env = NULL;

	dup_env(envp);

	/* allocate buffer to stock user input */
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL) {
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}

	/* prompt */
	write(1, "($) ", 4);

	/* reading STDIN in loop */
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = split(buffer, " \n\t");

		if (cmd[0] == NULL)
			fprintf(stderr, "Command not found\n");
		else if (is_built_in(cmd[0]) == true)
		{
			exec_built_in(cmd);
		}
		else
		{
			env = lst_to_array();
			if (get_absolute_path(cmd, env) == true)
			{
				exec_cmd(cmd, env);
			}
			else
			{
				fprintf(stderr, "Command not found\n");
			}
			free(env);
			env = NULL;
		}

		write(1, "($) ", 4);
		free_array(cmd);

	}

	free_lst();
	printf("Bye \n");
	free(buffer);

	(void)argc;
	(void)argv;

	return (0);
}
