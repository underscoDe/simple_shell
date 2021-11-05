#ifndef BUILTINS_H
#define BUILTINS_H

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

bool is_built_in(char *cmd);
void exec_built_in(char **built_in);

void built_in_cd(char *path);
char *built_in_pwd(void);
void built_in_env(void);

char *get_env_var(char *var);
void add_tail(char *var);
void add_env_var(char *var);
void dup_env(char **envp);
char **lst_to_array();
void free_lst(void);

#endif /* BUILTINS_H */
