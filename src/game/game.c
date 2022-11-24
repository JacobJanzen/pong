#include "../../include/game.h"

#include <stdio.h>
#include <stdlib.h>

#define PADDLE_SPEED 0.015

game_state_t *game_state = NULL;

bool init_game() {
    game_state = malloc(sizeof(game_state_t));
    if (!game_state) {
        perror("failed to create game state");
        return false;
    }

    game_state->l_paddle_pos = 0.5;
    game_state->r_paddle_pos = 0.5;

    return true;
}

game_state_t *get_game_state() {
    if (!game_state)
        return NULL;
    return game_state;
}

void move_paddle(int direction, double *position) {
    if (!position)
        return;

    if (direction < 0) {
        *position -= PADDLE_SPEED;
        if (*position < PADDLE_HEIGHT / 2) {
            *position = PADDLE_HEIGHT / 2;
        }
    } else if (direction > 0) {
        *position += PADDLE_SPEED;
        if (*position > 1 - PADDLE_HEIGHT / 2) {
            *position = 1 - PADDLE_HEIGHT / 2;
        }
    }
}

void update_state(game_update_t *update) {
    if (update && game_state) {
        //        if (update->l_paddle_dir < 0) {
        //            game_state->l_paddle_pos -= PADDLE_SPEED;
        //            if (game_state->l_paddle_pos < PADDLE_HEIGHT / 2) {
        //                game_state->l_paddle_pos = PADDLE_HEIGHT / 2;
        //            }
        //        } else if (update->l_paddle_dir > 0) {
        //            game_state->l_paddle_pos += PADDLE_SPEED;
        //            if (game_state->l_paddle_pos > 1 - PADDLE_HEIGHT / 2) {
        //                game_state->l_paddle_pos = 1 - PADDLE_HEIGHT / 2;
        //            }
        //        }
        move_paddle(update->l_paddle_dir, &game_state->l_paddle_pos);
        move_paddle(update->r_paddle_dir, &game_state->r_paddle_pos);
    }
}

void cleanup_game() {
    if (game_state)
        free(game_state);
    game_state = NULL;
}
