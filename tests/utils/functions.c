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
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("Shell");
		exit(EXIT_FAILURE);
	}
}

/**
 * get_absolute_path - get a command's absolute path
 * @cmd: command
 *
 * Return: true or false whether binary exist or not
 */
bool get_absolute_path(char **cmd)
{
	char *path = strdup(getenv("PATH"));
	char *bin = NULL;
	char **path_split = NULL;
	int i = 0;

	/* if path is null, we create a new path */
	if (path == NULL)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	/* if cmd is not the absolute path, we check the absolute path
	using the environment variable PATH */
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		// we split the path to find where the binary is
		path_split = split(path, ":");
		free(path);
		path = NULL;

		/* we loop over each folder of the path to get it found */
		for (; path_split[i]; i++)
		{
			/* alloc len of path + '/' + len of binary + 1 for the '\0' */
			bin = (char *)calloc(sizeof(char),
				(strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break;

			/* we concat the path , the '/' and the binary name */
			strcat(bin, path_split[i]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);

			/* we check if the file exists, we quit the loop when access = 0 */
			if (access(bin, F_OK) == 0)
				break;

			free(bin);
			bin = NULL;
		}
		free_array(path_split);

		/* we replace the binary with the absolute path
		or NULL if the binary doesn't exist */
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}

	/* we return true when the binary exists */
	return (bin == NULL ? false : true);
}

