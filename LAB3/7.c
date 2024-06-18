// Name: Cole Fettkether
// Date: 4/25
// Title: Lab2 – Step 7
// Description: This program creates a pipe, reads in the contents of argv, and uses them
//              them to print the location of the file

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define numThreads 10
pthread_t threads[numThreads];

void *go(void *arg) {
    int id = *(int *)arg; 
    printf("Hello from thread %ld with iteration %d\n", (long int)pthread_self(), id);
    return 0;
}

int main() {
    int i;
    int ids[numThreads];  

    for (i = 0; i < numThreads; i++) {
        ids[i] = i; 
        pthread_create(&threads[i], NULL, go, &ids[i]);
    }

    for (i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d returned\n", i);
    }
    printf("Main thread done.\n");
    return 0;
}


