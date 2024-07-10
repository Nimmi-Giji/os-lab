#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int complete;
}process;

int find_process(process* queue, int n, int time) {
    int shortest = INT_MAX, id = -1;
    for(int i = 0; i < n; i++) {
        if(queue[i].complete == 0 && queue[i].arrival_time <= time && queue[i].burst_time < shortest)
            shortest = queue[i].burst_time, id = i;
    }
    return id;
}
void sort_by_burst(process* queue, int n) {
    for(int i = 0; i < n - 1; i++ ) {
        for(int j = 0; j < n - i - 1; j++) {
            if(queue[j].burst_time > queue[j+1].burst_time) {
                process temp = queue[j];
                queue[j] = queue[j+1];
                queue[j+1] = temp;
            }
        }
    }
}
void sjf(process* queue, int n) {
    int wt = 0, tt = 0, ct = 0, id;
    int count = 0;
    while(count < n) {
        if((id = find_process(queue, n, ct)) != -1) {
            wt += ct - queue[id].arrival_time;
            ct += queue[id].burst_time;
            tt += ct - queue[id].arrival_time;

            queue[id].complete =  1;
            count++;

            printf("P%d\t|", queue[id].pid);
        }
        else {
            printf("CPU IDLE|");
            int min = INT_MAX;
            for(int i = 0 ; i < n ; i++) {
                if(queue[i].complete!=1 && queue[i].arrival_time < min && queue[i].arrival_time > ct) {
                    min = queue[i].arrival_time;
                }
            }
            ct = min;
        }
    }
    printf("\nTurnaround time %f\n", (float)tt/n);
    printf("Waiting time %f\n", (float)wt/n);
}
int main() {
    process queue[5];
    for(int i = 0; i < 5; i++) {
        queue[i].pid = i;
        scanf("%d %d", &queue[i].arrival_time, &queue[i].burst_time);
        queue[i].complete = 0;
    }
    sjf(queue, 5);
}