#include "minishell.h"


/**
 * main - entry point
 *
 * @argc: number of arguments given to the program
 * @argv: arguments list
 *
 * Return: returns the value of the last executed command
 */
int main(int argc, char **argv)
{
    char *cmdline = NULL;
    char **cmdargs;
    char prompt[] = "(hsh) ";
    Bool status = true;

    while (status)
    {
        write(1, prompt, strlen(prompt));
        cmdline = get_user_input();
    }

    return (0);
}
