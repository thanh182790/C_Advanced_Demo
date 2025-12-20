#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 * DEMO 1: Uninitialized local variable
 * ============================================================ */
void demo_uninit_local(void)
{
    int x; // uninitialized

    if (x > 0)
    {
        printf("x > 0\n");
    }
    else
    {
        printf("x <= 0\n");
    }
}

/* ============================================================
 * DEMO 2: Uninitialized heap memory
 * ============================================================ */
void demo_uninit_heap(void)
{
    int *p = malloc(sizeof(int));

    printf("value = %d\n", *p); // uninitialized read

    free(p);
}

/* ============================================================
 * DEMO 3: Out-of-bounds write (stack)
 * ============================================================ */
void demo_oob(void)
{
    int *arr = malloc(5 * sizeof(int));

    for (int i = 0; i <= 5; i++)
    {
        arr[i] = i;
    }

    free(arr);
}

/* ============================================================
 * DEMO 4: Use-after-free
 * ============================================================ */
void demo_use_after_free(void)
{
    int *p = malloc(sizeof(int));
    *p = 42;

    free(p);

    printf("%d\n", *p);
}

/* ============================================================
 * DEMO 5: Memory leak
 * ============================================================ */
void demo_leak(void)
{
    int *p = malloc(100 * sizeof(int));
    (void)p;
}

/* ============================================================
 * MAIN: select demo by compile-time flag
 * ============================================================ */
int main(void)
{
#if defined(DEMO_UNINIT_LOCAL)
    demo_uninit_local();

#elif defined(DEMO_UNINIT_HEAP)
    demo_uninit_heap();

#elif defined(DEMO_OUT_OF_BOUND)
    demo_oob();

#elif defined(DEMO_USE_AFTER_FREE)
    demo_use_after_free();

#elif defined(DEMO_LEAK)
    demo_leak();

#else
#error "No demo flag defined. Use -DDEMO_xxx"
#endif

    return 0;
}
