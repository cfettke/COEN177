/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h>  /* errno */
#include <stdlib.h> /* atoi */
#include <bits/pthreadtypes.h>

void *child_thread(void *arg) {
    int i, n = *((int *)arg); 
    for (i = 0; i < 10; i++) {
        printf("I am the child thread displaying iteration %d\n", i);
        usleep(n);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <delay> \n", argv[0]);
        exit(0);
    }

    int n = atoi(argv[1]); // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before creating thread.\n");

    pthread_t tid; 
    pthread_create(&tid, NULL, child_thread, (void *)&n); 

    // Parent process: main thread
    int i;
    for (i = 0; i < 10; i++) {
        printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
        usleep(n);
    }

    pthread_join(tid, NULL); 

    return 0;
}
