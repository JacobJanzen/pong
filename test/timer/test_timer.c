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
#include "../../include/timer.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

app_timer_t *g_timer;

static void before_each() {
    g_timer = timer_init();
    assert(g_timer);
}

static void after_each() {
    free(g_timer);
    g_timer = NULL;
}

static void test_initialization() {
    before_each();

    assert(0 == get_ticks(g_timer));

    after_each();
}

static void test_timer_start() {
    before_each();

    timer_start(g_timer);

    SDL_Delay(100);

    assert(0 < get_ticks(g_timer));

    after_each();
}

static void test_timer_stop() {
    before_each();

    timer_start(g_timer);
    timer_stop(g_timer);
    uint8_t time = get_ticks(g_timer);
    SDL_Delay(100);

    assert(time == get_ticks(g_timer));

    after_each();
}

static void test_timer_pause() {
    before_each();

    timer_start(g_timer);
    timer_toggle_pause(g_timer);
    uint8_t time = get_ticks(g_timer);
    SDL_Delay(100);
    assert(time == get_ticks(g_timer));

    timer_toggle_pause(g_timer);
    SDL_Delay(100);
    assert(time < get_ticks(g_timer));

    after_each();
}

void test_timer() {
    test_initialization();
    test_timer_start();
    test_timer_stop();
    test_timer_pause();
}
