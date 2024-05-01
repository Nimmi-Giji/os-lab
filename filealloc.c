#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define BLOCK_SIZE 50
#define NUM_BLOCKS 30

bool blocks[NUM_BLOCKS];

void init() {
    for(int i = 0 ; i < NUM_BLOCKS ; i++) {
        blocks[i] = false;
    }
}
void seqAlloc(int fileSize) {
    int numBlocks = fileSize/BLOCK_SIZE + (fileSize%BLOCK_SIZE!=0);
    if(numBlocks > NUM_BLOCKS) return;
    int count = 0;
    int start = 0;
    int i, j;
    for(i = 0 ; i < NUM_BLOCKS; i++) 
        if(blocks[i]) start++;
    for(j = start ; j < NUM_BLOCKS && count < numBlocks ; j++) {
        if(!blocks[j]) count++;
        else {
            j = start++;
            count = 0;
        }
    }

    if(count == numBlocks) {
        printf("Sequential Allocation of FileSize %d\n", fileSize);
        printf("Start Index : %d\n", start);
        for(int k = start; k < start+numBlocks ; k++)
            blocks[k] = true;
        printf("Allocated Blocks: %d\n", numBlocks);
    }
    else
        printf("File too big for Sequential Allocation\n");
}
void indAlloc(int fileSize) {
    int numBlocks = fileSize/BLOCK_SIZE + (fileSize%BLOCK_SIZE!=0);
    if(numBlocks > NUM_BLOCKS) return;
    int count = 0;
    int* index = (int *)malloc(numBlocks*sizeof(int));
    for(int i = 0 ; i < NUM_BLOCKS && count < numBlocks; i++) {
        if(!blocks[i]) {
            index[count++] = i;
            blocks[i] = true;
        }
    }
    if( count  == numBlocks ) {
        printf("Index Block: \n");
        for(int i = 0; i < numBlocks ; i++) 
            printf("%d->%d\n", i, index[i]);
    }
    else
        printf("Not enough memory\n");
}
int main() {
    init();
    seqAlloc(100);
    seqAlloc(120);
    blocks[6] = true;
    seqAlloc(140);
    indAlloc(150);
}