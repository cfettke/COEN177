#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
    char buffer[atoi(argv[2])];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while (fread(buffer, 1, sizeof(buffer), fp)){
    }
    fclose(fp);
}