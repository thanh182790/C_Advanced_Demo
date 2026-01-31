#include <stdio.h>

int main()
{

    int arr[5] = {10, 20, 30, 40, 50};
    int other_array[5] = {100, 200, 300, 400, 500};
    int *ptr = arr;
    ptr = other_array;
    // arr = other_array;
   // arr++;
    ptr = arr + 1;
    // printf("Accessing the element at index 2 (should be 30):\n");
    // printf("Using array indexing: arr[2] = %d\n", arr[2]);
    // printf("Using pointer arithmetic on array name: *(arr + 2) = %d\n", *(arr + 2));
    printf("Using array indexing through pointer: ptr[2] = %d\n", ptr[2]);
    printf("Using pointer arithmetic on ptr: *(ptr + 2) = %d\n\n", *(ptr + 2));

    // 2. Duyệt mảng bằng con trỏ
    printf("Traversing the array using a pointer:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("*(ptr + %d) = %d   |   address = %p\n", i, *(ptr + i), (ptr + i));
    }
    printf("\n");

    return 0;
}
