#include <unistd.h>
#include <linux/limits.h>

/**
 * built_in_cd - changes directory
 * @path: given directory
 *
 * Return: nothing
*/
void	built_in_cd(char *path)
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
