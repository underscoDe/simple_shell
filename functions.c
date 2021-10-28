#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "tests/utils/headers.h"
#include <stdlib.h>

/* 
* returns the full path of a command name if it is contained in the given
* syspath otherwise returns an empty string. The memory of returned string
* should be freed after use.
*
* command: e.g grep
* syspath: same as that gotten via $PATH in bash
*/
char *_which(char *command, char *syspath){

    int i, j;
    char *search_path = NULL; // to be returned
    
    int path_length, command_length, fullpath_length;
    for(path_length = 0; syspath[path_length]; path_length++); // get path_length
    for(command_length = 0; command[command_length]; command_length++); // get command length
    fullpath_length = path_length + command_length;

    // create tokenizable arg 
    char args_tokenizable[fullpath_length + 2];
    for (i = 0; i < command_length; i++)
        args_tokenizable[i] = command[i];

    args_tokenizable[i++] = ':';

    for (j = 0; j < path_length; i++, j++)
        args_tokenizable[i] = syspath[j];

    char **splitted = split(args_tokenizable, ":");
    // --at this point it is like: grep,/path1,/path2...-- (tested)
    

    char *subpath;
    struct stat stat_buffer; // stores a struct of the file information if filepath valid
    i = 1;
    while ( (subpath = splitted[i++]) != NULL){
        int len_subpath;
        for (len_subpath = 0; subpath[len_subpath]; len_subpath++); //get length of subpath

        // get string of command/subpath AND test for its existence
        search_path = malloc(command_length + len_subpath + 1); // +1 for '/' in /filename
        int x, y;
        for (x = 0, y = 0; y < len_subpath; x++,y++)
            search_path[x] = subpath[y];

        search_path[x++] = '/'; // for '/commandName' e.g /grep

        for (y = 0; y < command_length; x++, y++)
            search_path[x] = command[y];
            

        search_path[x] = '\0';

        // if path valid, return it
        if (stat(search_path, &stat_buffer) == 0){
            // puts(search_path);
            return search_path;
        }
    }
    return "\0";    
}
