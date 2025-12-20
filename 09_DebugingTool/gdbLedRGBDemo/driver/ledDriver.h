#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stddef.h>
#include <stdint.h>

/* Initialize LED strip with numPixels LEDs
 * Return 0 on success, -1 on failure
 */
int ledInit(size_t numPixels);

/* Free allocated memory */
void ledShutdown(void);

/* Set color of one pixel (GRB format internally) */
void ledSetPixelColor(size_t index, uint8_t r, uint8_t g, uint8_t b);

/* Fill entire strip with one color */
void ledFill(uint8_t r, uint8_t g, uint8_t b);

/* Clear strip (all pixels = black) */
void ledClear(void);

/* Get read-only pointer to buffer */
const uint32_t *ledGetBuffer(void);

/* Get number of pixels */
size_t ledGetPixelCount(void);

#endif /* LED_DRIVER_H */
