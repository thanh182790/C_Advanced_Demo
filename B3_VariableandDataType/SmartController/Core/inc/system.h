#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"
#include "registers.h"

#ifdef __cplusplus
extern "C"
{
#endif

void System_init(void);
void System_run(void);

#ifdef __cplusplus
}
#endif

#endif
