#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error open file data.txt");
        exit(1);
    }

    printf("A is writing string\n");
    for (int i = 0; i < 1000; i++) {
        char msg[128];
        snprintf(msg, sizeof(msg), "AAAAA - writeA - %d\n", i);
        write(fd, msg, strlen(msg));
        usleep(10000);
    }

    close(fd);
    printf("A written 1000 lines!\n");
    return 0;
}
