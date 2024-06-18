// Name: Cole Fettkether
// Date: 5/2
// Title: Lab2 – Step 1, 2, 3
// Description: This program creates 20 threads, then had each thread print its location and itereation
//pt 2: arg is a shared state value since it is stored in the shared memory and is called in the main funciton
//pt 3: i is a per thread variable since each thread makes its own copy, it is stored in the TLS

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void *go(void *);
#define NTHREADS 20
pthread_t threads[NTHREADS];

int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}