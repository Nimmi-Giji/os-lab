#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NUM_FRAMES 4

void fifo(int* pages, int n) {
    int frames[NUM_FRAMES] = {-1, -1, -1, -1};
    bool pageFault = false;
    int pageFaultCount = 0;
    int nextFrameIndex = 0;
    for(int i = 0 ; i < n ; i++) {
        int j, k;
        for(j = 0 ; j < NUM_FRAMES; j++) {
            if(frames[j] == pages[i]) {
                pageFault = false;
                break;
            }
        }
        if(j == NUM_FRAMES) {
            pageFault = true;
            pageFaultCount++;
            frames[nextFrameIndex] = pages[i];
            nextFrameIndex = (nextFrameIndex+1) % NUM_FRAMES;
        }
        printf("Page %d->\t", pages[i]);
        for( k = 0 ; k < NUM_FRAMES ; k++) 
            printf("%d\t", frames[k]);

        if(pageFault) printf("(Page Fault)");
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaultCount);
}

void lru(int* pages, int n) {
    int frames[NUM_FRAMES] = {-1, -1, -1, -1};
    int recent[NUM_FRAMES] = {-1, -1, -1, -1};
    bool pageFault = false;
    int pageFaultCount = 0;
    int leastRecent = 0;
    for(int i = 0 ; i < n ; i++) {
        int j, k;
        for(j = 0 ; j < NUM_FRAMES; j++) {
            if(frames[j] == pages[i]) {
                pageFault = false;
                recent[j] = i;
                break;
            }
        }
        if(j == NUM_FRAMES) {
            pageFault = true;
            leastRecent = 0;
            pageFaultCount++;
            for( k = 0 ; k < NUM_FRAMES ; k++) {
                if(recent[k] < recent[leastRecent])
                    leastRecent = k;
            }
            frames[leastRecent] = pages[i];
            recent[leastRecent] = i;
        }
        printf("Page %d->\t", pages[i]);
        for( k = 0 ; k < NUM_FRAMES ; k++) 
            printf("%d\t", frames[k]);

        if(pageFault) printf("(Page Fault)");
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaultCount);
}
void lfu(int* pages, int n) {
    int frames[NUM_FRAMES] = {-1, -1, -1, -1};
    int frequency[NUM_FRAMES] = {0};
    bool pageFault = false;
    int pageFaultCount = 0;
    int leastFrequent = 0;
    for(int i = 0 ; i < n ; i++) {
        int j, k;
        for(j = 0 ; j < NUM_FRAMES; j++) {
            if(frames[j] == pages[i]) {
                pageFault = false;
                frequency[j]++;
                break;
            }
        }
        if(j == NUM_FRAMES) {
            pageFault = true;
            leastFrequent = 0;
            pageFaultCount++;
            for( k = 0 ; k < NUM_FRAMES ; k++) {
                if(frequency[k] < frequency[leastFrequent])
                    leastFrequent = k;
            }
            frames[leastFrequent] = pages[i];
            frequency[leastFrequent] = 1;
        }
        printf("Page %d->\t", pages[i]);
        for( k = 0 ; k < NUM_FRAMES ; k++) 
            printf("%d\t", frames[k]);

        if(pageFault) printf("(Page Fault)");
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaultCount);
}
int main(){
    int pages[] = {1, 2, 4, 5, 1, 6, 3, 2, 1, 4, 6};
    int n = sizeof(pages)/sizeof(pages[0]);
    fifo(pages, n);
    lru(pages, n);
    lfu(pages, n);
}