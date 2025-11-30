#include <stdio.h>
#include <stdint.h>

int main()
{
    printf("===== DEMO 1: uint8_t* reading int array =====\n");

    int arr_int[3] = {0x11223344, 0x55667788, 0xAABBCCDD};

    uint8_t *p8 = (uint8_t *)arr_int;

    for (int i = 0; i < sizeof(arr_int); i++)
    {
        printf("p8 + %d -> address: %p | value: 0x%02X\n",
               i, (void *)(p8 + i), *(p8 + i));
    }

    printf("\n===== DEMO 2: int* reading uint8_t array =====\n");

    uint8_t arr_u8[12];
    for (int i = 0; i < 12; i++)
    {
        arr_u8[i] = i + 1; // values: 1..12
    }

    int *p32 = (int *)arr_u8;
    int count_int = sizeof(arr_u8) / sizeof(int);

    for (int i = 0; i < count_int; i++)
    {
        printf("p32 + %d -> address: %p | value: 0x%08X\n",
               i, (void *)(p32 + i), *(p32 + i));
    }

    printf("\n===== DEMO 3: Pointer arithmetic difference =====\n");

    int arr_test[3] = {10, 20, 30};

    int *p_int = arr_test;
    char *p_char = (char *)arr_test;

    printf("int*   p_int + 1   -> %p (moves 4 bytes)\n", (void *)(p_int + 1));
    printf("char*  p_char + 1  -> %p (moves 1 byte)\n", (void *)(p_char + 1));

    return 0;
}
