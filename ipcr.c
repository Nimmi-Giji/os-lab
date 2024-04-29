#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#define shm 32

int main() {
    int shmid;
    char* shmaddr;
    key_t key = 1234;

    if((shmid = shmget(key, shm, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1){
        perror("shmat");
        exit(1);
    }

    while(shmaddr[shm - 1]!='!') sleep(1);

    printf("Data read %s\n", shmaddr);

    shmaddr[shm - 1] = '*';

    shmdt(shmaddr);
    
    return 0;
}