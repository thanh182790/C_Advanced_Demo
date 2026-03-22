#include "logger.h"

int main(void)
{
    logger_init("system.log", LOG_DEBUG);

    log_message(LOG_INFO, "System starting...");
    log_message(LOG_DEBUG, "Debug mode enabled");
    log_message(LOG_NOTICE, "System running normally");
    log_message(LOG_WARNING, "Low memory detected");
    log_message(LOG_ERROR, "Failed to connect database");
    log_message(LOG_CRITICAL, "Critical error!");
    log_message(LOG_DEBUG, "Gia tri cua nhiet do la %d %s %f ", 10);

    logger_set_level(LOG_WARNING);

    log_message(LOG_INFO, "This will NOT appear");
    log_message(LOG_ERROR, "This will appear");

    logger_close();
    return 0;
}

