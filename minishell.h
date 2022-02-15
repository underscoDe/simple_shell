#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


/* global environemnt */
extern char **environ;
/* global program name */
char *name;

/**
 * struct list_s - struct defining a linked list
 * @dir: a directory path
 * @next: a pointer to another struct list_s
 */
typedef struct list_s
{
    char *dir;
    struct list_s *next;
} list_t;

/**
 * struct builtin_s - defines builtin commands
 * @name: the builtin command's name
 * @f: function pointer to the builtin command
 */
typedef struct builtin_s
{
    char *name;
    int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - defines aliases
 * @name: alias' name
 * @value: alias' value
 * @next: a pointer to the next alias
 */
typedef struct alias_s
{
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

/* global aliases linked list */
alias_t *aliases;

void signal_handler(int fildes);

char **getenvcopy(void);

#endif /* _MINISHELL_H_ */