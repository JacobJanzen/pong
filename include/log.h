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
