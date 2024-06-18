#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
    char buffer[atoi(argv[2])];
    FILE *fp, *fp_write;
    fp = fopen(argv[1], "rb");
    fp_write = fopen("write.txt", "wb");
    while (fread(buffer, 1, sizeof(buffer), fp)){
        fwrite(buffer, 1, sizeof(buffer), fp_write);
    }
    fclose(fp);
    fclose(fp_write);
}