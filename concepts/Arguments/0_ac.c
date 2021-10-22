#include <stdio.h>


int main(int ac, char **argv){
    for (int i=0; argv[i]; i++)
        puts(argv[i]);
}