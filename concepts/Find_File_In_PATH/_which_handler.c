#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int n_args, char **arguments){

    /*
    HOW THIS WORKS
    - user will call batch script "_which"
    - _which will echo filename:PATH as input to c program, "_which_handler"
    - the c program "_which_handler" will then process the PATH together with filename and display result

    c file: _which_handler.c
    */

    if (n_args < 2)
        return 1;
    
    // char *arguments[] = {"main", "grep:/home/flashxy/.local/bin:/home/flashxy/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin", NULL}; // replace this with the main args
    int arg_length;
    for(arg_length = 0; arguments[1][arg_length]; arg_length++); // get arg_length

    // create tokenizable arg 
    char args_tokenizable[arg_length];
    for (int i = 0; i< arg_length; i++)
        args_tokenizable[i] = arguments[1][i];
    
    // tokens
    char *filename = strtok(args_tokenizable, ":");
    int len_filename;
    for (len_filename = 0; filename[len_filename]; len_filename++); //get length of filename

    char *path;
    struct stat stat_buffer; // stores a struct of the file information if filepath valid
    while ( (path = strtok(NULL, ":")) != NULL){
        int len_path;
        for (len_path = 0; path[len_path]; len_path++); //get length of path

        // get string of filename/path AND test for its existence
        char search_path[len_filename + len_path + 1]; // +1 for '/' in /filename
        int i, j;
        for (i = 0, j = 0; j < len_path; i++,j++)
            search_path[i] = path[j];

        search_path[i++] = '/'; // /filename

        for (j = 0; j < len_filename; i++, j++)
            search_path[i] = filename[j];
            

        search_path[i] = '\0';

        // if path valid, display it and exit
        if (stat(search_path, &stat_buffer) == 0){
            puts(search_path);
            return 0;
        }
    }

    
}