#ifndef BUILTINS_H
#define BUILTINS_H

bool is_built_in(char *cmd);
void exec_built_in(char **built_in);
void built_in_cd(char *path);
char *built_in_pwd(void);
void built_in_env(void);


#endif /* BUILTINS_H */
