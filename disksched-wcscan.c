#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MIN_DISK 0
#define MAX_DISK 499

void sort(int* queue, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(queue[j]>queue[j+1]) {
                int temp = queue[j];
                queue[j] = queue[j+1];
                queue[j+1] = temp;
            }
        }
    }
}

void fcfs(int* queue, int n, int head) {
    int thm = 0, pos = head;
    printf("Total Head Movement: %d ", pos);
    for(int i = 0 ; i < n ; i++) {
        thm += abs(queue[i] - pos);
        pos = queue[i];
        printf("-> %d ", pos);
    }
    printf("\n%d\n", thm);
}

void scan(int* queue, int n, int head, int dir) {
    int thm = 0, pos = head;
    sort(queue, n);
    printf("Total Head Movement: %d ", pos);
    if(dir) {
        for(int i = 0; i < n; i++) {
            if(queue[i] >= pos) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        thm += abs(MAX_DISK - pos);
        pos = MAX_DISK;
        printf("-> %d ", pos);
        for(int i = n - 1; i >= 0; i--) {
            if(queue[i] < head) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        printf("\n%d\n", thm);
    }
    else {
        for(int i = n - 1; i >= 0; i--) {
            if(queue[i] <= pos) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        thm += abs(MIN_DISK - pos);
        pos = MIN_DISK;
        printf("-> %d ", pos);
        for(int i = 0; i < n; i++) {
            if(queue[i] > head) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        printf("\n%d\n", thm);
    }
}
void cscan(int* queue, int n, int head, int dir) {
    int thm = 0, pos = head;
    sort(queue, n);
    printf("Total Head Movement: %d ", pos);
    if(dir) {
        for(int i = 0; i < n; i++) {
            if(queue[i] >= pos) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        thm += abs(MAX_DISK - pos);
        pos = MAX_DISK;
        printf("-> %d ", pos);
        thm += abs(MIN_DISK - pos);
        pos = MIN_DISK;
        printf("-> %d ", pos);
        for(int i = 0; i < n; i++) {
            if(queue[i] < head) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        printf("\n%d\n", thm);
    }
    else {
        for(int i = n - 1; i >= 0; i--) {
            if(queue[i] <= pos) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        thm += abs(MIN_DISK - pos);
        pos = MIN_DISK;
        printf("-> %d ", pos);
        thm += abs(MAX_DISK - pos);
        pos = MAX_DISK;
        printf("-> %d ", pos);
        for(int i = n - 1 ; i >= 0; i--) {
            if(queue[i] > head) {
                thm += abs(queue[i] - pos);
                pos = queue[i];
                printf("-> %d ", pos);
            }
        }
        printf("\n%d\n", thm);
    }
}
int main() {
    int queue[] = {133, 25, 62, 16, 24, 6, 205, 403, 121, 192, 244, 13, 342, 235, 308};
    int head = 55;
    int n = sizeof(queue)/sizeof(int);
    fcfs(queue, n, head);
    scan(queue, n, head, 1);
    cscan(queue, n, head, 1);
}