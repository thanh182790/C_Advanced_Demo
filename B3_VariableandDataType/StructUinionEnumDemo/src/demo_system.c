// src/demo_full.c
#include "types.h"
#include <stdio.h>

// DÙNG HÀM TỪ CÁC STAGE TRƯỚC
extern SensorReading create_sample_sensor();

#define MAX_LOGS 5
LogEntry log_buffer[MAX_LOGS];
uint8_t log_count = 0;
SystemState state = STATE_POWER_ON;

const char *state_str[] = {
    "POWER_ON", "IDLE", "READING_SENSOR", "LOGGING", "ERROR", "SLEEP"};

ErrorCode add_log(LogEntry *entry)
{
    if (log_count >= MAX_LOGS)
        return ERR_LOG_FULL;
    log_buffer[log_count++] = *entry;
    return ERR_NONE;
}

void run_system()
{
    printf("\n=== STAGE 3: FULL EMBEDDED SYSTEM LOOP ===\n");

    // 1. Boot
    state = STATE_IDLE;
    printf("[STATE] %s\n", state_str[state]);
    add_log(&(LogEntry){.type = LOG_BOOT, .timestamp = 0});

    // 2. Read sensor → log
    state = STATE_READING_SENSOR;
    printf("[STATE] %s\n", state_str[state]);

    SensorReading s = create_sample_sensor(); // ← DÙNG TỪ STAGE 1
    LogEntry sensor_log = {
        .type = LOG_SENSOR,
        .timestamp = 100,
        .data.sensor = s};
    state = STATE_LOGGING;
    printf("[STATE] %s\n", state_str[state]);
    ErrorCode err = add_log(&sensor_log);

    // 3. Key press
    LogEntry key_log = {
        .type = LOG_KEYPRESS,
        .timestamp = 200,
        .data.key = {'A', 1}};
    add_log(&key_log);

    // 4. Error
    state = STATE_ERROR;
    printf("[STATE] %s → Sensor timeout!\n", state_str[state]);
    if (err == ERR_LOG_FULL)
    {
        printf("[ERROR] Log buffer full!\n");
    }

    // 5. Print logs
    printf("\nLog Buffer (%d entries):\n", log_count);
    for (int i = 0; i < log_count; i++)
    {
        LogEntry *l = &log_buffer[i];
        printf("  [%d] Type=%d, TS=%u → ", i, l->type, l->timestamp);
        if (l->type == LOG_SENSOR)
        {
            printf("Temp=%.1f°C", l->data.sensor.temperature / 10.0);
        }
        else if (l->type == LOG_KEYPRESS)
        {
            printf("Key='%c'", l->data.key.key_code);
        }
        printf("\n");
    }
}