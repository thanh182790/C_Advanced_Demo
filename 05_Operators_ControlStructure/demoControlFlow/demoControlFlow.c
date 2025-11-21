#include <stdio.h>
#include <stdint.h>
#include <time.h>

typedef enum
{
    DEV_0,
    DEV_1,
    DEV_2,
    DEV_3,
    DEV_4,
    DEV_5,
    DEV_6,
    DEV_7,
    DEV_8,
    DEV_9,
    DEV_10,
    DEV_11,
    DEV_12,
    DEV_13,
    DEV_14,
    DEV_15,
    DEV_16,
    DEV_17,
    DEV_18,
    DEV_19,
    DEV_20,
    DEV_21,
    DEV_22,
    DEV_23,
    DEV_24,
    DEV_25,
    DEV_26,
    DEV_27,
    DEV_28,
    DEV_29,
    DEV_30,
    DEV_31,
    DEV_COUNT
} DeviceCode;

volatile uint32_t systemRegister = 0;

// Complex dummy processing function to simulate "work"
static inline uint32_t complexWork(uint32_t x, int factor)
{
    x = (x ^ (factor * 1234567));
    x = (x << (factor % 5)) | (x >> (32 - (factor % 5)));
    x += factor * 37;
    x ^= (x >> 3);
    x *= (factor * 13 + 7);
    return x;
}

// ===================================================================
// IF–ELSE version
// ===================================================================
void processDeviceIf(DeviceCode code)
{
    if (code == DEV_0)
        systemRegister = complexWork(systemRegister, 0);
    else if (code == DEV_1)
        systemRegister = complexWork(systemRegister, 1);
    else if (code == DEV_2)
        systemRegister = complexWork(systemRegister, 2);
    else if (code == DEV_3)
        systemRegister = complexWork(systemRegister, 3);
    else if (code == DEV_4)
        systemRegister = complexWork(systemRegister, 4);
    else if (code == DEV_5)
        systemRegister = complexWork(systemRegister, 5);
    else if (code == DEV_6)
        systemRegister = complexWork(systemRegister, 6);
    else if (code == DEV_7)
        systemRegister = complexWork(systemRegister, 7);
    else if (code == DEV_8)
        systemRegister = complexWork(systemRegister, 8);
    else if (code == DEV_9)
        systemRegister = complexWork(systemRegister, 9);
    else if (code == DEV_10)
        systemRegister = complexWork(systemRegister, 10);
    else if (code == DEV_11)
        systemRegister = complexWork(systemRegister, 11);
    else if (code == DEV_12)
        systemRegister = complexWork(systemRegister, 12);
    else if (code == DEV_13)
        systemRegister = complexWork(systemRegister, 13);
    else if (code == DEV_14)
        systemRegister = complexWork(systemRegister, 14);
    else if (code == DEV_15)
        systemRegister = complexWork(systemRegister, 15);
    else if (code == DEV_16)
        systemRegister = complexWork(systemRegister, 16);
    else if (code == DEV_17)
        systemRegister = complexWork(systemRegister, 17);
    else if (code == DEV_18)
        systemRegister = complexWork(systemRegister, 18);
    else if (code == DEV_19)
        systemRegister = complexWork(systemRegister, 19);
    else if (code == DEV_20)
        systemRegister = complexWork(systemRegister, 20);
    else if (code == DEV_21)
        systemRegister = complexWork(systemRegister, 21);
    else if (code == DEV_22)
        systemRegister = complexWork(systemRegister, 22);
    else if (code == DEV_23)
        systemRegister = complexWork(systemRegister, 23);
    else if (code == DEV_24)
        systemRegister = complexWork(systemRegister, 24);
    else if (code == DEV_25)
        systemRegister = complexWork(systemRegister, 25);
    else if (code == DEV_26)
        systemRegister = complexWork(systemRegister, 26);
    else if (code == DEV_27)
        systemRegister = complexWork(systemRegister, 27);
    else if (code == DEV_28)
        systemRegister = complexWork(systemRegister, 28);
    else if (code == DEV_29)
        systemRegister = complexWork(systemRegister, 29);
    else if (code == DEV_30)
        systemRegister = complexWork(systemRegister, 30);
    else if (code == DEV_31)
        systemRegister = complexWork(systemRegister, 31);
}

// ===================================================================
// SWITCH–CASE version (compiler sẽ tạo jump table)
// ===================================================================
void processDeviceSwitch(DeviceCode code)
{
    switch (code)
    {
    case DEV_0:
        systemRegister = complexWork(systemRegister, 0);
        break;
    case DEV_1:
        systemRegister = complexWork(systemRegister, 1);
        break;
    case DEV_2:
        systemRegister = complexWork(systemRegister, 2);
        break;
    case DEV_3:
        systemRegister = complexWork(systemRegister, 3);
        break;
    case DEV_4:
        systemRegister = complexWork(systemRegister, 4);
        break;
    case DEV_5:
        systemRegister = complexWork(systemRegister, 5);
        break;
    case DEV_6:
        systemRegister = complexWork(systemRegister, 6);
        break;
    case DEV_7:
        systemRegister = complexWork(systemRegister, 7);
        break;
    case DEV_8:
        systemRegister = complexWork(systemRegister, 8);
        break;
    case DEV_9:
        systemRegister = complexWork(systemRegister, 9);
        break;
    case DEV_10:
        systemRegister = complexWork(systemRegister, 10);
        break;
    case DEV_11:
        systemRegister = complexWork(systemRegister, 11);
        break;
    case DEV_12:
        systemRegister = complexWork(systemRegister, 12);
        break;
    case DEV_13:
        systemRegister = complexWork(systemRegister, 13);
        break;
    case DEV_14:
        systemRegister = complexWork(systemRegister, 14);
        break;
    case DEV_15:
        systemRegister = complexWork(systemRegister, 15);
        break;
    case DEV_16:
        systemRegister = complexWork(systemRegister, 16);
        break;
    case DEV_17:
        systemRegister = complexWork(systemRegister, 17);
        break;
    case DEV_18:
        systemRegister = complexWork(systemRegister, 18);
        break;
    case DEV_19:
        systemRegister = complexWork(systemRegister, 19);
        break;
    case DEV_20:
        systemRegister = complexWork(systemRegister, 20);
        break;
    case DEV_21:
        systemRegister = complexWork(systemRegister, 21);
        break;
    case DEV_22:
        systemRegister = complexWork(systemRegister, 22);
        break;
    case DEV_23:
        systemRegister = complexWork(systemRegister, 23);
        break;
    case DEV_24:
        systemRegister = complexWork(systemRegister, 24);
        break;
    case DEV_25:
        systemRegister = complexWork(systemRegister, 25);
        break;
    case DEV_26:
        systemRegister = complexWork(systemRegister, 26);
        break;
    case DEV_27:
        systemRegister = complexWork(systemRegister, 27);
        break;
    case DEV_28:
        systemRegister = complexWork(systemRegister, 28);
        break;
    case DEV_29:
        systemRegister = complexWork(systemRegister, 29);
        break;
    case DEV_30:
        systemRegister = complexWork(systemRegister, 30);
        break;
    case DEV_31:
        systemRegister = complexWork(systemRegister, 31);
        break;
    }
}

// ===================================================================
// Benchmark
// ===================================================================
int main()
{
    const int ITER = 30000000; // 30 million iterations
    clock_t start, end;
    for (int i = 0; i < 20; i++)
    {
        printf("---Loop %d---\n", i);
        // IF
        start = clock();
        for (int i = 0; i < ITER; i++)
            processDeviceIf(i % DEV_COUNT);
        end = clock();
        printf("  IF-ELSE: %.3f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        systemRegister = 0;

        // SWITCH
        start = clock();
        for (int i = 0; i < ITER; i++)
            processDeviceSwitch(i % DEV_COUNT);
        end = clock();
        printf("  SWITCH-CASE: %.3f sec\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    }

    return 0;
}
