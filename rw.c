#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define NUM_WRITERS 2
#define NUM_READERS 4

pthread_mutex_t rw_mutex;
pthread_mutex_t mutex;
int read_count = 0;
int data = 1;

void* writer(void* arg) {
    int id = *(int *)arg;

    while(1) {
        pthread_mutex_lock(&rw_mutex);
        data *= 2;
        printf("Writer %d writes %d\n", id, data);
        pthread_mutex_unlock(&rw_mutex);
        sleep(2);
    }
}

void* reader(void* arg) {
    int id = *(int *)arg;

    while(1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if(read_count == 1)
            pthread_mutex_lock(&rw_mutex);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d reads %d\n", id, data);

        pthread_mutex_lock(&mutex);
        read_count--;
        if(read_count == 0)
            pthread_mutex_unlock(&rw_mutex);
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
}

int main() {
    pthread_t writers[NUM_WRITERS];
    pthread_t  readers[NUM_READERS];
    int wids[NUM_WRITERS];
    int rids[NUM_READERS];

    pthread_mutex_init(&rw_mutex, NULL);
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0 ;i < NUM_WRITERS; i++) {
        wids[i] = i;
        pthread_create(&writers[i], NULL, writer, &wids[i]);
    }

    for(int i = 0; i < NUM_READERS; i++) {
        rids[i] = i;
        pthread_create(&readers[i], NULL, reader, &rids[i]);
    }

    for(int i = 0; i < NUM_WRITERS; i++)
        pthread_join(writers[i], NULL);

    for(int i = 0; i < NUM_READERS; i++)
        pthread_join(readers[i], NULL);

    pthread_mutex_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);
}