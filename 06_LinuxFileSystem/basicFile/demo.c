
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>
#include <stdio.h>

#define FILENAME "demo.txt"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)  // 0644

int main() {
    int fd;
    ssize_t bytes_written, bytes_read;
    char buffer[256];

    // ===================================================================
    // 1. Mở file (tạo mới nếu chưa có) - O_RDWR | O_CREAT | O_TRUNC
    // ===================================================================
    fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
    if (fd == -1) {
        // Dùng write() để in lỗi ra stderr (không dùng perror)
        const char msg[] = "Loi: khong mo duoc file!\n";
        write(STDERR_FILENO, msg, sizeof(msg) - 1);
        return 1;
    }

    // ===================================================================
    // 2. Ghi 10 dòng vào file bằng write()
    // ===================================================================
    for (int i = 0; i < 10; i++) {
        char line[128];
        int len = snprintf(line, sizeof(line), "Dong so %d - Xin chao tu system call!\n", i + 1);

        bytes_written = write(fd, line, len);
        if (bytes_written != len) {
            write(STDERR_FILENO, "Loi ghi file!\n", 14);
            close(fd);
            return 1;
        }
    }

    printf("Da ghi xong 10 dong vao file.\n");

    // ===================================================================
    // 3. Dùng lseek() để quay con trỏ về đầu file
    // ===================================================================
    if (lseek(fd, 0, SEEK_SET) == -1) {
        write(STDERR_FILENO, "Loi lseek!\n", 11);
        close(fd);
        return 1;
    }

    write(STDOUT_FILENO, "Doc lai noi dung file...\n", 26);

    // ===================================================================
    // 4. Đọc và in nội dung file bằng read()
    // ===================================================================
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';              // Thêm null terminator
        write(STDOUT_FILENO, buffer, bytes_read); // In ra màn hình
    }

    if (bytes_read == -1) {
        write(STDERR_FILENO, "Loi khi doc file!\n", 19);
    }

    // ===================================================================
    // 5. Đóng file
    // ===================================================================
    close(fd);

    write(STDOUT_FILENO, "\n=== Hoan tat chuong trinh ===\n", 31);
    return 0;
}
