#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> 

#include "../driver/ledDriver.h"

#define DEFAULT_LED_COUNT 10

static void printUsage(const char *progName)
{
    printf("Usage:\n");
    printf("  %s [num_led]\n", progName);
    printf("\n");
    printf("If num_led is not provided, default is %d\n", DEFAULT_LED_COUNT);
}

static void printPixel(const uint32_t *buf, size_t index)
{
    printf("Pixel[%zu] = 0x%08X\n", index, buf[index]);
}

int main(int argc, char *argv[])
{
    size_t ledCount = DEFAULT_LED_COUNT;
    int *p = 0;
    *p = 23;
    /* ================= Parse argument ================= */
    if (argc > 2) {
        printUsage(argv[0]);
        return -1;
    }

    if (argc == 2) {
        ledCount = (size_t)atoi(argv[1]);
        if (ledCount == 0) {
            printUsage(argv[0]);
            return -1;
        }
    }

    printf("LED count = %zu\n", ledCount);

    /* 1. Init LEDs */
    if (ledInit(ledCount) != 0) {
        printf("LED init failed\n");
        return -1;
    }

    /* 2. Check buffer initialized to 0 */
    const uint32_t *buffer = ledGetBuffer();
    printf("After init:\n");
    printPixel(buffer, 0);

    /* 3. First pixel = Red (255,0,0) */
    ledSetPixelColor(0, 255, 0, 0);

    /* 4. Last pixel = Blue (0,0,255) */
    if (ledCount > 1) {
        ledSetPixelColor(ledCount - 1, 0, 0, 255);
    }

    /* 5. Middle pixel = White */
    if (ledCount > 4) {
        ledSetPixelColor(4, 255, 255, 255);
    }

    /* 6. Get buffer */
    buffer = ledGetBuffer();

    /* 7. Print values */
    printf("\nAfter setting individual pixels:\n");
    printPixel(buffer, 0);

    if (ledCount > 4) {
        printPixel(buffer, 4);
    }

    if (ledCount > 1) {
        printPixel(buffer, ledCount - 1);
    }

    /* 8. Fill all pixels with Green (0,255,0) */
    ledFill(0, 255, 0);

    /* 9. Verify all pixels */
    printf("\nAfter ledFill(Green):\n");
    for (size_t i = 0; i < ledGetPixelCount(); i++) {
        printPixel(buffer, i);
    }

    // while (1)
    // {
    //     sleep(10);
    // }

    /* 10. Shutdown */
    ledShutdown();

    return 0;
}
