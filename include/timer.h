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
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct TIMER app_timer_t;

app_timer_t *timer_init();

void timer_start(app_timer_t *timer);
void timer_stop(app_timer_t *timer);
void timer_toggle_pause(app_timer_t *timer);

uint32_t get_ticks(app_timer_t *timer);

#endif
