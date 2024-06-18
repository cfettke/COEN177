/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h>  /* errno */
#include <stdlib.h> /* atoi */
/* main function */
int main(int argc, char *argv[]) {
    if (argc != 5){
        printf ("Usage: %s <delay> <delay2> <delay3> <delay4>\n",argv[0]);
        exit(0);
    }
    pid_t pid[4];
    int i, j, n[4];
    n[0] = atoi(argv[1]), n[1] = atoi(argv[2]), n[2] = atoi(argv[3]), n[3] = atoi(argv[4]); // n is a delay in microseconds inserted in parent and
    // child iterations
    printf("\n Before forking.\n");
        for (i = 1; i < 4; i++) {
            pid[i] = fork();
            if (pid[i] < 0) {
                fprintf(stderr, "can't fork, error %d\n", errno);
                exit(0);
            }
            if (pid[i]) {
                // Parent continues forking
                continue;
            } else {
                // Child process: pid[i] = 0
                for(j = 0; j < 10; j++) {
                    printf("I am the child process %d displaying iteration %d\n", i, j);
                    usleep(n[i]);
                }
                exit(0); // Child exits after its iterations
            }
        }
    
        // Parent process: pid = 0
        for (i = 0; i < 10; i++) {
            printf("I am the parent process displaying iteration %d\n", i);
            usleep(n[0]);
        }
        for (i = 1; i < 4; i++) {
            waitpid(pid[i], NULL, 0);
        }
        exit(0);
    
    return 0;
}