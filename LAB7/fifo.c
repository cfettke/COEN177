#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pageno;
} ref_page;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <cache size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0;   // Keeps track of the total page faults
    int placeInArray = 0;  // Index for the next replacement (FIFO)
    
    // Initialize cache array
    for (i = 0; i < C_SIZE; i++) {
        cache[i].pageno = -1;
    }

    // Read input and implement FIFO page replacement
    while (fgets(pageCache, sizeof(pageCache), stdin)) {
        int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;      // Flag to check if the page is already in cache

        // Check if page is already in cache
        for (i = 0; i < C_SIZE; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                break; // Break out of loop because found page_num in cache
            }
        }

        // If page is not found in cache, we have a page fault
        if (!foundInCache) {
            printf("Page fault caused by page number: %d\n", page_num);
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = (placeInArray + 1) % C_SIZE;
        }
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;
}
