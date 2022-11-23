#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define PADDLE_HEIGHT 1.0 / 6.0

typedef struct GAME_STATE {
    double l_paddle_pos;
} game_state_t;

typedef struct GAME_UPDATE {
    int l_paddle_dir;
} game_update_t;

bool init_game();
game_state_t *get_game_state();
void update_state(game_update_t *update);
void cleanup_game();

#endif
