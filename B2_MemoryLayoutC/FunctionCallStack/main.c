#include <stdio.h>

void funcB(int a, int b)
{
    static int total = 10;
    int sum = a + b;
    printf("Total = %d\n", total);
    printf("Sum of a + b = %d\n", sum);
}

void funcA(void)
{
    int n = 5;
    int m = 7;
    funcB(n, m);
}

int main(void)
{
    funcA();
    return 0;
}
