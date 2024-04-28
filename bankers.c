#include<stdio.h>
#include<stdbool.h>

#define NUM_OF_RESOURCES 3
#define NUM_OF_PROCESSES 5

int available[NUM_OF_RESOURCES];
int allocation[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
int max[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
int need[NUM_OF_PROCESSES][NUM_OF_RESOURCES];
bool finish[NUM_OF_PROCESSES];

bool isSafeState() {
    int work[NUM_OF_RESOURCES];
    bool finish_copy[NUM_OF_PROCESSES];

    for(int i = 0 ; i < NUM_OF_RESOURCES ; i++)
        work[i] = available[i];

    for(int i = 0 ; i < NUM_OF_PROCESSES ; i++)
        finish_copy[i] = finish[i];

    int count = 0;
    while( count < NUM_OF_PROCESSES ) {
        bool found = false;
        for(int i = 0 ; i < NUM_OF_PROCESSES ; i++) {
            if(!finish_copy[i]) {
                bool canRun = true;
                for(int j = 0 ; j < NUM_OF_RESOURCES ; j++) {
                    if(need[i][j] > work[j]){
                        canRun = false;
                        break;
                    }
                }
                if(canRun) {
                    found = true;
                    count++;
                    for(int j = 0; j < NUM_OF_RESOURCES ; j++) 
                        work[j]+=allocation[i][j];
                    finish_copy[i] = true;
                }
            }
        }
        if(!found)
            return false;
    }
    return true;
}
void requestResources(int process, int request[]) {
    for(int i = 0; i < NUM_OF_RESOURCES ; i++) {
        if( request[i] > available[i] || request[i] > need[process][i]) {
            printf("Allocation not possible\n");
            return;
        }
    }
    for(int i = 0; i < NUM_OF_RESOURCES ; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    if(isSafeState()) 
        printf("Request Allocated\n");
    else {
        for(int i = 0; i < NUM_OF_RESOURCES ; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request Cannot be granted\n");
    }
}
int main() {
    printf("Number of Processes %d, Number of Resources %d", NUM_OF_PROCESSES, NUM_OF_RESOURCES);

    printf("\nEnter available: ");
    for(int i = 0 ; i < NUM_OF_RESOURCES ; i++)
        scanf("%d", &available[i]);

    printf("\nEnter maximum: ");
    for(int i = 0; i < NUM_OF_PROCESSES ; i++) {
        printf("\nFor P%d: ", i);
        for(int j = 0 ; j < NUM_OF_RESOURCES; j++) 
            scanf("%d", &max[i][j]);
    }
    printf("\nEnter allocation: ");
    for(int i = 0; i < NUM_OF_PROCESSES ; i++) {
        printf("\nFor P%d: ", i);
        for(int j = 0 ; j < NUM_OF_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
        finish[i] = false;
    }
    int process;
    int request[NUM_OF_RESOURCES];
    printf("\nEnter process : ");
    scanf("%d", &process);
    printf("\nEnter request: ");
    for(int i = 0 ; i < NUM_OF_RESOURCES ; i++)
        scanf("%d", &request[i]);

    requestResources(process, request);
}