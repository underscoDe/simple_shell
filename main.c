#include "minishell.h"
#include <stddef.h>
#include <signal.h>

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
    int retval = 0, retnval;
    int *retnval_ptr = &retnval;
    char *prompt = "($) ", newline = "\n";

    /* we get the program name in the variable */
    /* name which is a global variable */
    name = argv[0];
    /* set history count to 1 */
    hist = 1;
    /* initialize aliases to NULL */
    aliases = NULL;
    /* send SIGINT signal to print a new prompt */
    signal(SIGINT, signal_handler);

    /* initialize retnval to 0 */
    *retnval_ptr = 0;
    /* get a copy of the environment variable */
    environ = getenvcopy();

    return (0);
}
