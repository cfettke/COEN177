#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    bool reference;
} ref_page;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <cache size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[cacheSize];     // Cache that stores pages
    char pageCache[100];           // Cache that holds the input from test file

    int i;
    int totalFaults = 0;           // Keeps track of the total page faults
    int placeInArray = 0;          // Index for the next replacement (FIFO)
    
    // Initialize cache array
    for (i = 0; i < cacheSize; i++) {
        cache[i].pageno = -1;
        cache[i].reference = false;
    }

    // Read input and implement FIFO page replacement
    while (fgets(pageCache, sizeof(pageCache), stdin)) {
        int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;      // Flag to check if the page is already in cache

        // Check if page is already in cache
        for (i = 0; i < cacheSize; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                cache[i].reference = true; // Set reference bit if page is found
                break; // Break out of loop because found page_num in cache
            }
        }

        // If page is not found in cache, we have a page fault
        if (!foundInCache) {
            printf("Page fault caused by page number: %d\n", page_num);
            while (true) {
                if (cache[placeInArray].reference == false) {
                    // If found, replace where reference bit is 0
                    cache[placeInArray].pageno = page_num;
                    placeInArray = (placeInArray + 1) % cacheSize;
                    break;
                } else {
                    // Else give page a second chance
                    cache[placeInArray].reference = false;
                    placeInArray = (placeInArray + 1) % cacheSize;
                }
            }
            totalFaults++;
        }
    }

    //printf("%d Total Page Faults\n", totalFaults);
    return 0;
}
