#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "headers.h"
#include "../errors/errors.h"

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

/**
 * exec_cmd - executes the given command
 * @cmd: command to be executed
 *
 * Return: nothing
 */
void exec_cmd(char **cmd)
{
	pid_t pid = 0;
	int status = 0;

	/* we duplicate the current process */
	pid = fork();
	if (pid == -1)
		perror(FORK_ERROR);
	/* if fork() works, the parent process wait for its child */
	else if (pid > 0)
	{
		/* we block the parent process until its child ends */
		waitpid(pid, &status, 0);
		/* then we kill the child */
		kill(pid, SIGTERM);
	}
	else
	{
		/* child process executes the command or quit whether execve fails */
		if (execve(cmd[0], cmd, NULL) == -1)
			perror(SHELL);
		exit(EXIT_FAILURE);
	}
}
