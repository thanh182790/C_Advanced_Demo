#include "registers.h"
#include <stdio.h>

volatile GpioRegUnion_t g_gpioSimReg = {0};

void GpioReg_dumpLayout(void)
{
    printf("===== GPIO REGISTER LAYOUT =====\n");
    printf("sizeof(GpioCtrlBit_t)   = %zu bytes\n", sizeof(GpioCtrlBit_t));
    printf("sizeof(Reg32View_t)     = %zu bytes\n", sizeof(Reg32View_t));
    printf("sizeof(GpioStatusReg_t) = %zu bytes\n", sizeof(GpioStatusReg_t));
    printf("sizeof(GpioReg_t)       = %zu bytes\n", sizeof(GpioReg_t));
    printf("sizeof(GpioRegUnion_t)  = %zu bytes\n", sizeof(GpioRegUnion_t));
    printf("--------------------------------------------------------\n");
    printf("CTRL bitfield layout:\n");
    printf(" EN(1) MODE(3) DIR(1) PULLUP(1) PULLDOWN(1) RESERVED(25)\n");
    printf("--------------------------------------------------------\n");
}
