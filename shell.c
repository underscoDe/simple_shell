#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "tests/errors/errors.h"
#include <string.h>
#include "tests/utils/headers.h"

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
			char **args = split(buffer, " ");  /* get separate arguments */
			execve(args[0], args, NULL);
		}
			
	}

	/* when the user types CTRL + D (abort) */
	printf("See you ^^\n");
	free(buffer);
}
