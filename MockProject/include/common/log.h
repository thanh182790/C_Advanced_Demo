#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_INFO(fmt, ...)  printf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  printf("[WARN] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERR(fmt, ...)   printf("[ERR ] " fmt "\n", ##__VA_ARGS__)

#endif

