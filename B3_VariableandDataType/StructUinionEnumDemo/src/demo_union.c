// src/demo_union.c
#include "types.h"
#include <stdio.h>

// DÙNG HÀM TỪ demo_struct.c
extern SensorReading create_sample_sensor();

void print_hex(const void *p, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%02x ", ((uint8_t *)p)[i]);
    printf("\n");
}

void demo_union()
{
    printf("\n=== STAGE 2: TAGGED UNION (using SensorReading from STAGE 1) ===\n");

    LogEntry log;
    SensorReading sensor = create_sample_sensor();

    log.type = LOG_SENSOR;
    log.timestamp = 1000;
    log.data.sensor = sensor;

    printf("LogEntry.type = LOG_SENSOR\n");
    printf("LogEntry.data.sensor.temp = %.1f°C\n", log.data.sensor.temperature / 10.0);
    printf("Raw union memory (12 bytes):\n  ");
    print_hex(&log.data.sensor, sizeof(SensorReading));

    log.type = LOG_KEYPRESS;
    log.data.key = (KeyEvent){'M', 1};
    printf("\nSwitch to KEYPRESS → same memory reused!\n  ");
    print_hex(&log.data.key, 2);
}