#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
 
        for (i = 0; i < cacheSize; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                break; // Break out of loop because found page_num in cache
            }
        }

        // If page is not found in cache, we have a page fault
        if (!foundInCache) {
            // Print the page that caused the page fault (if needed)
            printf("Page fault caused by page number: %d\n", page_num);
            // Replace the page at the placeInArray index with the new page
            cache[placeInArray].pageno = page_num;
            // Increment the total page faults
            totalFaults++;
            // Update the index for the next replacement
            placeInArray = (placeInArray + 1) % cacheSize;
        }
    }

    printf("%d Total Page Faults", faultno);
    return 0;
}
