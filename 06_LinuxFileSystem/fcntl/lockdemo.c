#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void print_lock_type(short type)
{
    if (type == F_RDLCK)
        printf("READ LOCK");
    else if (type == F_WRLCK)
        printf("WRITE LOCK");
    else
        printf("UNLOCK");
}

int set_lock(int fd, short type, int start, int len, int blocking)
{
    struct flock lk;
    lk.l_type = type;
    lk.l_whence = SEEK_SET;
    lk.l_start = start;
    lk.l_len = len;

    int cmd = blocking ? F_SETLKW : F_SETLK;

    printf("PID %d: Trying to acquire ", getpid());
    print_lock_type(type);
    printf(" on [%d, %d] %s\n",
           start, start + len - 1,
           blocking ? "(blocking)" : "(non-block)");

    if (fcntl(fd, cmd, &lk) == -1)
    {
        printf("PID %d: FAILED to lock (%s)\n", getpid(), strerror(errno));
        return -1;
    }

    printf("PID %d: LOCKED byte from [%d, %d] as ", getpid(), start, start + len - 1);
    print_lock_type(type);
    printf("\n");
    return 0;
}

void unlock_region(int fd, int start, int len)
{
    struct flock lk;
    lk.l_type = F_UNLCK;
    lk.l_whence = SEEK_SET;
    lk.l_start = start;
    lk.l_len = len;

    fcntl(fd, F_SETLK, &lk);
    printf("PID %d: UNLOCKED [%d, %d]\n",
           getpid(), start, start + len - 1);
}

void read_region(int fd, int start, int len)
{
    char buf[1024] = {0};
    lseek(fd, start, SEEK_SET);
    int n = read(fd, buf, len);
    if (n > 0)
    {
        buf[n] = '\0';
        printf("PID %d: READ from byte [%d,%d] = \"%s\"\n",
               getpid(), start, start + n - 1, buf);
    }
    else
    {
        printf("PID %d: READ FAILED (%s)\n", getpid(), strerror(errno));
    }
}

void write_region(int fd, int start, const char *msg)
{
    lseek(fd, start, SEEK_SET);
    int n = write(fd, msg, strlen(msg));
    if (n > 0)
        printf("PID %d: WROTE \"%s\" at [%d,%d]\n", getpid(), msg, start, start + n - 1);
    else
        printf("PID %d: WRITE FAILED (%s)\n", getpid(), strerror(errno));
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf("Usage: ./lockdemo [R|W] start length [block|nonblock] [msg-if-write-if-W]\n");
        exit(1);
    }

    short type = (argv[1][0] == 'W') ? F_WRLCK : F_RDLCK;

    if (type == F_WRLCK && argc < 6)
    {
        printf("WRITE lock requires message: ./lockdemo W start length block MSG\n");
        exit(1);
    }

    int fd = open("demo.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    int start = atoi(argv[2]);
    int len = atoi(argv[3]);
    int blocking = strcmp(argv[4], "block") == 0;

    // Hiển thị nội dung vùng trước khi lock
    printf("PID %d: BEFORE LOCK - File content\n", getpid());
    read_region(fd, start, len);

    if (set_lock(fd, type, start, len, blocking) == -1)
    {
        close(fd);
        exit(1);
    }

    // Nếu là WRITE, ghi msg vào vùng
    if (type == F_WRLCK)
        write_region(fd, start, argv[5]);

    printf("PID %d: LOCK is active. Press ENTER to unlock...\n", getpid());
    getchar(); // chờ nhấn ENTER

    unlock_region(fd, start, len);

    // Hiển thị vùng sau khi unlock
    printf("PID %d: AFTER UNLOCK content:\n", getpid());
    read_region(fd, start, len);

    close(fd);
    return 0;
}
