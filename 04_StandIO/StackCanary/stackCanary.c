#include <stdio.h>
#include <string.h>

void vulnerable_function()
{
    char buffer[16];
    int grant_access = 0; // 0 = false

    printf("Enter text: ");
    gets(buffer); // Deliberate vulnerability (overflow)

    if (grant_access != 0)
    {
        // Nếu biến bị ghi đè → truy cập được cấp
        printf("\n[+] ACCESS GRANTED: Access has been granted.\n");
    }
    else
    {
        // Trường hợp overflow KHÔNG đè được grant_access
        printf("\n[-] ACCESS DENIED: Access has been denied.\n");
    }
}

int main()
{
    vulnerable_function();
    return 0;
}

/* gcc -fno-stack-protector stackCanary.c -o out */