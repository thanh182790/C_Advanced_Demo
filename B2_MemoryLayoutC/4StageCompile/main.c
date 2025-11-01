#include <stdio.h>
#include "math_utils.h"

int main(void)
{
    int x = 5, y = 3;
    printf("x + y = %d\n", add(x, y));
    printf("x * y = %d\n", multiply(x, y));
    return 0;
}

