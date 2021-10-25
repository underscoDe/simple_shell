#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "errors/errors.h"

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

	buffer = (char *)calloc(sizeof(char), buffer_size);
	if (buffer == NULL)
	{
		perror(MALLOC_FAILED);
		return (EXIT_FAILURE);
	}

	/* prompt writing to the standard output (console) */
	write(1, "$> ", 3);

	/* reading STDIN in loop */
	while (getline(&buffer, &buffer_size, stdin) > 0)
	{
		printf("cmd = %s\n", buffer);
		write(1, "$> ", 3);
	}

	/* when the user types CTRL + D (abort) */
	printf("See you ^^\n");
	free(buffer);
}
