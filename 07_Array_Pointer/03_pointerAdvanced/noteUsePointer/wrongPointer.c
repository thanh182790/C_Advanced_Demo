#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void test_wrong(uint8_t *p)
{
    p = malloc(4);
    printf("Inside wrong: p = %p\n", p);
}

uint8_t *test_correct_1(void)
{
    return malloc(4);
}

void test_correct_2(uint8_t **p)
{
    *p = malloc(4);
}

int main(void)
{
    printf("=== SAI LAM NGHIEM TRONG ===\n");
    uint8_t *a = NULL;
    printf("Truoc goi: a = %p\n", a);
    test_wrong(a);
    printf("Sau goi : a = %p\n", a); // NULL or other and memorory leak?

    printf("=== CACH 1: TRA VE POINTER ===\n");
    uint8_t *b = test_correct_1();
    printf("b = %p\n", b);
    if (b)
    {
        b[0] = 123;
    }
    free(b);

    printf("\n=== CACH 2: POINTER TO POINTER ===\n");
    uint8_t *c = NULL;
    printf("Truoc: c = %p\n", c);
    test_correct_2(&c);
    printf("Sau : c = %p\n", c);
    if (c)
    {
        c[0] = 456;
    }
    free(c);

    return 0;
}
