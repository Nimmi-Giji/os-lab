#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define NUM_PRO 2
#define NUM_CONS 4
#define BUFFER_SIZE 32

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
char buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

void* producer(void* arg) {
    int id = *(int *)arg;

    while(1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = (char)(count++ %26) + 65;
        printf("Producer %d writes %c\n", id, buffer[in]);
        in = (in+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(2);
    }
}

void* consumer(void* arg) {
    int id = *(int *)arg;

    while(1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("COnsumer %d consumes: %c\n", id, buffer[out]);
        out = (out+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}

int main() {
    pthread_t producers[NUM_PRO];
    pthread_t consumers[NUM_CONS];
    int pids[NUM_PRO];
    int cids[NUM_CONS];

    pthread_mutex_init(&mutex, NULL);

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for(int i = 0; i < NUM_PRO; i++) {
        pids[i] = i;
        pthread_create(&producers[i], NULL, producer, &pids[i]);
    }

    for(int i = 0; i < NUM_CONS; i++) {
        cids[i] = i;
        pthread_create(&consumers[i], NULL, consumer, &cids[i]);
    }

    for(int i = 0; i < NUM_PRO; i++)
        pthread_join(producers[i], NULL);

    for(int i = 0; i < NUM_CONS; i++)
        pthread_join(consumers[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}