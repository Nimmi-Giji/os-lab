#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int queue_arrival;
    int rem;
} process;

void sort_by_arrival(process *queue, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (queue[j].queue_arrival > queue[j + 1].queue_arrival)
            {
                process temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
}

void fcfs(process *queue, int n)
{
    sort_by_arrival(queue, n);
    int wt = 0, tt = 0, ct = 0;
    for (int i = 0; i < n; i++)
    {
        if (ct >= queue[i].arrival_time)
        {
            printf("P%d\t|", i);
            wt += ct - queue[i].arrival_time;
            ct += queue[i].burst_time;
            tt += ct - queue[i].arrival_time;
        }
        else
        {
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
void round_robin(process *queue, int n)
{
    int time_slice = 4;
    int remp = n;
    int ct = 0, wt = 0, tt = 0;
    while (remp > 0)
    {
        bool all = true;
        sort_by_arrival(queue, n);
        for (int i = 0; i < n; i++)
        {
            if (queue[i].rem > 0)
            {
                all = false;
                if (queue[i].queue_arrival <= ct)
                {
                    if (queue[i].rem > time_slice)
                    {
                        printf("P%d\t|", queue[i].pid);
                        queue[i].rem -= time_slice;
                        wt += ct - queue[i].queue_arrival;
                        ct += time_slice;
                        queue[i].queue_arrival = ct;
                    }
                    else
                    {
                        remp--;
                        printf("P%d\t|", queue[i].pid);
                        wt += ct - queue[i].queue_arrival;
                        ct += queue[i].rem;
                        tt += ct - queue[i].queue_arrival;//arrival_time
                        queue[i].queue_arrival = ct;
                        queue[i].rem = 0;
                    }
                }
                else
                    ct = queue[i].queue_arrival;
            }
        }
    }
    printf("\nAverage turnaround time: %f\n", (float)tt / n);
    printf("Average waiting time: %f\n", (float)wt / n);
}

int main()
{
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    process *queue = (process *)calloc(n, sizeof(process));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &queue[i].arrival_time, &queue[i].burst_time);
        queue[i].pid = i;
        queue[i].queue_arrival = queue[i].arrival_time;
        queue[i].rem = queue[i].burst_time;
    }
    fcfs(queue, n);
    //round_robin(queue, n);
}