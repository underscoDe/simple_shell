#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "headers.h"

/**
 * split - splits command input into parts
 * @raw_cmd: command string to split
 * @sep: separator (for strtok function)
 *
 * Return: splited command input
 */
char **split(char *raw_cmd, char *sep)
{
	char *strToken = NULL;
	char **command = NULL;
	size_t index = 0;

	/* split on spaces */
	strToken = strtok(raw_cmd, sep);

	while (strToken)
	{
		command = (char **)realloc(command, ((index + 1) * sizeof(char *)));
		command[index] = strdup(strToken);
		strToken = strtok(NULL, sep);
		index++;
	}

	/* allocation of an element set to NULL at the end of the tab */
	command = (char **)realloc(command, ((index + 1) * sizeof(char *)));
	command[index] = NULL;

	return (command);
}

/**
 * free_array - free two dim. array
 * @array: array to free up
 *
 * Return: nothing
 */
void free_array(char **array)
{
	int i = 0;

	for (; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}

	free(array);
	array = NULL;
}
