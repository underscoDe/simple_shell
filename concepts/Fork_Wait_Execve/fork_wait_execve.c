#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){

    pid_t child_pid; // -1 if fork failed, > 0 if parent, 0 if child
    int wait_status;

    char *arguments[] = {"/usr/bin/ls", "-l", "/tmp", NULL}; // for execve

    for (int fork_count = 0; fork_count < 5; fork_count++){
        printf("FORK number %d!\n", fork_count + 1);
        child_pid = fork();

        // at this point, handle program execution based on if it's parent or child
        if (child_pid == -1) // fork failed
        {
            perror("failed to create child process");
            return 1;
        }

        else if (child_pid > 0) // fork succeeded. this is parent
        {
            puts("WAIT!");
            wait(&wait_status); // wait for one of the children to terminate
            puts("RESUMED FROM WAIT");
        }

        else if (child_pid == 0) // fork succeeded. this is child
        {
            puts ("I am forked child, about to execute another program now");

            // execute intended program
            execve(arguments[0], arguments, NULL);
        }

    }
}