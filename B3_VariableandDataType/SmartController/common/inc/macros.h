#ifndef MACROS_H
#define MACROS_H

#define BIT_SET(REG, BIT)     ((REG) |=  (1U << (BIT)))
#define BIT_CLEAR(REG, BIT)   ((REG) &= ~(1U << (BIT)))
#define BIT_READ(REG, BIT)    (((REG) >> (BIT)) & 1U)
#define BIT_WRITE(REG,BIT,VAL) ((VAL) ? BIT_SET(REG,BIT) : BIT_CLEAR(REG,BIT))

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#endif
