#ifndef LOG_H
#define LOG_H

typedef enum LOG_LEVEL {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
} log_level_t;

void log_message(log_level_t level, char *message);

#endif
