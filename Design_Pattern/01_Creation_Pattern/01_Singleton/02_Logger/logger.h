#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

int logger_init(const char *log_file, LogLevel level);
void logger_set_level(LogLevel level);
void logger_close(void);

void logger_log(LogLevel level,
                const char *file,
                int line,
                const char *fmt, ...);

#define log_message(level, fmt, ...) \   
    logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif

