#include "error.h"
#include <stdio.h>

const char *errorToString(ErrorCode_t code)
{
    switch (code)
    {
    case ERR_NONE:
        return "No error";
    case ERR_SENSOR_FAIL:
        return "Sensor failure";
    case ERR_OVERHEAT:
        return "Overheat";
    case ERR_LOW_SOIL:
        return "Low soil moisture";
    default:
        return "Unknown";
    }
}
