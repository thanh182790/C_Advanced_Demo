#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    STATUS_OK = 0,
    STATUS_ERROR,
    STATUS_BUSY,
    STATUS_TIMEOUT
} Status_t;

#endif
