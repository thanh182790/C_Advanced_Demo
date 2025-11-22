// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    const char *id = (argc > 1) ? argv[1] : "R";

    int fd = open("demo.txt", O_RDWR | O_APPEND);
    if (fd < 0)
    {
        perror("open demo.txt");
        return 1;
    }

    printf("[%s] opened demo.txt. Trying LOCK_SH...\n", id);

    if (flock(fd, LOCK_SH) != 0)
    {
        perror("flock LOCK_SH");
        close(fd);
        return 1;
    }

    printf("[%s] LOCK_SH acquired.\n", id);

    // const char *msg = "WRITE BY READER\n";
    // write(fd, msg, strlen(msg));

    // Đọc file
    if (lseek(fd, 0, SEEK_SET) < 0)
        perror("lseek");

    char buf[256];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n < 0)
    {
        perror("read");
    }
    else
    {
        buf[n] = '\0';
        printf("[%s] File content:\n-----\n%s-----\n", id, buf);
    }

    // Chờ ENTER để thả lock
    printf("[%s] Press ENTER to release LOCK_SH...\n", id);
    getchar();

    printf("[%s] Releasing LOCK_SH and exiting.\n", id);
    flock(fd, LOCK_UN);
    close(fd);
    return 0;
}
