// Name: Cole Fettkether
// Date: 4/25
// Title: Lab2 – Step 5
// Description: This program creates a pipe, reads in the contents of argv, and uses them
//              them to print the location of the file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int fds[2];
    int i;

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }


    if (fork() == 0) {
        close(fds[1]); 
        char buffer[BUFFER_SIZE];

        while (1) {
            ssize_t bytes_read = read(fds[0], buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                break; 
            }
            buffer[bytes_read] = '\0';
            printf("Consumer received: %s", buffer);
        }

        close(fds[0]); 
        printf("Consumer exiting.\n");
        exit(0);
    } else {
        close(fds[0]); 
        char *messages[] = {"Message 1\n", "Message 2\n", "Message 3\n"};

        for (i = 0; i < 3; i++) {
            write(fds[1], messages[i], strlen(messages[i]));
            printf("Producer sent: %s", messages[i]);
            sleep(1); 
        }

        close(fds[1]); 
        printf("Producer finished.\n");

        wait(NULL);
    }

    return 0;
}
