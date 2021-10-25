#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int n_args, char **args){
    
    struct stat stat_buffer; // stores a struct of the file information if filepath valid

    int result = stat("/usr/bin/ls", &stat_buffer); // returns 0 if path valid, -1 if path not valid

    if (result == 0)
        puts("File Found");

    else if(result == -1)
        puts("File not Found");
}