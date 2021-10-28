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

/*
* returns 1 if substring contained in main_string
* example: "apple" is contained in  "apple  ",   "  apple  "   AND   "  apple"
*          but not in "napple  ",  "  zapples  "  OR  "  grapple"
*
*/
int string_in(char *main_string, char *sub_string)
{
    //exit--------
    // ----exit--------
    // ---------exit

    int count_flag = 1;

    int i, j;
    j = 0;

    int sub_string_length;
    for (sub_string_length = 0; sub_string[sub_string_length++];);
    sub_string_length --;

    for (i = 0; main_string[i]; i++)
    {
        if ( count_flag && main_string[i] == sub_string[j])
            j++;

        else if (main_string[i] != sub_string[j] && main_string[i] != ' ')
        {
            j = 0;
            count_flag = 0;
        }

        else if (main_string[i] == ' ' && j < sub_string_length)
        {
            count_flag = 1;
            j = 0;
        }

        if (j == sub_string_length && (main_string[i + 1] == ' ' || main_string[i + 1] == '\0'))
            return 1;
    }
    return 0;
}
