// Name: Cole Fettkether
// Date: 4/25
// Title: Lab2 – Step 3
// Description: This program creates a pipe, reads in the contents of argv, and uses them
//              them to print the location of the file

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
// main
int main(int argc, char *argv[]) {
    int fds[2];
    dup2(fds[1],1);
    char buff[60];
    int count;
    int i;
    //execlp("ls", "ls", "-l", NULL);  
    pipe(fds);
    if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", 0);
        exit(0);
    } else if (fork() == 0) {
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while ((count = read(fds[0], buff, 60)) > 0) {
            for (i = 0; i < count; i++) {
                write(1, buff + i, 1);
                write(1," ", 1);
            }
            printf("\n");
        }
        exit(0);
    } else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}