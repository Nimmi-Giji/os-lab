#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_NUM 50

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int queue_arrival;
    int rem;
}process;
typedef struct queue {
    process p[MAX_NUM];
    int front;
    int rear;
}queue;
void init(queue* q) {
    q->front = -1;
    q->rear = -1;
};
void enqueue(queue* q, process pr) {
    if(q->rear == MAX_NUM - 1) return;
    q->p[++q->rear] = pr;
    for (int i = 0; i < q->rear; i++) {
        for (int j = 0; j < q->rear - i ; j++) {
            if (q->p[j].queue_arrival > q->p[j + 1].queue_arrival) {
                process temp = q->p[j];
                q->p[j] = q->p[j + 1];
                q->p[j + 1] = temp;
            }
        }
    }
}
bool isEmpty(queue* q){
    return q->rear == q->front;
}
process* dequeue(queue* q) {
    if(!isEmpty(q)) {
        process* temp = &(q->p[++q->front]);
        if(q->front == q->rear) init(q);
        return temp;
    }
}
void print(queue* q) {
    for(int i = q->front+1 ; i <= q->rear ; i++)
        printf("%d\t", q->p[i].pid);
}
void rr(queue* q, int n) {
    int wt, tt, ct, qt;
    wt = tt = ct = 0;
    qt = 4;
    while(!isEmpty(q)) {
        process temp = *dequeue(q);
        if(temp.queue_arrival <= ct) {
            if(temp.rem > qt) {
                printf("P%d\t|", temp.pid);
                temp.rem -= qt;
                wt += ct - temp.queue_arrival;
                ct += qt;
                temp.queue_arrival = ct;
                enqueue(q, temp);
            }
            else {
                printf("P%d\t|", temp.pid);
                wt += ct - temp.queue_arrival;
                ct += temp.rem;
                tt += ct - temp.arrival_time;
            }
        }
        else {
            ct = temp.queue_arrival;
            enqueue(q, temp);
        }
    }
    printf("\nAverage turnaround time: %f\n", (float)tt / n);
    printf("Average waiting time: %f\n", (float)wt / n);
}
int main() {
    printf("Enter number of processes:\n");
    int n;
    scanf("%d", &n);
    queue q;
    init(&q);
    process p;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p.arrival_time, &p.burst_time);
        p.pid = i;
        p.queue_arrival = p.arrival_time;
        p.rem = p.burst_time;
        enqueue(&q, p);
    }
    //print(&q);
    rr(&q, n);
}