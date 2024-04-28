#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct process
{
    int pid;
    int arrival_time;
    int burst_time;
} process;

void sort_by_arrival(process *queue, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j].arrival_time > queue[j + 1].arrival_time) {
                process temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
}

void fcfs(process *queue, int n) {
    sort_by_arrival(queue, n);
    int wt = 0, tt = 0, ct = 0;
    for (int i = 0; i < n; i++) {
        if (ct >= queue[i].arrival_time) {
            printf("P%d\t|", i);
            wt += ct - queue[i].arrival_time;
            ct += queue[i].burst_time;
            tt += ct - queue[i].arrival_time;
        }
        else {
            ct = queue[i].arrival_time;
            printf("P%d\t|", i);
            wt += ct - queue[i].arrival_time;
            ct += queue[i].burst_time;
            tt += ct - queue[i].arrival_time;
        }
    }
    printf("\nAverage turnaround time: %f\n", (float)tt / n);
    printf("Average waiting time: %f\n", (float)wt / n);
}
int main() {
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    process *queue = (process *)calloc(n, sizeof(process));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &queue[i].arrival_time, &queue[i].burst_time);
        queue[i].pid = i;
    }
    fcfs(queue, n);
}