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
#include "../../include/game.h"
#include "../../include/log.h"

#include <stdio.h>
#include <stdlib.h>

#define PADDLE_SPEED 0.015

game_state_t *game_state = NULL;

bool init_game() {
    game_state = malloc(sizeof(game_state_t));
    if (!game_state) {
        log_message(LOG_ERROR, "failed to create game state");
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
        move_paddle(update->l_paddle_dir, &game_state->l_paddle_pos);
        move_paddle(update->r_paddle_dir, &game_state->r_paddle_pos);
    }
}

void cleanup_game() {
    if (game_state)
        free(game_state);
    game_state = NULL;
}
