#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main(int argc, char *argv[])
{
    int nonblock = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        nonblock = 1;

    int fd = open("demo.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    printf("Writer PID=%d: trying LOCK_EX %s\n",
           getpid(), nonblock ? "(non-block)" : "");

    int flags = LOCK_EX | (nonblock ? LOCK_NB : 0);
    if (flock(fd, flags) < 0)
    {
        perror("flock EX");
        printf("Writer PID=%d: FAILED to acquire LOCK_EX\n", getpid());
        exit(1);
    }

    printf("Writer PID=%d: acquired LOCK_EX\n", getpid());

    char msg[128];
    snprintf(msg, sizeof(msg), "Writer PID=%d wrote line\n", getpid());

    ssize_t w = write(fd, msg, strlen(msg));
    if (w < 0)
        perror("write");

    // Chờ ENTER để thả lock
    printf("Press ENTER to release LOCK_EX...\n");
    getchar();

    printf("Writer PID=%d: unlocking\n", getpid());
    flock(fd, LOCK_UN);
    close(fd);
}
