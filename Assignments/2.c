#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>

int main() {
    int val = 5;
    int pid;

    if(pid == fork()) {
        wait(pid);
    } 
    val++;
    printf("%d\n", val);
    return val;
}