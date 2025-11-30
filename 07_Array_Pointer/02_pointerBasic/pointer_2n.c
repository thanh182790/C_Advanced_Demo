#include <stdio.h>

int main() {

    int x = 10;
    int *p = &x;     
    int **p_ptr = &p;    
    printf("Value of x                   : %d\n", x);    //
    printf("Value via *p                 : %d\n", *p);
    printf("Value via **p_ptr            : %d\n", **p_ptr);   //10 -> *p+_ptr = &x ---> *(*p_ptr) = *(&x) = giá trị cua x

    printf("\nAddress of x                 : %p\n", (void*)&x);
    printf("Value stored in p            : %p (address of x)\n", (void*)p);
    printf("Address of p                 : %p\n", (void*)&p);
    printf("Value stored in p_ptr           : %p (address of p)\n", (void*)p_ptr);    //p_ptr = &p
    printf("Address of p_ptr                : %p\n\n", (void*)&p_ptr);

    printf("Changing x via **p_ptr ...\n");
    **p_ptr = 99;
    printf("x is now                     : %d\n\n", x);

}
