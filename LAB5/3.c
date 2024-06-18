// Name: Cole Fettkether
// Date: 5/9
// Title: Lab5 – Step 3
// Description: creates producer and consumer threads which share a buffer using semaphors

//Shared data: 3 semaphores, called full, empty, and mutex
//pool of n<10 buffers, each can hold one item
//mutex semaphore provides mutual exclusion to the buffer pool
//empty and full semaphores count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCE_COUNT 20
#define CONSUME_COUNT 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t full, empty, mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < PRODUCE_COUNT; i++) {
        int item = i + 1;
        sem_wait(&empty);  
        sem_wait(&mutex);  

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer produced item %d\n", item);

        sem_post(&mutex);  
        sem_post(&full);  

        sleep(1); 
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < CONSUME_COUNT; i++) {
        sem_wait(&full);  
        sem_wait(&mutex);  

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer consumed item %d\n", item);

        sem_post(&mutex);  
        sem_post(&empty); 

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    sem_init(&full, 0, 0);          
    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&mutex, 0, 1);        

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

    return 0;
}
