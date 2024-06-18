#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[sizeof(int)];
    int numRequests = atoi(argv[1]);
    int maxPageNumber = atoi(argv[2]);

    int i;
    fp = fopen("testInput.txt", "w");
    for (i = 0; i < numRequests; i++) {
        sprintf(buffer, "%d\n", rand() % maxPageNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}