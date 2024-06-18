#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

void *copy_file(void *arg);

typedef struct {
    char *source_file;
    char dest_file[50];
    size_t buffer_size;
} thread_arg_t;

int main(int argc, char *argv[]) {
    char *source_file = argv[1];
    int buffer_size = atoi(argv[2]);
    char buffer[atoi(argv[2])];
    int num_threads = atoi(argv[3]);
    int i;

    pthread_t threads[num_threads];
    thread_arg_t thread_args[num_threads];

    for (i = 0; i < num_threads; i++) {
        thread_args[i].source_file = source_file;
        thread_args[i].buffer_size = buffer_size;

        // Create a unique destination file for each thread
        sprintf(thread_args[i].dest_file, "write_copy_%d.txt", i + 1);

        pthread_create(&threads[i], NULL, copy_file, &thread_args[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

void *copy_file(void *arg) {
    thread_arg_t *thread_arg = (thread_arg_t *)arg;
    char *source_file = thread_arg->source_file;
    char *dest_file = thread_arg->dest_file;
    size_t buffer_size = thread_arg->buffer_size;

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        pthread_exit(NULL);
    }

    FILE *fp = fopen(source_file, "rb");
    if (fp == NULL) {
        perror("Failed to open source file");
        free(buffer);
        pthread_exit(NULL);
    }

    FILE *fp_write = fopen(dest_file, "wb");
    if (fp_write == NULL) {
        perror("Failed to open destination file");
        fclose(fp);
        free(buffer);
        pthread_exit(NULL);
    }

    size_t bytes_read;
    while (fread(buffer, 1, buffer_size, fp)){
        fwrite(buffer, 1, buffer_size, fp_write);
    }

    fclose(fp);
    fclose(fp_write);
    free(buffer);
    pthread_exit(NULL);
}