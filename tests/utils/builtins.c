#include <unistd.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "builtins.h"

/**
 * struct s_env - Environment variables
 * @var: element
 * @next: pointer to next element
 */
typedef struct s_env
{
	char *var;
	struct s_env *next;
}t_env;

t_env *first = NULL;

/**
 * get_env_var - helps get env variable
 * @var: variable name
 *
 * Return: variable
*/
char *get_env_var(char *var)
{
	t_env	*tmp = first;
	size_t	len = 0;

	len = strlen(var);

	while (tmp)
	{
		if (!strncmp(var, tmp->var, len))
			return (tmp->var);

		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * is_built_in - checks whether a command is a builtin or not
 * @cmd: given command
 *
 * Return: boolean true when it is, false when it's not
*/
bool is_built_in(char *cmd)
{
	/* this list will be update as we add new builtins */
	const char *built_in[] = {"pwd", "cd", NULL};

	for (int i = 0; built_in[i]; i++) {
		if (!strcmp(built_in[i], cmd))
			return (true);
	}

	return (false);
}

/**
 * exec_built_in - executes a builtin
 * @built_in: given builtin
 *
 * Return: nothing
*/
void exec_built_in(char **built_in)
{
	if (!strcmp(built_in[0], "pwd"))
		built_in_pwd();
	else if (!strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
}

/**
 * built_in_cd - changes directory
 * @path: given directory
 *
 * Return: nothing
*/
void built_in_cd(char *path)
{
	if (chdir(path) == -1) {
		perror("chdir()");
	}
}

/**
 * built_in_pwd - prints the working directory
 *
 * Return: nothing
*/
void built_in_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		   printf("%s\n", cwd);
	} else {
		perror("getcwd()");
	}
}
