#include "../../include/game.h"

#include <stdio.h>
#include <stdlib.h>

#define VELOCITY 0.015

game_state_t *game_state = NULL;

bool init_game() {
    game_state = malloc(sizeof(game_state_t));
    if (!game_state) {
        perror("failed to create game state");
        return false;
    }

    game_state->l_paddle_pos = 0.5;

    return true;
}

game_state_t *get_game_state() {
    if (!game_state)
        return NULL;
    return game_state;
}

void update_state(game_update_t *update) {
    if (update && game_state) {
        if (update->l_paddle_dir < 0) {
            game_state->l_paddle_pos -= VELOCITY;
            if (game_state->l_paddle_pos < PADDLE_HEIGHT / 2) {
                game_state->l_paddle_pos = PADDLE_HEIGHT / 2;
            }
        } else if (update->l_paddle_dir > 0) {
            game_state->l_paddle_pos += VELOCITY;
            if (game_state->l_paddle_pos > 1 - PADDLE_HEIGHT / 2) {
                game_state->l_paddle_pos = 1 - PADDLE_HEIGHT / 2;
            }
        }
    }
}

void cleanup_game() {
    if (game_state)
        free(game_state);
    game_state = NULL;
}
