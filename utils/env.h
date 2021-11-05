#ifndef ENV_H
#define ENV_H

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

char *get_env_var(char *var);
void add_env_var(char *var);
void dup_env(char **envp);

#endif /* ENV_H */
