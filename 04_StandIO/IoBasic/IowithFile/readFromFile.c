#include <stdio.h>

int main()
{
    
    char name[100];
    int age;

    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        perror("Loi mo file input.txt");
        return 1;
    }

    if (fscanf(fp, "Ten: %99[^\n]\nTuoi: %d", name, &age) == 2)
    {
        printf("Doc tu file:\n");
        printf("Ten: %s\n", name);
        printf("Tuoi: %d\n", age);
    }
    else
    {
        printf("Loi dinh dang du lieu trong file!\n");
    }

    fclose(fp);
    return 0;
}
