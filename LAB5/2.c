// Name: Cole Fettkether
// Date: 5/9
// Title: Lab5 – Step 2
// Description: Thread Synchronization - Mutex
//              This program uses mutex to n threads, then calls the function go using the thread and uses
//              mutex to sync up all the threads so that first the thread attempting is printed, and then once
//              all threads have been created, prints tha the thread is running in the critical section

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NTHREADS 10

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

int main() {
    int i;
    signal(SIGINT, cleanup);
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NTHREADS; i++)   {
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    }
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)(size_t)arg);
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)(size_t)arg);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void cleanup(int sigtype) {
    pthread_mutex_destroy(&mutex);
    printf("\nTerminating\n");
    exit(0);
}
