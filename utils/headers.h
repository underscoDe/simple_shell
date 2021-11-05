#ifndef HEADERS_H
#define HEADERS_H
#include <stdbool.h>

char **split(char *raw_cmd, char *limit);
void free_array(char **array);
void exec_cmd(char **cmd, char **env);
bool get_absolute_path(char **cmd, char **env);

#endif /* HEADERS_H */
