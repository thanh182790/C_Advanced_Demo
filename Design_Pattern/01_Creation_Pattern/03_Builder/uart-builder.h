#ifndef UART_BUILDER_H
#define UART_BUILDER_H

#include <stdint.h>

/* ================= UART Constants ================= */

#define BAUDRATE_9600     9600
#define BAUDRATE_115200   115200

/* ================= UART Types ================= */

typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_ODD,
    UART_PARITY_EVEN
} UART_Parity_e;

typedef struct {
    uint32_t baudRate;
    UART_Parity_e parity;
    uint8_t stopBits;   /* 1 or 2 */
    uint8_t dataBits;   /* 8 or 9 */
} UART_Config_t;

/* ================= Builder ================= */

typedef struct UART_Builder UART_Builder;

struct UART_Builder {
    UART_Config_t config;

    UART_Builder* (*setBaudRate)(UART_Builder*, uint32_t);
    UART_Builder* (*setParity)(UART_Builder*, UART_Parity_e);
    UART_Builder* (*setStopBits)(UART_Builder*, uint8_t);
    UART_Builder* (*setDataBits)(UART_Builder*, uint8_t);

    UART_Config_t (*build)(UART_Builder*);
};

/* ================= API ================= */

UART_Builder UART_Builder_Init(void);

#endif // UART_BUILDER_H

