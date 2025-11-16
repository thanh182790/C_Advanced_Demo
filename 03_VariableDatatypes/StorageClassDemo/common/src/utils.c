#include "config.h"
#include <unistd.h>
#include <stdint.h>

void delayMs(uint32_t ms)
{
    volatile unsigned int i;
    for (; ms; ms--)
    {
        for (i = 0; i < 30000u; ++i)
        { /* busy */
        }
    }
}

void delayMsNonVolatile(uint32_t ms)
{
    unsigned int i;
    for (; ms; ms--)
    {
        for (i = 0; i < 30000u; ++i)
        { /* busy */
        }
    }
}
