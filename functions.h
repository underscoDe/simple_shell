#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char *_which(char *command, char *syspath);
int string_in(char *main_string, char *sub_string);
int string_w_match(char *main_string, char *sub_string);

/* error messages */
const char *MALLOC_FAILED = "Memory allocation failed";
const char *FORK_FAILED = "Program fork failed";
const char *INVALID_COMMAND = "Invalid command";

#endif /* FUNCTIONS_H */