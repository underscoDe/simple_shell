#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "typedefs.h"
#include "constants.h"


/* global environemnt */
extern char **environ;
/* global program name */
char *name;
/* global aliases linked list */
alias_t *aliases;

/* signals and processes */
void signal_handler(int);

/* helpers for user inputs */
char *get_user_input();

/* helpers errors handling */
/* 0 : readline_error */
void readline_error(void);

void (*handle_error[])(void) = {
    readline_error
};

#endif /* _MINISHELL_H_ */