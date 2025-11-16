// file_full.c
#include <stdio.h>

int main()
{
    FILE *fp = fopen("output_full.txt", "w");
    if (!fp)
        return 1;

    char buf[8192];                        // Buffer 8KB
    setvbuf(fp, buf, _IOFBF, sizeof(buf)); // Full buffering

    for (int i = 0; i < 10000000; i++)
    {
        fprintf(fp, "Line %d\n", i);
    }

    fclose(fp); // Tự động flush khi đóng
    return 0;
}
