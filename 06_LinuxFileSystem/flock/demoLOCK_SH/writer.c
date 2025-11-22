// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int nonblock = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        nonblock = 1;

    int fd = open("demo.txt", O_WRONLY | O_APPEND);
    if (fd < 0)
    {
        perror("open demo.txt");
        return 1;
    }

    if (nonblock)
    {
        printf("[W] Trying LOCK_EX | LOCK_NB (non-blocking)...\n");
        if (flock(fd, LOCK_EX | LOCK_NB) != 0)
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                printf("[W] FAIL: cannot get LOCK_EX (would block).\n");
            else
                perror("flock LOCK_EX | LOCK_NB");
            close(fd);
            return 1;
        }
    }
    else
    {
        printf("[W] Trying LOCK_EX (blocking)...\n");
        printf("[W] If readers hold LOCK_SH, this will wait...\n");

        if (flock(fd, LOCK_EX) != 0)
        {
            perror("flock LOCK_EX");
            close(fd);
            return 1;
        }
    }

    printf("[W] LOCK_EX acquired. Writing to file...\n");

    const char *msg = "WRITE BY WRITER\n";
    write(fd, msg, strlen(msg));
    fsync(fd);

    printf("[W] Done. Releasing lock.\n");
    flock(fd, LOCK_UN);
    close(fd);
    return 0;
}
