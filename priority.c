#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int rem_time;
    int queue_arrival;
    int complete;
}process;
int find_process(process* queue, int n, int time) {
    int least = INT_MAX, id = -1;
    for(int i = 0; i < n; i++) {
        if(queue[i].complete == 0 && queue[i].queue_arrival <= time && queue[i].priority < least)
            least = queue[i].priority, id = i;
    }
    return id;
}
void priority(process* queue, int n) {
    int wt, tt, ct, count, id;
    wt = ct = tt = count = 0;
    while(count < n) {
        if ((id = find_process(queue, n, ct)) != -1) {
            int start = ct;
            while(find_process(queue, n, ct) == id && ct - start < queue[id].rem_time) ct++;
            printf("P%d\t|", queue[id].pid);
            wt += start - queue[id].queue_arrival;
            if(ct - start == queue[id].rem_time) {
                tt += ct - queue[id].queue_arrival;
                queue[id].complete = 1;
                queue[id].rem_time = 0;
                count ++;
            }
            else {
                queue[id].queue_arrival = ct;
                queue[id].rem_time -= (ct - start);
            }
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
        scanf("%d %d %d", &queue[i].arrival_time, &queue[i].burst_time, &queue[i].priority);
        queue[i].complete = 0;
        queue[i].queue_arrival = queue[i].arrival_time;
        queue[i].rem_time = queue[i].burst_time;
    }
    priority(queue, 5);
}