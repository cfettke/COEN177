// Name: Cole Fettkether
// Date: 4/25
// Title: Lab2 – Step 6
// Description: This program creates a pipe, reads in the contents of argv, and uses them
//              them to print the location of the file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define size 1024

struct shared_data {
    int is_written; 
    char message[size];
};

int main() {
    key_t key = ftok("shared_memory_key", 'R'); 
    int shmid = shmget(key, sizeof(struct shared_data), IPC_CREAT | 0666); 

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    struct shared_data *shared = (struct shared_data *)shmat(shmid, NULL, 0); 

    if (fork() == 0) {
        sleep(2); 

        strcpy(shared->message, "Message Content");
        shared->is_written = 1;

        printf("Message written to shared memory by producer\n");

        exit(0);
    } else {
        wait(NULL);

        if (shared->is_written) {
            printf("Message read from shared memory by consumer: %s\n", shared->message);
        } 

        exit(0);
    }

    return 0;
}
