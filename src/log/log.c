/*
   This file is part of Pong.

    Pong is free software: you can redistribute it and/or modify it under the
   terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    Pong is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
   Pong. If not, see <https://www.gnu.org/licenses/>.
*/
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
