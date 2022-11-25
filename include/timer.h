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
