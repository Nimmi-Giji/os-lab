#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    printf("Parent Process\n");
    int status;
    pid_t pid;

    pid = fork();

    if( pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if(pid == 0) {
        printf("Child Process - pid %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        wait(&status);
        if(WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        else
            printf("Child terminated abnormally\n");

        printf("Back to parent process - pid %d\n", getpid());
        printf("Closing std i/o\n");
        close(STDOUT_FILENO);
    }
}