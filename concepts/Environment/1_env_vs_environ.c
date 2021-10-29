#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main(int n_args, char **args, char **env)
{
    printf("Address of env: %p\n", &env);
    printf("Address of environ: %p\n", &environ);
}