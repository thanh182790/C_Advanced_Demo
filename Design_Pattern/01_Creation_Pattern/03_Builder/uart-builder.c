#include <stdio.h>
#include "uart-builder.h"

/* ================= Internal validation helpers ================= */

static int is_valid_baudrate(uint32_t baudRate) {
    return (baudRate >= 1200 && baudRate <= 115200);
}

/* ================= Builder methods ================= */

static UART_Builder* setBaudRate(UART_Builder* builder, uint32_t baudRate) {
    if (!is_valid_baudrate(baudRate)) {
        printf("[UART Builder] Invalid baud rate\n");
        return builder;
    }

    builder->config.baudRate = baudRate;
    return builder;
}

static UART_Builder* setParity(UART_Builder* builder, UART_Parity_e parity) {
    if (parity > UART_PARITY_EVEN) {
        printf("[UART Builder] Invalid parity\n");
        return builder;
    }

    builder->config.parity = parity;
    return builder;
}

static UART_Builder* setStopBits(UART_Builder* builder, uint8_t stopBits) {
    if (stopBits != 1 && stopBits != 2) {
        printf("[UART Builder] Invalid stop bits\n");
        return builder;
    }

    builder->config.stopBits = stopBits;
    return builder;
}

static UART_Builder* setDataBits(UART_Builder* builder, uint8_t dataBits) {
    if (dataBits != 8 && dataBits != 9) {
        printf("[UART Builder] Invalid data bits\n");
        return builder;
    }

    builder->config.dataBits = dataBits;
    return builder;
}

static UART_Config_t build(UART_Builder* builder) {
    return builder->config;
}

/* ================= Builder Init ================= */

UART_Builder UART_Builder_Init(void) {
    UART_Builder builder;

    /* Default configuration */
    builder.config.baudRate = BAUDRATE_9600;
    builder.config.parity   = UART_PARITY_NONE;
    builder.config.stopBits = 1;
    builder.config.dataBits = 8;

    /* Bind methods */
    builder.setBaudRate = setBaudRate;
    builder.setParity   = setParity;
    builder.setStopBits = setStopBits;
    builder.setDataBits = setDataBits;
    builder.build       = build;

    return builder;
}

