#ifndef BUILTINS_H
#define BUILTINS_H

void built_in_cd(char *path);
void built_in_pwd(void);
bool is_built_in(char *cmd);
void exec_built_in(char **built_in);

#endif /* BUILTINS_H */
