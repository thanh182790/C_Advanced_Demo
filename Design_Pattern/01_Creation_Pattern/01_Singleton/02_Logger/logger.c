#include "logger.h"
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    FILE *fp;
    LogLevel level;
    int initialized;
} Logger;

static Logger logger;

static const char *level_str[] = {
    "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
    "WARNING", "NOTICE", "INFO", "DEBUG"
};

static const char *get_timestamp(char *buf, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buf, size, "%Y-%m-%d %H:%M:%S", tm_info);
    return buf;
}

int logger_init(const char *log_file, LogLevel level)
{
    if (logger.initialized)
        return 0;

    logger.level = level;

    if (log_file) {
        logger.fp = fopen(log_file, "a");
        if (!logger.fp) {
            perror("fopen");
            return -1;
        }
    }

    logger.initialized = 1;
    return 0;
}

void logger_set_level(LogLevel level)
{
    logger.level = level;
}

void logger_close(void)
{
    if (logger.fp) {
        fclose(logger.fp);
        logger.fp = NULL;
    }
    logger.initialized = 0;
}

void logger_log(LogLevel level,
                const char *file,
                int line,
                const char *fmt, ...)
{
    if (!logger.initialized || level > logger.level)
        return;

    char time_buf[32];
    char msg_buf[512];

    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, args);
    va_end(args);

    char final_buf[1024];
    snprintf(final_buf, sizeof(final_buf),
             "[%s] [%s] [%s:%d] - %s\n",
             get_timestamp(time_buf, sizeof(time_buf)),
             level_str[level], file, line, msg_buf);

    FILE *out = (level <= LOG_ERROR) ? stderr : stdout;
    fputs(final_buf, out);
    fflush(out);

    if (logger.fp) {
        fputs(final_buf, logger.fp);
        fflush(logger.fp);
    }
}

