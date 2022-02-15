#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "typedefs.h"
#include "constants.h"


/* global environemnt */
extern char **environ;
/* global program name */
char *name;
/* global aliases linked list */
alias_t *aliases;

void signal_handler(int fildes);

#endif /* _MINISHELL_H_ */