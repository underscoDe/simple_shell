#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "tests/errors/errors.h"
#include <string.h>
#include "tests/utils/headers.h"
#include "functions.h"

/**
 * main - Entry point
 *
 * Return: returns EXIT_FAILURE OF EXIT_SUCCESS
 *
 */
int main(int n_args, char **args, char **env)
{
	char *syspath = args[1];


	/* buffer will stock the user input command,
	we'll give it a size of 2048 */
	char *buffer = NULL;
	size_t buffer_size = 2048;
	int wait_status;
	pid_t child_pid;
	int i;

	buffer = (char *)calloc(sizeof(char), buffer_size);
	if (buffer == NULL)
	{
		perror(MALLOC_FAILED);
		return (EXIT_FAILURE);
	}

	/* prompt writing to the standard output (console) */
	write(1, "($) ", 4);

	/* reading STDIN in loop */
	while (getline(&buffer, &buffer_size, stdin) > 0)
	{
		/* IMPORTANT! -- nullify the newline character from buffer */
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == '\n')
			buffer[i] = '\0';
		}

		printf("cmd = %s\n", buffer);
		write(1, "($) ", 4);

		/* create fork for executing the command entered */
		child_pid = fork();
		if (child_pid == -1)  /* fork failure */
		{
			write(1, FORK_FAILED, strlen(FORK_FAILED) );
		}

		else if (child_pid > 0)  /* parent of fork */
		{
			wait(&wait_status);
		}

		else if (child_pid == 0)  /* child of fork */
		{
			/* execute the command entered */
			char **buffer_args = split(buffer, " ");  /* get separate arguments */

			struct stat stat_buffer; // stores a struct of the file information if filepath valid
			int path_status = stat(buffer_args[0], &stat_buffer); // 0 if path valid else -1

			if (path_status == 0) // command is a valid path
				execve(buffer_args[0], buffer_args, NULL);

			else if ( (path_status = stat(_which(buffer_args[0], syspath), &stat_buffer) ) == 0) // _which <command> is valid path
				execve(_which(buffer_args[0], syspath), buffer_args, NULL);

			else // command is invalid, so cast an error
				perror(INVALID_COMMAND);			

		}
			
	}

	/* when the user types CTRL + D (abort) */
	printf("See you ^^\n");
	free(buffer);
}
