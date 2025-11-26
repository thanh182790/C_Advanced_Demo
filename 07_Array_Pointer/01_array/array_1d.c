#include <stdio.h>

#define ARRAY_SIZE 10

void demo_array_init(void)
{

    printf("===== CACH 1 =====\n");
    int arr1[ARRAY_SIZE] = {1, 65535, 200, 555, 9, 456, 999, 8, 10000, 666};

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("arr1[%d] = %d\n", i, arr1[i]);
    }

    printf("\n===== CACH 2 =====\n");
    int arr2[ARRAY_SIZE] = {0};

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("arr2[%d] = %d\n", i, arr2[i]);
    }

    printf("\n===== CACH 3 =====\n");
    int arr3[ARRAY_SIZE] = {1, 5};

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("arr3[%d] = %d\n", i, arr3[i]);
    }

    printf("\n===== CACH 4 =====\n");
    int arr4[ARRAY_SIZE]; // các giá trị có thể là bất kì hoặc 0

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("arr4[%d] = %d\n", i, arr4[i]);
    }
}

int main(void)
{
    demo_array_init();
    return 0;
}
