#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// function to split string and return an array of each word in the string
char **split_string(char string[], char *delimiter) {

    int index = 0;
    char *split_part;

    int string_length = 0; 
    for (; string[string_length++]; ); //gets string length (null term incl)

    // create copy of string
    char _string[string_length];
    for (index = 0; index < string_length; index++)
        _string[index] = string[index];    

    // for storing split parts
    char **array = malloc(string_length * 2); // space for first dimension

    printf("Tokens from split:\n----------------\n");

    index = 0;
    int jndex = 0;
    int part_length = 0;

    // first token (tokens are split parts)
    split_part = strtok(_string, delimiter);

    // get part length + null
    for(; split_part[part_length]; part_length++); 

    array[index] = malloc(part_length);
    for (jndex = 0; jndex < part_length;jndex++){
        array[index][jndex] = split_part[jndex];
    }
    index++;

    printf("%s\n", split_part);

    // other tokens

    while( (split_part = strtok(NULL, delimiter) ) != NULL ){
        part_length = 0;
        // get part length + null
        for(; split_part[part_length]; part_length++);

        array[index] = malloc(part_length);
        for (jndex = 0; jndex < part_length;jndex++){
            array[index][jndex] = split_part[jndex];
        }

        printf("%s\n", split_part);
        index++;
    }

    // add null terminator to array
    array[index] = NULL;

    // print array
    printf("--------Printing Array Contents\n");
    for (index = 0; array[index] != NULL; index++){
        printf("%s\n", array[index]);
    }

    // return the array
    return array;
}

int main(){

    // test it
    char **words_array = split_string("Glo is slow as hell", " ");
    printf("-----Printing words of array returned from split function----\n");
    for (int index = 0; words_array[index]; index++){
        printf("%s\n", words_array[index]);
    }

}