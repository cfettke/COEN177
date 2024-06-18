// Name: Cole Fettkether
// Date: 4/25
// Title: Lab2 – Step 4
// Description: This program creates a pipe, reads in the contents of argv, and uses them
//              them to print the location of the file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int fds[2];

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }


    if (fork() == 0) {
        dup2(fds[1], STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);

        execlp("cat", "cat", "/etc/passwd", NULL);
        exit(0);
    } else {
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        close(fds[1]);

        execlp("grep", "grep", "root", NULL);
        exit(0);
    }

    return 0;
}