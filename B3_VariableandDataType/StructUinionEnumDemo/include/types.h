// include/types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// ====================== STAGE 1: STRUCT (dùng ở cả 3 stage) ======================
typedef struct
{
    uint8_t id;
    uint16_t temperature; // x10 → 25.5°C = 255
    uint16_t humidity;    // %
    uint8_t light;        // 0-100
    uint8_t battery;      // %
    uint32_t timestamp;
} SensorReading; // ← DÙNG TRONG UNION & STATE MACHINE

typedef struct
{
    uint8_t node_id;
    uint8_t event_type;
    uint32_t sequence;
    uint8_t checksum;
} PacketHeader; // ← DÙNG TRONG LOG HEADER (mở rộng sau)

// ====================== STAGE 2: TAGGED UNION (dùng SensorReading) ======================
typedef enum
{
    LOG_BOOT,
    LOG_SENSOR, // ← chứa SensorReading
    LOG_KEYPRESS,
    LOG_ERROR
} LogType;

typedef struct
{
    uint8_t key_code;
    uint8_t pressed;
} KeyEvent;

typedef struct
{
    uint8_t code;
    uint8_t severity;
} ErrorEvent;

typedef struct
{
    LogType type;
    uint32_t timestamp;
    union
    {
        SensorReading sensor; // ← DÙNG STRUCT TỪ STAGE 1
        KeyEvent key;
        ErrorEvent err;
    } data;
} LogEntry; // ← DÙNG TRONG STATE MACHINE

// ====================== STAGE 3: STATE MACHINE ======================
typedef enum
{
    STATE_POWER_ON,
    STATE_IDLE,
    STATE_READING_SENSOR,
    STATE_LOGGING,
    STATE_ERROR,
    STATE_SLEEP
} SystemState;

typedef enum
{
    ERR_NONE,
    ERR_SENSOR_TIMEOUT,
    ERR_LOG_FULL,
    ERR_LOW_BATTERY
} ErrorCode;

#endif