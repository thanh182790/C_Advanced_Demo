#include <stdio.h>
#include <string.h>

void printInt(void *p)
{
    printf("Int value: %d\n", *(int*)p);
}

void printFloat(void *p)
{
    printf("Float value: %.2f\n", *(float *)p);
}

void traverseIntArray(void *arr, int size)
{
    int *p = (int *)arr;
    printf("Traverse int array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
}

int main()
{

    printf("===== DEMO: void pointer =====\n\n");

    int a = 42;
    float b = 3.14f;

    void *vp;

    // =======================
    // 1. void* can point to any data type
    // =======================
    printf("1. void* can hold address of any type:\n");

    vp = &a;
    printInt(vp);

    vp = &b;
    printFloat(vp);

    printf("\n");

    // =======================
    // 2. Cannot dereference (*vp) directly – must cast first
    // =======================
    printf("2. Cannot dereference void* directly (*vp). Must cast it:\n");

    vp = &a;

    // Wrong:
    // printf("%d", *vp);  // compile error

    printf("Correct access (cast to int*): *(int*)vp = %d\n\n", *(int *)vp);

    // =======================
    // 3. Cannot do pointer arithmetic on void*
    // =======================
    printf("3. Cannot increment vp (vp++). void* has no element size:\n");

    vp = &a;
    vp++;  // compile error

    printf("→ To increment, cast to a specific type first (e.g., int*):\n");
    int *ip = (int *)vp;
    ip++; // moves sizeof(int) bytes
    printf("After ip++, it now points to a different memory location (do not use)\n\n");

    // =======================
    // 4. Traversing an array using void*
    // =======================
    printf("4. Traversing an int array using void*:\n");

    int arr[] = {10, 20, 30, 40, 50};
    vp = arr;
    traverseIntArray(vp, 5);
    printf("\n");

    printf("\n===== END OF DEMO =====\n");

    return 0;
}
