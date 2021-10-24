#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    pid_t child_pid; // -1 if fork failed, > 0 if parent, 0 if child
    int wait_status;

    size_t argument_length = 0;
    char *line_buffer;

    printf("Simple_Shell__$ ");
    getline(&line_buffer, &argument_length, stdin);    
    
    // find raw_argument length up to newline
    for (argument_length = 0; line_buffer[argument_length] != '\n'; argument_length++);

    int i = 0;
    char arg[argument_length];
    for (i = 0; ; i++){
         arg[i] = line_buffer[i] != '\n' ? line_buffer[i] : '\0';
         if (line_buffer[i] == '\n')
            break;
    }

    char *argument[] = {arg, NULL};


    int fork_ntimes = 1;

    for (int fork_count = 0; fork_count < fork_ntimes; fork_count++){
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
            execve(argument[0], argument, NULL);
        }

    }
}