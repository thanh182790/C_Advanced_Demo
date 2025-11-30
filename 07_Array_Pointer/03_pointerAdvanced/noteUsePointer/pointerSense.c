#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void test(uint8_t *z)
{
    printf("Gia tri cua z la: %p\n", z);
    *z = (uint8_t)malloc(4);
    printf("Gia tri cua *z: %p\n", *z);
}

int main(void)
{
    uint8_t *aptr = NULL;

    printf("Truoc khi goi: aptr = %p, Dịa chi cua aptr = %p\n", (void *)aptr, &aptr);

    test((uint8_t*)&aptr);

    printf("Sau khi goi : aptr = %p, Dia chi cua aptr = %p\n", (void *)aptr, &aptr);

    if (aptr)
    {
        aptr[0] = 1; /* --- is it OK ?---*/
        printf("Da ghi: %d\n", aptr[0]);
    }

    return 0;
}





// void test(uint8_t **z)
// {
//     printf("Gia tri cua z la: %p\n", z);
//     *z = malloc(4);
//     printf("Gia tri cua *z: %p\n", *z);
// }

// int main(void)
// {
//     uint8_t *aptr = NULL;

//     printf("Truoc khi goi: aptr = %p, Dia chi cua aptr = %p\n", (void *)aptr, &aptr);

//     test(&aptr);

//     printf("Sau khi goi : aptr = %p, Dia chi cua aptr = %p\n", (void *)aptr, &aptr);

//     if (aptr)
//     {
//         aptr[0] = 1;
//         printf("Da ghi: %d\n", aptr[0]);
//     }

//     free(aptr);
//     return 0;
// }