#include<stdio.h>
#include<stdbool.h>

#define NUM_OF_RESOURCES 3
#define NUM_OF_PROCESSES 5

int available[NUM_OF_RESOURCES];
int allocation[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
int request[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
bool finish[NUM_OF_PROCESSES];

bool isDeadlock() {
    int work[NUM_OF_RESOURCES];
    bool visited[NUM_OF_PROCESSES];

    for(int i = 0 ; i < NUM_OF_RESOURCES ; i++)
        work[i] = available[i];

    for(int i = 0 ; i < NUM_OF_PROCESSES ; i++)
        visited[i] = false;

    int count = 0;
    while( count < NUM_OF_PROCESSES ) {
        bool found = false;
        for(int i = 0 ; i < NUM_OF_PROCESSES ; i++) {
            if(!visited[i]) {
                bool canRun = true;
                for(int j = 0 ; j < NUM_OF_RESOURCES ; j++) {
                    if(request[i][j] > work[j]){
                        canRun = false;
                        break;
                    }
                }
                if(canRun) {
                    found = true;
                    count++;
                    for(int j = 0; j < NUM_OF_RESOURCES ; j++) 
                        work[j]+=allocation[i][j];
                    visited[i] = true;
                }
            }
        }
        if(!found)
            return true;
    }
    return false;
}
int main() {
    printf("Number of Processes %d, Number of Resources %d", NUM_OF_PROCESSES, NUM_OF_RESOURCES);

    printf("\nEnter allocation: ");
    for(int i = 0; i < NUM_OF_PROCESSES ; i++) {
        printf("\nFor P%d: ", i);
        for(int j = 0 ; j < NUM_OF_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
        finish[i] = false;
    }
    printf("\nEnter requests: ");
    for(int i = 0; i < NUM_OF_PROCESSES ; i++) {
        printf("\nFor P%d: ", i);
        for(int j = 0 ; j < NUM_OF_RESOURCES; j++) 
            scanf("%d", &request[i][j]);
    }
    printf("\nEnter available: ");
    for(int i = 0 ; i < NUM_OF_RESOURCES ; i++)
        scanf("%d", &available[i]);

    if(isDeadlock())
        printf("Deadlock Detected\n");
    else
        printf("No Deadlocks\n");
}