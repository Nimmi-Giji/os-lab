#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define MIN_DISK 0
#define MAX_DISK 4999

void sort(int* arr, int n) {
    for(int i = 0 ; i < n - 1 ; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if( arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void fcfs(int* queue,int head, int n) {
    int pos = head;
    int thm = 0;
    printf("Head movement fcfs:\n%d", pos);
    for(int i = 0 ;  i < n ; i++) {
        thm += abs(pos - queue[i]);
        pos = queue[i];
        printf("->%d", pos);
    }
    printf("\nTotal head movement: %d\n", thm);
}
void scan(int* queue, int head, int n, int dir) {
    int pos = head;
    int thm = 0;
    sort(queue, n);
    printf("Head movement scan:\n%d", pos);
    if(dir) {
        for(int i = 0 ; i < n ; i++) {
            if(queue[i] >= pos) {
                thm += abs(pos - queue[i]);
                pos = queue[i];
                printf("->%d", pos);
            }
        }
        thm += abs(pos - MAX_DISK);
        pos = MAX_DISK;
        printf("->%d", pos);
        for(int i = n - 1 ; i >=0 ; i--) {
            if(queue[i] <= head) {
                thm += abs(pos - queue[i]);
                pos = queue[i];
                printf("->%d", pos);
            }
        }
    }
    else {
        for(int i = 0 ; i < n ; i++) {
            if(queue[i] <= pos) {
                thm += abs(pos - queue[i]);
                pos = queue[i];
                printf("->%d", pos);
            }
        }
        thm += abs(pos - MIN_DISK);
        pos = MIN_DISK;
        printf("->%d", pos);
        for(int i = 0 ; i < n ; i++) {
            if(queue[i] >= head) {
                thm += abs(pos - queue[i]);
                pos = queue[i];
                printf("->%d", pos);
            }
        }   
    }
    printf("\nTotal head movement: %d\n", thm);
}
int main() {
    int queue [] = {86, 1470, 913, 1774, 948, 1509, 1022, 1750, 130};
    int head = 143;
    int n = sizeof(queue)/sizeof(queue[0]);
    fcfs(queue, head, n);
    scan(queue, head, n, 1);
    scan(queue, head, n, 0);
}