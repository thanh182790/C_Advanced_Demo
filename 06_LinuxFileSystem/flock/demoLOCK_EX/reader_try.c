#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./reader_try [SH|EX]\n");
        return 1;
    }

    int mode = 0;
    if (strcmp(argv[1], "SH") == 0)
        mode = LOCK_SH | LOCK_NB;
    else if (strcmp(argv[1], "EX") == 0)
        mode = LOCK_EX | LOCK_NB;
    else
    {
        printf("Mode must be SH or EX\n");
        return 1;
    }

    int fd = open("demo.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    printf("Reader PID=%d: trying %s | NONBLOCK\n",
           getpid(), argv[1]);

    if (flock(fd, mode) < 0)
    {
        perror("flock");
        printf("Reader PID=%d: FAILED to acquire %s\n",
               getpid(), argv[1]);
        exit(1);
    }

    printf("Reader PID=%d: acquired %s\n", getpid(), argv[1]);
    sleep(5);

    printf("Reader PID=%d: unlocking\n", getpid());
    flock(fd, LOCK_UN);
    close(fd);

    return 0;
}
