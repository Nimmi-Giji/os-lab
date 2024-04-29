#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct block {
    int size;
    bool allocated;
}block;

block* initializeBlocks(int n) {
    block *blocks = (block *)malloc(n*sizeof(block));
    for(int i = 0 ;  i < n; i++) {
        printf("Enter size of block %d: ", i);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = false;
    }
    return blocks;
}

void printMemoryStatus(block* blocks, int n) {
    for(int i = 0 ;  i < n; i++) 
        printf("BLOCK %d SIZE %d ALLOCATED %s\n", i, blocks[i].size, blocks[i].allocated?"True":"False");
}
void allocateMemory(block* blocks, int n, int size, int method) {
    int index = -1;
    switch(method) {
        case 1:
        for(int i = 0 ; i < n ; i++) {
            if(blocks[i].size >= size) {
                index = i;
                break;
            }
        }
        break;
        case 2:
        for(int i  = 0; i < n ; i++) {
            if(blocks[i].size >= size) {
                if(index == -1 || blocks[i].size > blocks[index].size)
                    index = i;
            }
        }
        break;
        case 3: 
        for(int i = 0 ; i < n ; i++) {
            if(blocks[i].size >= size) {
                if(index == -1 || blocks[i].size < blocks[index].size)
                    index = i;
            }
        }
        break;
        default: exit(1);
    }
    if(index == -1) 
        printf("Allocation not possible\n");
    else {
        printf("Block %d allocated", index);
        blocks[index].allocated = true;
    }
}
int main() {
    int n;
    printf("Enter number of blocks: ");
    scanf("%d", &n);
    block *blocks = initializeBlocks(n);
    printMemoryStatus(blocks, n);
    int ch, size;
    printf("1.First 2.Worst 3.Best");
    while(1) {
        printf("\nEnter fileSize, choice: ");
        scanf("%d %d", &size, &ch);
        allocateMemory(blocks, n, size, ch);
        printMemoryStatus(blocks, n);
    }
}