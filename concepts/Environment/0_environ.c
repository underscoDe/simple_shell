#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main()
{
    for(int i = 0; environ[i]; i++)
        puts(environ[i]);
}