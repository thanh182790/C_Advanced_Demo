#include "ledDriver.h"
#include <stdlib.h>
#include <string.h>

/* Internal state */
static uint32_t *ledBuffer = NULL;
static size_t ledCount = 0;

/* Helper: pack RGB into GRB 24-bit format */
static uint32_t packColor(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)g << 16) |
           ((uint32_t)r << 8) |
           ((uint32_t)b);
}

int ledInit(size_t numPixels)
{
    if (numPixels == 0)
    {
        return -1;
    }

    ledBuffer = (uint32_t *)malloc(numPixels * sizeof(uint32_t));
    if (ledBuffer == NULL)
    {
        return -1;
    }

    ledCount = numPixels;

    /* Initialize all pixels to black */
    memset(ledBuffer, 0, numPixels * sizeof(uint32_t));

    return 0;
}

void ledShutdown(void)
{
    if (ledBuffer != NULL)
    {
        free(ledBuffer);
        ledBuffer = NULL;
    }
    ledCount = 0;
}

void ledSetPixelColor(size_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (ledBuffer == NULL)
    {
        return;
    }

    /* Boundary check */
    if (index >= ledCount)
    {
        return;
    }

    ledBuffer[index] = packColor(r, g, b);
}

void ledFill(uint8_t r, uint8_t g, uint8_t b)
{
    if (ledBuffer == NULL)
    {
        return;
    }

    uint32_t color = packColor(r, g, b);

    for (size_t i = 0; i < ledCount; i++)
    {
        ledBuffer[i] = color;
    }
}

void ledClear(void)
{
    ledFill(0, 0, 0);
}

const uint32_t *ledGetBuffer(void)
{
    return ledBuffer;
}

size_t ledGetPixelCount(void)
{
    return ledCount;
}
