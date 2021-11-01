#ifndef BUILTINS_H
#define BUILTINS_H

bool is_built_in(char *cmd);
void exec_built_in(char **built_in);

void built_in_cd(char *path);
char *built_in_pwd(void);
void built_in_env(void);

char *get_env_var(char *var);
void add_tail(char *var);

#endif /* BUILTINS_H */
