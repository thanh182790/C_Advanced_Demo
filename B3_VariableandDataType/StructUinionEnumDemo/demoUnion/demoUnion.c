#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAYLOAD_SIZE 36 /* Maximum payload size for union view */

/* ===============================================
 * 1. ENUMS: Event types & Log Levels
 * =============================================== */

typedef enum
{
    EVENT_TEMPERATURE = 1,
    EVENT_HUMIDITY = 2,
    LOG_MESSAGE = 100
} Eventtype_t; /* 4 bytes */

typedef enum
{
    LOG_INFO = 0,
    LOG_WARN = 1,
    LOG_ERROR = 2
} Loglevel_t; /* 4 bytes */

/* ===============================================
 * 2. STRUCT DEFINITIONS: Event payloads
 * =============================================== */

typedef struct
{
    float value;        /* Temperature value in °C */
    uint32_t timestamp; /* UNIX timestamp */
} Tempevent_t;          /* 8 bytes */

typedef struct
{
    uint8_t humidity;   /* Percent */
    uint8_t reserved;   /* Reserved for alignment */
    uint16_t batteryMv; /* Battery voltage in mV */
} Humidityevent_t;      /* 4 bytes */

typedef struct
{
    Loglevel_t level;
    char message[32];
} Logevent_t; /* 36 bytes */

/* ===============================================
 * 3. UNION VIEW (Type punning payload)
 * =============================================== */

typedef union
{
    Tempevent_t temp;
    Humidityevent_t hum;
    Logevent_t log;
    uint8_t raw[MAX_PAYLOAD_SIZE];
} Payload_t;

/* ===============================================
 * 4. UART PACKET (Tagged union container)
 * =============================================== */

typedef struct __attribute__((packed))
{
    uint8_t startByte; /* Should always be 0xAA */
    Eventtype_t type;  /* Indicates which payload is valid */
    uint8_t length;    /* Length of payload in bytes */
    Payload_t payload; /* Data union */
    uint8_t checksum;  /* XOR from "type" through payload */
} uart_packet_t;

/* ===============================================
 * 5. UTILITY FUNCTIONS
 * =============================================== */

uint8_t calcChecksum(const void *data, size_t len)
{
    const uint8_t *p = (const uint8_t *)data;
    uint8_t cs = 0;

    for (size_t i = 0; i < len; i++)
    {
        cs ^= p[i];
    }

    return cs;
}

void printRaw(const uint8_t *data, size_t len, const char *label)
{
    printf("  %s: ", label);

    for (size_t i = 0; i < len; i++)
    {
        printf("%02X ", data[i]);
    }

    printf("\n");
}

/* ===============================================
 * 6. DEMO 1: Union view, type punning, sizeof()
 * =============================================== */

void demoUnionBasic(void)
{
    printf("\n=== DEMO 1: UNION VIEW & SIZE ===\n");

    Payload_t p = {0};

    printf("sizeof(Payload_t) = %zu bytes\n", sizeof(p));
    printf("→ Should match Logevent_t (36 bytes)\n");

    /* Assign temperature event */
    p.temp.value = 28.7f;
    p.temp.timestamp = 987654321;

    printf("\nAssigned TempEvent (28.7°C):\n");
    printf("  p.temp.value     = %.1f\n", p.temp.value);
    printf("  p.temp.timestamp = %u\n", p.temp.timestamp);

    printf("\n  [TYPE PUNNING] Raw bytes of temp event:\n");
    printRaw(p.raw, 8, "raw[0..7]");

    /* Overwrite with log event */
    p.log.level = LOG_ERROR;
    strcpy(p.log.message, "Battery low!");

    printf("\nAssigned LogEvent:\n");
    printf("  p.log.message = \"%s\"\n", p.log.message);
    printf("  p.log.level   = %d\n", p.log.level);

    /* Temperature view is now corrupted */
    printf("\n  [UNION OVERLAP] p.temp.value is now corrupted: %.1f\n",
           p.temp.value);

    printRaw(p.raw, 8, "raw[0..7] after log overwrite");
}

/* ===============================================
 * 7. DEMO 2: Build UART packets
 * =============================================== */

void makeTempEvent(uart_packet_t *pkt, float temp, uint32_t ts)
{
    pkt->startByte = 0xAA;
    pkt->type = EVENT_TEMPERATURE;
    pkt->payload.temp.value = temp;
    pkt->payload.temp.timestamp = ts;
    pkt->length = sizeof(Tempevent_t);
    pkt->checksum = calcChecksum(&pkt->type, 2 + pkt->length);
}

void makeHumEvent(uart_packet_t *pkt, uint8_t hum, uint16_t battery)
{
    pkt->startByte = 0xAA;
    pkt->type = EVENT_HUMIDITY;
    pkt->payload.hum.humidity = hum;
    pkt->payload.hum.batteryMv = battery;
    pkt->length = sizeof(Humidityevent_t);
    pkt->checksum = calcChecksum(&pkt->type, 2 + pkt->length);
}

void makeLogEvent(uart_packet_t *pkt, Loglevel_t level, const char *msg)
{
    pkt->startByte = 0xAA;
    pkt->type = LOG_MESSAGE;
    pkt->payload.log.level = level;
    strncpy(pkt->payload.log.message, msg, 31);
    pkt->payload.log.message[31] = '\0';
    pkt->length = sizeof(Logevent_t);
    pkt->checksum = calcChecksum(&pkt->type, 2 + pkt->length);
}

void sendUartPacket(const uart_packet_t *pkt)
{
    const uint8_t *bytes = (const uint8_t *)pkt;
    size_t total = 1 + 4 + 1 + pkt->length + 1;

    printf("\t[UART SEND] %zu bytes:\n\t ", total);

    for (size_t i = 0; i < total; i++)
    {
        printf("%02X ", bytes[i]);
    }

    printf("\n\t  → type=%d, len=%d, checksum=0x%02X\n\n",
           pkt->type, pkt->length, pkt->checksum);
}

void demoUartSendPacket(void)
{
    printf("\n=== DEMO 2: UART SEND ===\n");

    srand(time(NULL));
    uart_packet_t pkt;

    const char *logMsgs[] = {
        "All OK",
        "High temp!",
        "Low humidity",
        "Sensor error!"};

    for (int i = 0; i < 10; i++)
    {
        int r = rand() % 4;

        if (r == 0)
        {
            float temp = 20.0f + (rand() % 200) / 10.0f;
            makeTempEvent(&pkt, temp, 1000000 + i * 1000);
            printf("[Loop %2d] Send Temperature: %.1f°C\n", i + 1, temp);
        }
        else if (r == 1)
        {
            uint8_t hum = 30 + (rand() % 60);
            uint16_t bat = 3000 + (rand() % 1000);
            makeHumEvent(&pkt, hum, bat);
            printf("[Loop %2d] Send Humidity: %d%%, battery: %d mV\n",
                   i + 1, hum, bat);
        }
        else
        {
            Loglevel_t lvl = rand() % 3;
            const char *msg = logMsgs[rand() % 4];
            makeLogEvent(&pkt, lvl, msg);
            printf("[Loop %2d] Send Log [%s]: %s\n",
                   i + 1,
                   (lvl == LOG_INFO) ? "INFO" : (lvl == LOG_WARN) ? "WARN"
                                                                  : "ERROR",
                   msg);
        }

        sendUartPacket(&pkt);
    }
}

int main(void)
{
    printf("\t\t=================== UNION DEMO ===================\n\n");

    demoUnionBasic();
    printf("\t\t\n======================= END ======================\n\n");
    demoUartSendPacket();

    return 0;
}
