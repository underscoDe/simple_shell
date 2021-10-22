#include <string.h>
#include <stdio.h>

int main() {

    char string[] = "I went out|with an|umbrella";
    char *delimiter = "|";
    char *split_part;

    printf("Tokens from split:\n----------------\n");

    // first token (tokens are split parts)
    split_part = strtok(string, delimiter);
    printf("%s\n", split_part);

    // other tokens
    while( (split_part = strtok(NULL, delimiter) ) != NULL )
        printf("%s\n", split_part);


}