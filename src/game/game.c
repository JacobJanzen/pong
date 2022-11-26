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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PADDLE_SPEED 0.015
#define MIN_BALL_X_VELOCITY 0.005

game_state_t *game_state = NULL;

static double rand_double(double low, double high) {
    return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
}

static bool hit_paddle(double x_pos, double y_pos) {
    if ((x_pos > 0.5 &&
         (y_pos + BALL_RADIUS < game_state->r_paddle_pos - PADDLE_HEIGHT / 2 ||
          y_pos - BALL_RADIUS >
              game_state->r_paddle_pos + PADDLE_HEIGHT / 2)) ||
        (x_pos < 0.5 &&
         (y_pos + BALL_RADIUS < game_state->l_paddle_pos - PADDLE_HEIGHT / 2 ||
          y_pos - BALL_RADIUS > game_state->l_paddle_pos + PADDLE_HEIGHT / 2)))
        return false;
    return (x_pos - BALL_RADIUS < SPACE_BEHIND_PADDLE + PADDLE_WIDTH &&
            x_pos - BALL_RADIUS > SPACE_BEHIND_PADDLE) ||
           (x_pos + BALL_RADIUS > 1 - SPACE_BEHIND_PADDLE - PADDLE_WIDTH &&
            x_pos + BALL_RADIUS < 1 - SPACE_BEHIND_PADDLE);
}

static void spawn_ball() {
    int x_dir = (rand() & 1) == 0 ? -1 : 1;
    int y_dir = (rand() & 1) == 0 ? -1 : 1;
    game_state->ball_x_pos = 0.5;
    game_state->ball_y_pos = 0.5;
    game_state->ball_x_velocity = MIN_BALL_X_VELOCITY * x_dir;
    game_state->ball_y_velocity =
        rand_double(0, MIN_BALL_X_VELOCITY * 2) * y_dir;
}

game_state_t *init_game() {
    srand(time(NULL));
    game_state = malloc(sizeof(game_state_t));
    if (!game_state) {
        log_message(LOG_ERROR, "failed to create game state");
        return NULL;
    }

    game_state->l_paddle_pos = 0.5;
    game_state->r_paddle_pos = 0.5;
    spawn_ball();

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

    double new_y_pos = game_state->ball_y_pos + game_state->ball_y_velocity;
    if (new_y_pos - BALL_RADIUS <= 0 || new_y_pos + BALL_RADIUS >= 1) {
        game_state->ball_y_velocity = -game_state->ball_y_velocity;
        game_state->ball_y_pos += game_state->ball_y_velocity;
    } else {
        game_state->ball_y_pos = new_y_pos;
    }

    double new_x_pos = game_state->ball_x_pos + game_state->ball_x_velocity;
    if (new_x_pos - BALL_RADIUS <= 0 || new_x_pos + BALL_RADIUS >= 1) {
        spawn_ball();
    } else if (hit_paddle(new_x_pos, new_y_pos)) {
        game_state->ball_x_velocity = -game_state->ball_x_velocity;
        game_state->ball_x_pos += game_state->ball_x_velocity;
    } else {
        game_state->ball_x_pos = new_x_pos;
    }
}

void cleanup_game() {
    if (game_state)
        free(game_state);
    game_state = NULL;
}
