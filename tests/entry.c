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
 * Return: returns EXIT_FAILURE OF EXIT_SUCCESS
 *
 */
int main()
{
	/* buffer will stock the user input command,
	we'll give it a size of 2048 */
	char *buffer = NULL;
	size_t buffer_size = 2048;
	char	**cmd = NULL;

	buffer = (char *)calloc(sizeof(char), buffer_size);
	if (buffer == NULL)
	{
		perror("Memory allocation failed");
		return (EXIT_FAILURE);
	}

	/* prompt writing to the standard output (console) */
	write(1, "($) ", 4);

	/* reading STDIN in loop */
	while (getline(&buffer, &buffer_size, stdin) > 0)
	{
		cmd = split(buffer, " \n\t");
		get_absolute_path(cmd);

		if (cmd[0] == NULL)
			printf("%s\n", "Command not found");
		else if (is_built_in(cmd[0]) == false)
		{
			get_absolute_path(cmd);
			exec_cmd(cmd);
		}
		else
			exec_built_in(cmd);

		write(1, "($) ", 4);
		free_array(cmd);
	}

	/* when the user types CTRL + D (abort) */
	printf("Bye !\n");
	free(buffer);
}
