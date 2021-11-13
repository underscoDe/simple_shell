#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#define END_OF_FILE -2;
#define EXIT -3;

/* environemnt */
extern char **environ;
/* program name */
char *name;
/* history counter */
int hist;

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



void signal_handler(int fildes);

#endif /* _MINISHELL_H_ */