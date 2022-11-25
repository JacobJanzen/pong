#include "../../include/log.h"

#include <stdio.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define RESET "\x1B[0m"

void log_message(log_level_t level, char *message) {
    switch (level) {
    case LOG_INFO:
        printf("{ INFO: %s }\n", message);
        break;
    case LOG_WARNING:
        fprintf(stderr, YEL "{ WARNING: %s }\n" RESET, message);
        break;
    case LOG_ERROR:
        fprintf(stderr, RED "{ ERROR: %s }\n" RESET, message);
        break;
    case LOG_FATAL:
        fprintf(stderr, RED "{ ERROR: %s }\n" RESET, message);
        exit(EXIT_FAILURE);
    }
}
