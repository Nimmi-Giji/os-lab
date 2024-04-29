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

    if((shmid = shmget(key, shm, IPC_CREAT|0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if((shmaddr = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Enter a string: ");
    fgets(shmaddr, shm, stdin);

    shmaddr[shm - 1] = '!';
    printf("Data written!");

    while(shmaddr[shm - 1]!='*') sleep(1);

    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}