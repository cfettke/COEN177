// Name: Cole Fettkether
// Date: 5/9
// Title: Lab5 – Step 3
// Description: creates producer and consumer threads which share a buffer using semaphors, additionally uses a 
//              condition variable which keeps track of issues with shared buffer

//Shared data: 2 condition variables, called full and empty, and a mutex lock, called mutex.
//Same pool of n<10 buffers, but no need to initialize full, empty, and mutex to specific values.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCE_COUNT 20
#define CONSUME_COUNT 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t full, empty;

void *producer(void *arg) {
    int i, item;
    for (i = 0; i < PRODUCE_COUNT; i++) {
        item = i + 1;
        pthread_mutex_lock(&mutex); 

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer produced item %d\n", item);

        pthread_cond_signal(&full); 
        pthread_mutex_unlock(&mutex);

        sleep(1); 
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < CONSUME_COUNT; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer consumed item %d\n", item);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
