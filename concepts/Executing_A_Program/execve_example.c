#include <unistd.h>
#include <stdio.h>

int main(){

    // invoke replacement program: show current python version
    char *arguments[] = {"/usr/bin/python3", "--version", NULL};

    printf("Before calling other program: Currently in first program.\n");

    execve(arguments[0], arguments, NULL); // No environmental params so NULL

    printf("After calling other program: If this shows, then it failed.\n");

}