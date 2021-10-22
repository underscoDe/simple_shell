#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){

    char *name = "Parent";

    // example case of program state before fork
    int some_variable = 0;
    for (; some_variable < 6; some_variable++){
        printf("%s Program state: %d\n",name, some_variable);
    }

    pid_t child_pid = fork();
    pid_t my_pid = getpid();

    // you can only tell which one is parent or child via the child pid.
    // for the parent, child_pid > 0.
    // for the child, child_pid = 0.
    // if fork failed, child_pid = -1.

    if (child_pid == -1)
        return 1;

    if (child_pid == 0){
        printf("I am minimie the forked baby copycat\n");
        name = "minimie";
    }

    else
        printf("I, %d, am the parent of %d\n", my_pid, child_pid);


    // program states after fork
    for (; some_variable <= 10; some_variable++){
        printf("%s Program state: %d\n",name, some_variable);
    }
}
