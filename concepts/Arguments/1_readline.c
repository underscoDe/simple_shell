#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    char *buffer;
    size_t len = 1;
    ssize_t nread;

    buffer = (char*) malloc(len * sizeof(char));

    printf("$ ");
    nread = getline(&buffer, &len, stdin);
    printf("Command entered: %s", buffer);
    printf("Characters (newline inclusive): %lu\n", nread);
    printf("Buffer Length (newline + null terminator inclusive): %lu\n", len);

    free(buffer);
}