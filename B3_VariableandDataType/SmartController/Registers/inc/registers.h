#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include "macros.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* --------------------------
 * Bitfield cho thanh ghi điều khiển MODE (packed)
 * -------------------------- */
#pragma pack(push, 1)
typedef struct
{
    volatile uint32_t EN : 1;          // bit0 - Enable pin
    volatile uint32_t MODE : 3;        // bit[3:1] - Pin mode (GPIO, AF, ANALOG...)
    volatile uint32_t DIR : 1;         // bit4 - Direction (0=Input,1=Output)
    volatile uint32_t PULLUP_EN : 1;   // bit5 - Pull-up enable
    volatile uint32_t PULLDOWN_EN : 1; // bit6 - Pull-down enable
    volatile uint32_t RESERVED : 25;   // bit[31:7] - reserved
} GpioCtrlBit_t;
#pragma pack(pop)

/* --------------------------
 * Register View cho 32-bit register
 * -------------------------- */
typedef union
{
    uint32_t all;
    struct
    {
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    } bytes;
    struct
    {
        uint16_t low;
        uint16_t high;
    } half; // view halfword
} Reg32View_t;

/* --------------------------
 * Thanh ghi trạng thái GPIO (để demo padding)
 * -------------------------- */
#pragma pack(push, 1)
typedef struct
{
    volatile uint16_t readyFlag; // 2 bytes
    volatile uint8_t errorCode;  // 1 byte
    // Padding: thêm 1 byte ở đây nếu không pack (để canh 4-byte boundary)
    volatile uint32_t eventCount; // 4 bytes
} GpioStatusReg_t;
#pragma pack(pop)

/* --------------------------
 * Mô phỏng khối thanh ghi GPIO
 * -------------------------- */
typedef struct
{
    volatile Reg32View_t DATA;       // 0x00
    volatile Reg32View_t DIR;        // 0x04
    volatile GpioCtrlBit_t CTRL;     // 0x08 (bitfield)
    volatile Reg32View_t PULL;       // 0x0C
    volatile Reg32View_t INTERRUPT;  // 0x10
    volatile GpioStatusReg_t STATUS; // 0x14 (để show padding)
} GpioReg_t;

/* --------------------------
 * Union ánh xạ nhiều cách truy cập GPIO
 * -------------------------- */
typedef union
{
    GpioReg_t reg;                            // access theo tên
    uint8_t raw[sizeof(GpioReg_t)];           // access theo mảng byte
    uint32_t wordView[sizeof(GpioReg_t) / 4]; // access theo word
} GpioRegUnion_t;

/* --------------------------
 * Biến toàn cục mô phỏng vùng thanh ghi ngoại vi
 * -------------------------- */
extern volatile GpioRegUnion_t g_gpioSimReg;

/* --------------------------
 * Dump size struct
 * -------------------------- */
void GpioReg_dumpLayout(void);

#ifdef __cplusplus
}
#endif

#endif // REGISTERS_H
