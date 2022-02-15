#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/**
 * enum _bool - enumeration to use true and false
 * @false: 0
 * @true: 1
 */
typedef enum _bool
{
    false = 0,
    true = 1
} Bool;

typedef enum errors
{
    READLINE = 0
} Errors;

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

/**
 * struct builtin_s - defines builtin commands
 * @name: the builtin command's name
 * @f: function pointer to the builtin command
 */
typedef struct builtin_s
{
    char *name;
    int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - defines aliases
 * @name: alias' name
 * @value: alias' value
 * @next: a pointer to the next alias
 */
typedef struct alias_s
{
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

#endif /* TYPEDEFS_H */