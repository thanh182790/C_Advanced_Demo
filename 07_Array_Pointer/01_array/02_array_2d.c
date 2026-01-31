#include <stdio.h>

#define ROW 3
#define COL 4

void showAddress(int arr[][COL], int row)
{
    printf("\n===== Address =====\n");    

    for (int i = 0; i < row; i++)
    {
        printf("[ ");
        for (int j = 0; j < COL; j++)
        {
            printf("%p ", (int*)&arr[i][j]);
        }
        printf("]\n");
    }
}

void print_2d_array(int arr[][COL], int row)
{
    printf("\n===== Giá trị mảng là =====\n");

    for (int i = 0; i < row; i++)
    {
        printf("[ ");
        for (int j = 0; j < COL; j++)
        {
            printf("%5d ", arr[i][j]);
        }
        printf("]\n");
    }
}

void demo_2d_array_init(void)
{
    printf("===== CACH 1 =====\n");
    int a1[ROW][COL] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}};

    print_2d_array(a1, ROW);
    showAddress(a1, ROW);

    printf("\n===== CACH 2 =====\n");
    int a2[ROW][COL] = {
        {1, 2},
        {3},
        {4, 5, 6}};

    print_2d_array(a2, ROW);

    printf("\n===== CACH 3 =====\n");
    int a3[][COL] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80}};
    int row3 = sizeof(a3) / sizeof(a3[0]);

    print_2d_array(a3, row3);

    printf("\n===== CACH 4 =====\n");
    int a4[ROW][COL] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12};

    print_2d_array(a4, ROW);

    printf("\n===== CACH 5 =====\n");
    int a5[ROW][COL];

    print_2d_array(a5, ROW);
}

int main(void)
{
    demo_2d_array_init();
    return 0;
}
