// Name: Cole Fettkether
// Date: 5/2
// Title: Lab2 – Step 4
// Description: This program creates 2 matricies in a multithreaded enviornment, then multiplies them. Each thread is created to multiple one
//              row of the matricies. Some of the code is taken from my COEN 145 class

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>


#define MAX_THREADS 100

typedef struct {
    int i, n, m, l;
    const double *A, *B; 
    double *C;
} thread_data_t;

static int create_mat(size_t const nrows, size_t const ncols, double** const matp) {
    int i, j, k;
    double* mat = NULL;
    if (!(mat = (double*)malloc(nrows * ncols * sizeof(*mat)))) {
        goto cleanup;
    }
    /** Initialize matrix with random values **/
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            mat[(i * ncols) + j] = (double)(rand() % 1000) / 353.0;
        }
    }
    //prints matrix
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            printf("%lf, ", mat[(i * ncols) + j]);
        }
        printf("\n");
    }
    /** End random initialization **/
    *matp = mat;
    return 0;
cleanup:
    free(mat);
    return -1;
}

void* multiply(void* arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int i = data->i;
    int j, k;
    double sum;
    for (j = 0; j < data->l; ++j) {
        sum = 0;
        for (k = 0; k < data->m; ++k) {
            sum += data->A[i * data->m + k] * data->B[k * data->l + j];
        }
        data->C[i * data->l + j] = sum;
    }
    free(data);
    return NULL;
}

static int mult_mat(size_t const n, size_t const m, size_t const l, double const* const A, double const* const B, double** const Cp) {
    int i, j, k, t;
    double sum;
    double* C = NULL;
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;
    if (!(C = (double*)malloc(n * l * sizeof(*C)))) {
        goto cleanup;
    }
    for (i = 0; i < n; ++i) {
        thread_data_t *data = (thread_data_t *)malloc(sizeof(thread_data_t));
        data->i = i;
        data->n = n;
        data->m = m;
        data->l = l;
        data->A = A;
        data->B = B;
        data->C = C;

        pthread_create(&threads[thread_count], NULL, multiply, data);
        thread_count++;

        //Waits for new thread if max number has been reached
        if (thread_count >= MAX_THREADS) {
            for (t = 0; t < thread_count; ++t) {
                pthread_join(threads[t], NULL);
            }
            thread_count = 0;
        }
    }
    for (t = 0; t < thread_count; ++t) {
        pthread_join(threads[t], NULL);
    }
    //prints matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < l; j++) {
            printf("%lf, ", C[(i * l) + j]);
        }
        printf("\n");
    }
    *Cp = C;
    return 0;
cleanup:
    free(C);
    /*failure:*/
    return -1;
}
int main(int argc, char* argv[]) {
    // size_t stored an unsigned integer
    size_t N, M, L;
    double *A = NULL, *B = NULL, *C = NULL;
    if (argc != 4) {
        fprintf(stderr, "usage: matmult nrows ncols ncols2\n");
        goto failure;
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);
    printf("Mat 1\n");
    if (create_mat(N, M, &A)) {
        perror("error");
        goto failure;
    }
    printf("Mat 2\n");
    if (create_mat(M, L, &B)) {
        perror("error");
        goto failure;
    }
    printf("Mat 3\n");
    if (mult_mat(N, M, L, A, B, &C)) {
        perror("error");
        goto failure;
    }
    free(A);
    free(B);
    free(C);
    printf("Printed");
    return EXIT_SUCCESS;
failure:
    if (A) {
        free(A);
    }
    if (B) {
        free(B);
    }
    if (C) {
        free(C);
    }
    return EXIT_FAILURE;
}