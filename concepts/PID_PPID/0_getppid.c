
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void)
{
    pid_t my_ppid;    

    my_ppid = getppid();
    printf("%u\n", my_ppid);
}