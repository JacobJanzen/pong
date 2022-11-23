#include "../../include/game.h"

#include <stdio.h>
#include <stdlib.h>

game_state_t *game_state = NULL;

bool init() {
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
    // Do nothing for now
}

void cleanup() {
    if (game_state)
        free(game_state);
    game_state = NULL;
}
