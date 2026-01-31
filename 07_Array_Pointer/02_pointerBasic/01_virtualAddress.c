#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define PFN_MASK ((1ULL << 55) - 1)

/*
/proc/self/pagemap
- entry 0:  - VFPN0
    ( 8 byte - 64 bit) -
    bit 63: page vật lý có tồn tại không. 
    bit 0-54 : đại diện cho giá trị của page vật lý ( nằm ở page số bao nhiêu)
- entry 1: - VFPN1
- entry 2: - VFPN2
......
*/

int main() {
    int var = 100;
    int fd;
    uint64_t entry, pfn;
    off_t offset_entry;

    printf("Virtual address of var: %p\n", &var);

    fd = open("/proc/self/pagemap", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    offset_entry = (uintptr_t)&var / PAGE_SIZE * sizeof(entry); /* 1 entry dại diện cho 1 VPFN - kich thước 1 entry là 8 byte */
    if (lseek(fd, offset_entry, SEEK_SET) == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    if (read(fd, &entry, sizeof(entry)) != sizeof(entry)) { /* Đọc giá trị cho entry chứa biên var */
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);

    if ((entry & (1ULL << 63)) == 0) {    /* Bit 63 thể hiện page physical có tồn tại không */
        printf("Page not present\n");
        return 1;
    }

    pfn = entry & PFN_MASK;
    printf("Physical address: 0x%lx\n",
        (pfn << PAGE_SHIFT) | ((uintptr_t)&var & (PAGE_SIZE - 1)));

    return 0;
}
