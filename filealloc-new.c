#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NUM_BLOCKS 30
#define BLOCK_SIZE 50

bool blocks[NUM_BLOCKS];

typedef struct lblock{
    int index;
    struct lblock* next;
}lblock;

void init() {
    for(int i = 0; i < NUM_BLOCKS; i++) 
        blocks[i] = false;
}

void seqAlloc(int fileSize) {
    int numBlocks = fileSize/BLOCK_SIZE ;
    if ((fileSize % BLOCK_SIZE)> 0) numBlocks++;

    int start, count, i;
    count = 0;
    start = -1;
    for(i = 0; i < NUM_BLOCKS; i++) {
        if(!blocks[i]) {
            if(start == -1) start = i;
            count++;
            if(count == numBlocks) break;
        }
        else {
            start = -1;
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
        printf("File too big for sequential Allocation\n");
}

void indAlloc(int fileSize) {
    int numBlocks = fileSize/BLOCK_SIZE ;
    if ((fileSize % BLOCK_SIZE)> 0) numBlocks++;

    int* index = (int *)malloc(numBlocks*sizeof(int));
    int count  = 0;
    for(int i = 0; i < NUM_BLOCKS && count < numBlocks; i++) {
        if(!blocks[i]) {
            index[count++] = i;
        }
    }
    if(count == numBlocks) {
        printf("Indexed Allocation of FileSize %d\n", fileSize);
        printf("Index Block: \n");
        for(int k = 0; k < numBlocks ; k++) {
            printf("%d->%d\n", k, index[k]);
            blocks[index[k]] = true;
        }
    }
    else
        printf("File too big for Indexed Allocation\n");
}
void linkAlloc(int fileSize) {
    int numBlocks = fileSize/BLOCK_SIZE ;
    if ((fileSize % BLOCK_SIZE)> 0) numBlocks++;
    int count  = 0;
    lblock *start = (lblock *)malloc(sizeof(lblock));
    for(int i = 0; i < NUM_BLOCKS && count < numBlocks; i++) {
        if(!blocks[i]) {
            count++;
            if(count == 1) {
                start->index = i;
                start->next = NULL;
            }
            else {
                lblock *pos = start;
                while(pos->next != NULL) pos = pos->next;
                lblock *temp = (lblock *)malloc(sizeof(lblock));
                temp->index = i;
                temp->next = NULL;
                pos->next = temp;
            }
        }
    }
    if(count == numBlocks) {
        printf("Linked Allocation of FileSize %d\n", fileSize);
        lblock *pos = start;
        printf("Start - ");
        while(pos->next != NULL) {
            printf("%d->", pos->index);
            blocks[pos->index] = true;
            pos = pos->next;
        }
        printf("%d End\n", pos->index);
    }
    else
        printf("File too big for Linked Allocation\n");
}
int main() {
    init();
    seqAlloc(100);
    seqAlloc(120);
    blocks[6] = true;
    seqAlloc(140);
    indAlloc(150);
    blocks[13] = true;
    blocks[16] = true;
    linkAlloc(220);
}