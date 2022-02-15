#include <signal.h>
#include <unistd.h>
#include "minishell.h"

/**
 * signal_handler - prints a new prompt upon a signal
 * @fildes: file descriptor
 *
 * Return: nothing
 */
void signal_handler(int fildes)
{
	char *prompt = "\n($) ";

	(void)fildes;
	signal(SIGINT, signal_handler);
	write(STDIN_FILENO, prompt, 3);
}

