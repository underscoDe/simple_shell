#ifndef HEADERS_H
#define HEADERS_H

char **split(char *raw_cmd, char *limit);
void free_array(char **array);
void exec_cmd(char **cmd);
void get_absolute_path(char **cmd);

#endif /* HEADERS_H */
