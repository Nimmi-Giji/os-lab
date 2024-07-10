#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    char source[20], dest[20];
    printf("Enter Source, Destination File: ");
    scanf("%s %s", source, dest);

    int source_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    source_fd = open(source, O_RDONLY);
    if(source_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    dest_fd = open(dest, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(dest_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if(bytes_read!=bytes_written) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if(bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    if(close(source_fd) == -1 || close(dest_fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}