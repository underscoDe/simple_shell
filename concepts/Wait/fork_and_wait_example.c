#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(){

    char *name = "Parent";
    int wait_status; // will retrieve pid of terminated child after a WAIT of parent

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

    if (child_pid == -1)  // fork failed
        return 1;

    if (child_pid == 0){    // fork successful and this is child
        printf("I am minimie the forked baby copycat\n");
        name = "minimie";
    }

    else{ // fork successful and this is parent, hence child_pid > 0
        printf("I, %d, am the parent of %d and I shall now WAIT for my child\n", my_pid, child_pid);
        wait(&wait_status); // WAIT for child process to terminate

        // after returning, when child process is already terminated
        printf("I, %d, the parent, shall now continue\n", my_pid);
    }


    // program states after fork
    for (; some_variable <= 10; some_variable++){
        printf("%s Program state: %d\n",name, some_variable);
    }
}
