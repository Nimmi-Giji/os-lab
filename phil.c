#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_mutex_t mutex;
sem_t forks[NUM_FORKS];

void* philosopher(void* arg) {
    int id = *(int *)arg;
    int right = id;
    int left = (id + 1)%NUM_FORKS;

    while(1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        pthread_mutex_lock(&mutex);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        pthread_mutex_unlock(&mutex);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }
    return NULL;
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);

    for(int i = 0 ; i < NUM_FORKS ; i++) 
        sem_init(&forks[i], 0, 1);

    for(int i = 0 ; i < NUM_PHILOSOPHERS ; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for(int i = 0 ; i < NUM_PHILOSOPHERS ; i++)
        pthread_join(philosophers[i], NULL);

    pthread_mutex_destroy(&mutex);

    for(int i = 0 ; i < NUM_FORKS ; i++) 
        sem_destroy(&forks[i]);
    
    return 0;
}