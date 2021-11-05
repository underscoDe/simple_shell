#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
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

/**
 * exec_cmd - executes the given command
 * @cmd: command to be executed
 * @env: environment
 *
 * Return: nothing
 */
void exec_cmd(char **cmd, char **env)
{
	pid_t pid = 0;
	int status = 0;

	/* we duplicate the current process */
	pid = fork();
	if (pid == -1)
		perror("Failed to duplicate process");
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
		if (execve(cmd[0], cmd, env) == -1)
			perror("Shell error");
		exit(EXIT_FAILURE);
	}
}

/**
 * get_absolute_path - get a command's absolute path
 * @cmd: command
 * @env: env var list
 *
 * Return: true or false whether binary exist or not
 */
bool get_absolute_path(char **cmd, char **env)
{
	char *path = NULL;
	char *bin = NULL;
	char **path_split = NULL;
	size_t idx = 0;
	int i = 0;

	/* if cmd isn't the absolute path, we search the absolute */
	/* path of the binary using PATH env var */
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{

		/* we search the PATH ; if we don't find it, */
		/* we can't concatenate then we exit */
		for (; env[i]; i++)
		{
			if (!strncmp(env[i], "PATH=", 5))
			{
				path = strdup(&env[i][5]);
				break;
			}
		}
		if (path == NULL)
			return (false);

		/* we split the path to find the binary */
		path_split = split(path, ":");
		free(path);
		path = NULL;

		/* we loop over each folder of the path to find the binary */
		for (idx = 0; path_split[idx]; idx++)
		{
			/* path length + '/' + binary length + 1 (for '\0') */
			bin = (char *)calloc(sizeof(char),
				(strlen(path_split[idx]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break;

			/* we concat the path, the '/' and the binary name */
			strcat(bin, path_split[idx]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);

			/* return 0 if the file doesn't exist */
			if (access(bin, F_OK) == 0)
				break;

			/* no waste of memory :D */
			free(bin);
			bin = NULL;
		}
		free_array(path_split);

		/* we replace the binary with the absolute path */
		/* or NULL of it doesn't exist */
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}

	/* if the binary exists, return true */
	return (bin == NULL ? false : true);
}
