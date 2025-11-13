// src/demo_struct.c
#include "types.h"
#include <stdio.h>

SensorReading create_sample_sensor()
{
    return (SensorReading){
        .id = 1,
        .temperature = 262, // 26.2°C
        .humidity = 58,
        .light = 72,
        .battery = 89,
        .timestamp = 12345678};
}

void demo_struct()
{
    printf("=== STAGE 1: STRUCT DEMO ===\n");

    SensorReading s = create_sample_sensor();

    printf("sizeof(SensorReading) = %zu bytes\n", sizeof(SensorReading));
    printf("sizeof(PacketHeader)  = %zu bytes\n", sizeof(PacketHeader));

    printf("\nSensorReading values:\n");
    printf("  ID: %d\n", s.id);
    printf("  Temp: %.1f°C\n", s.temperature / 10.0);
    printf("  Humidity: %d%%\n", s.humidity);
    printf("  Light: %d%%\n", s.light);
    printf("  Battery: %d%%\n", s.battery);
    printf("  Timestamp: %u ms\n", s.timestamp);

    printf("\nThis SensorReading will be used in STAGE 2 & 3!\n");
}