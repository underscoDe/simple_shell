#ifndef BUILTINS_H
#define BUILTINS_H

void built_in_cd(char *path);
char *built_in_pwd(void);
bool is_built_in(char *cmd);
void exec_built_in(char **built_in);

char *get_env_var(char *var);

#endif /* BUILTINS_H */
