#include "../../include/timer.h"
#include "../../include/log.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

struct TIMER {
    uint32_t start_ticks;
    uint32_t paused_ticks;

    bool paused;
    bool started;
};

app_timer_t *timer_init() {
    app_timer_t *timer = malloc(sizeof(app_timer_t));
    if (timer == NULL) {
        log_message(LOG_ERROR, "failed to allocate memory for timer");
        return NULL;
    }

    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->paused = false;
    timer->started = false;

    return timer;
}

void timer_start(app_timer_t *timer) {
    if (!timer) {
        log_message(LOG_WARNING, "NULL timer provided");
        return;
    }

    timer->started = true;
    timer->paused = false;
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
}

void timer_stop(app_timer_t *timer) {
    if (!timer) {
        log_message(LOG_WARNING, "NULL timer provided");
        return;
    }

    timer->started = false;
    timer->paused = false;
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
}

void timer_toggle_pause(app_timer_t *timer) {
    if (!timer) {
        log_message(LOG_WARNING, "NULL timer provided");
        return;
    }

    if (timer->started) {
        if (!timer->paused) {
            timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
            timer->start_ticks = 0;
        } else {
            timer->start_ticks = SDL_GetTicks() - timer->paused_ticks;
            timer->paused_ticks = 0;
        }
        timer->paused = !timer->paused;
    }
}

uint32_t get_ticks(app_timer_t *timer) {
    if (timer->started) {
        if (timer->paused) {
            return timer->paused_ticks;
        }
        return SDL_GetTicks() - timer->start_ticks;
    }

    return 0;
}
