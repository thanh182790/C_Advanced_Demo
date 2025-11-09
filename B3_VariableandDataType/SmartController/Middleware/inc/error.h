#ifndef ERROR_H
#define ERROR_H

typedef enum
{
    ERR_NONE = 0,
    ERR_SENSOR_FAIL,
    ERR_OVERHEAT,
    ERR_LOW_SOIL
} ErrorCode_t;

const char *errorToString(ErrorCode_t code);

#endif
