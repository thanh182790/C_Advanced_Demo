#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef struct
{
    uint8_t mode;
    uint16_t threshold;
    uint8_t channel;
    uint32_t timestamp;
    float voltage;
    uint64_t id;
} SensorDataAligned_t;

typedef struct __attribute__((packed))
{
    uint8_t mode;
    uint16_t threshold;
    uint8_t channel;
    uint32_t timestamp;
    float voltage;
    uint64_t id;
} SensorDataPacked_t;

typedef struct
{
    uint8_t enable : 1;
    uint8_t mode : 3;
    uint8_t priority : 2;
    uint8_t channel : 3;
    uint8_t reserved : 7;
    uint16_t threshold : 12;
    uint32_t timestamp : 20;
} SensorControlBits_t;

void printStructInfo(const char *name, const void *ptr, size_t size)
{
    printf("\n=== %s ===\n", name);
    printf("  sizeof = %zu bytes\n", size);
    printf("  address = %p\n", ptr);
}

#define PRINT_FIELD(s, type, field)                     \
    printf("    &%-12s = %p  (offset: +%zu)\n", #field, \
           (void *)&((type *)s)->field,                 \
           offsetof(type, field))

void printRawBytes(const void *ptr, size_t size)
{
    const uint8_t *bytes = (const uint8_t *)ptr;
    printf("    raw bytes: ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

void dumpBitfield(const SensorControlBits_t *ctrl)
{
    printf("\n  --- Bitfield Values ---\n");
    printf("    enable    : %d\n", ctrl->enable);
    printf("    mode      : %d\n", ctrl->mode);
    printf("    priority  : %d\n", ctrl->priority);
    printf("    channel   : %d\n", ctrl->channel);
    printf("    reserved  : %d\n", ctrl->reserved);
    printf("    threshold : %d\n", ctrl->threshold);
    printf("    timestamp : %lu\n", (unsigned long)ctrl->timestamp);

    printf("\n  --- Raw Memory Dump (8 bytes) ---\n");
    printRawBytes(ctrl, sizeof(*ctrl));
}

int main(void)
{
    printf("=== DEMO STRUCT: ALIGNED, PACKED, BITFIELD ===\n");

    SensorDataAligned_t dataAligned = {0};
    SensorDataPacked_t dataPacked = {0};
    SensorControlBits_t ctrlBits = {0};

    // === 1. ALIGNED STRUCT ===
    printStructInfo("SensorDataAligned_t", &dataAligned, sizeof(dataAligned));
    PRINT_FIELD(&dataAligned, SensorDataAligned_t, mode);
    PRINT_FIELD(&dataAligned, SensorDataAligned_t, threshold);
    PRINT_FIELD(&dataAligned, SensorDataAligned_t, channel);
    PRINT_FIELD(&dataAligned, SensorDataAligned_t, timestamp);
    PRINT_FIELD(&dataAligned, SensorDataAligned_t, voltage);
    PRINT_FIELD(&dataAligned, SensorDataAligned_t, id);

    // === 2. PACKED STRUCT ===
    printStructInfo("SensorDataPacked_t", &dataPacked, sizeof(dataPacked));
    PRINT_FIELD(&dataPacked, SensorDataPacked_t, mode);
    PRINT_FIELD(&dataPacked, SensorDataPacked_t, threshold);
    PRINT_FIELD(&dataPacked, SensorDataPacked_t, channel);
    PRINT_FIELD(&dataPacked, SensorDataPacked_t, timestamp);
    PRINT_FIELD(&dataPacked, SensorDataPacked_t, voltage);
    PRINT_FIELD(&dataPacked, SensorDataPacked_t, id);

    // === 3. BITFIELD STRUCT ===
    printStructInfo("SensorControlBits_t", &ctrlBits, sizeof(ctrlBits));

    ctrlBits.enable = 1;
    ctrlBits.mode = 5;     // 101b
    ctrlBits.priority = 3; // 11b
    ctrlBits.channel = 7;  // 111b
    ctrlBits.reserved = 0;
    ctrlBits.threshold = 4095;    // 111111111111b (12 bit)
    ctrlBits.timestamp = 1048575; // 20 bit max

    dumpBitfield(&ctrlBits);

    return 0;
}
