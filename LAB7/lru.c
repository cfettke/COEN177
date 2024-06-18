#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int timestamp;
} ref_page;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <cache size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int cacheSize = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[cacheSize]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i, time;
    int totalFaults = 0;   // Keeps track of the total page faults
    int placeInArray = 0;  // Index for the next replacement (FIFO)
    
    // Initialize cache array
    for (i = 0; i < cacheSize; i++) {
        cache[i].pageno = -1;
        cache[i].timestamp = -1;
    }

    // Read input and implement FIFO page replacement
    while (fgets(pageCache, sizeof(pageCache), stdin)) {
        int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;      // Flag to check if the page is already in cache

        // Check if page is already in cache
        for (i = 0; i < cacheSize; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                cache[i].timestamp = time;
                break; // Break out of loop because found page_num in cache
            }
        }

        // If page is not found in cache, we have a page fault
        if (!foundInCache) {
            int index = 0;
            for (i = 1; i < cacheSize; i++) {
                if (cache[i].timestamp < cache[index].timestamp) {
                    index = i;
                }
            }

            printf("Page fault caused by page number: %d\n", page_num);
            cache[index].pageno = page_num;
            cache[index].timestamp = time; // Update timestamp for the new page
            totalFaults++;
        }
        time++;
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;
}
