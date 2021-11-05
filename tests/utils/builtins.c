#include <unistd.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
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
	t_env *tmp = first;
	size_t len = 0;

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
 * add_tail - add an env var to a list end
 * @var: variable name
 *
 * Return: nothing
*/
void add_tail(char *var)
{
	t_env *ptr = first;
	t_env *new_node = NULL;

	new_node = (t_env *)calloc(sizeof(t_env), 1);
	if (new_node == NULL)
	{
		printf("Alloc failure\n");
		return ;
	}

	new_node->var = var;
	new_node->next = NULL;

	if (ptr == NULL)
	{
		first = new_node;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

/**
 * add_env_var - add a new env var
 * @var: variable name
 *
 * Return: nothing
*/
void add_env_var(char *var)
{
	struct passwd *pw = getpwuid(getuid());
	char *alloc = NULL;

	if (!strcmp(var, "HOME"))
	{
		alloc = (char *)calloc(sizeof(char),
			strlen(pw->pw_dir) + strlen("HOME=") + 1);
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add HOME\n");
			return ;
		}
		strcat(alloc, "HOME=");
		strcat(alloc, pw->pw_dir);
	}
	else if (!strcmp(var, "PATH"))
	{
		alloc = strdup("PATH=/bin:/usr/bin");
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add PATH\n");
			return ;
		}
	}
	else if (!strcmp(var, "OLDPWD"))
	{
		alloc = strdup("OLDPWD=");
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add OLDPWD\n");
			return ;
		}
	}
	else if (!strcmp(var, "PWD"))
	{
		alloc = built_in_pwd();
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add PWD\n");
			return ;
		}
	}
	else if (!strcmp(var, "SHLVL"))
	{
		alloc = strdup("SHLVL=1");
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add OLDPWD\n");
			return ;
		}
	}

	add_tail(alloc);
}

/**
 * dup_env - duplicate an env var
 * @envp: env var list
 *
 * Return: nothing
*/
void dup_env(char **envp)
{
	int i = 0;
	char *var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	/* number of elements in var_lst */
	ssize_t	nb_elem = 5;

	/* loop over env and stock variable in the list */
	for (; envp[i]; i++) {
		add_tail(strdup(envp[i]));

		/* we check if we have the minimal env vars */
		if (!strncmp(envp[i], "PATH", 4)) var_lst[0] = NULL;
		else if (!strncmp(envp[i], "HOME", 4)) var_lst[1] = NULL;
		else if (!strncmp(envp[i], "OLDPWD", 6)) var_lst[2] = NULL;
		else if (!strncmp(envp[i], "PWD", 3)) var_lst[3] = NULL;
		else if (!strncmp(envp[i], "SHLVL", 5)) var_lst[4] = NULL;
	}

	/* do we have PATH, HOME, OLD_PWD and SHLVL ?
	we add them if we don't */
	for (i = 0; i < nb_elem; i++) {
		if (var_lst[i] != NULL)
			add_env_var(var_lst[i]);
	}
}

/**
 * built_in_env - prints env var
 *
 * Return: nothing
*/
void built_in_env(void)
{
	t_env *tmp = first;

	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
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
	const char *built_in[] = {"pwd", "cd", "env", NULL};
	int i = 0;

	for (; built_in[i]; i++) {
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
		printf("%s\n", get_env_var("PWD="));
	else if (!strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
	else if (!strcmp(built_in[0], "env"))
		built_in_env();
}

/**
 * built_in_cd - changes directory
 * @path: given directory
 *
 * Return: nothing
*/
void built_in_cd(char *path)
{
	char *oldpwd = NULL;
	char *pwd = NULL;
	char *pwd_ptr = NULL;

	if (path == NULL)
		return;

	if (chdir(path) == 0) {
		pwd = strrchr(get_env_var("PWD="), '=') + 1;
		oldpwd = strrchr(get_env_var("OLDPWD="), '=') + 1;

		if (oldpwd != NULL && pwd != NULL) {
			strcpy(oldpwd, pwd);
		}
		if (pwd != NULL) {
			pwd = &pwd[-strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			strcpy(pwd, pwd_ptr);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	} else {
		perror("chdir");
	}
}

/**
 * built_in_pwd - prints the working directory
 *
 * Return: current working dir
*/
char *built_in_pwd(void)
{
	char *cwd = NULL;

	/* we allocate : PWD= + PATH_MAX + 1 for \0 ending char */
	cwd = (char *)calloc(sizeof(char), PATH_MAX + strlen("PWD=") + 1);
	if (cwd == NULL)
		return (NULL);

	/* we concat the var name */
	strcat(cwd, "PWD=");

	/* then we stock current path after the = of PATH= */
	if (getcwd(&cwd[4], PATH_MAX) == NULL) {
		perror("getcwd()");
	}

	return (cwd);
}