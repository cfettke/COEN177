/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h>  /* errno */
#include <stdlib.h> /* atoi */
/* main function */
int main(int argc, char *argv[]) {
    pid_t pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and
    // child iterations
    printf("\n Before forking.\n");
    pid = fork();

    if(pid == 0) {
        execlp("/bin/ls", "ls", 0);
    } else {
        wait(0);
        printf("Child has completed the task! \n");
        exit(0);
    }
    return 0;
}