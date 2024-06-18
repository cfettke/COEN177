// Name: Cole
// Date: 4/25
// Title: Lab2 – Step 1
// Description: This program creates a pipe, then sends the info from one end to another

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 redirects stdin to downstream of pipe */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", 0);
    }
    /*child 2 redirects stdout to upstream of pipe */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", "-l", 0);
    } else { /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}