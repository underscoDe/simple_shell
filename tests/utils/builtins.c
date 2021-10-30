#include <unistd.h>

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
