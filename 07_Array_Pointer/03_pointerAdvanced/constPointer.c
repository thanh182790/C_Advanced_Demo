#include <stdio.h>

int main()
{
    printf("\n===== DEMO: const with pointers =====\n\n");

    int a = 10, b = 20;

    /* 1. Pointer to const */
    printf("1. Pointer to const (cannot modify data but can change pointer):\n");
    // const int* p1 = &a; // same
    int const* p1 = &a;
    printf("p1 -> %d\n", *p1);

    // *p1 = 50;  // ERROR
    p1 = &b; // OK
    printf("p1 now -> %d\n\n", *p1);

    /* 2. Const pointer */
    printf("2. Const pointer (can modify data but cannot change pointer):\n");
    int* const p2 = &a;
    printf("p2 -> %d\n", *p2);

    *p2 = 99; // OK
    printf("After *p2 = 99, a = %d\n", a);

    //p2 = &b; // ERROR
    printf("\n");

    /* 3. Const pointer to const */
    printf("3. Const pointer to const (cannot modify both pointer and data):\n");
    const int *const p3 = &a;
    printf("p3 -> %d\n", *p3);

    // p3 = &b;  // ERROR
    // *p3 = 88; // ERROR

    printf("Nothing can be changed here.\n");

    printf("\n===== END CONST POINTER DEMO =====\n");
    return 0;
}
