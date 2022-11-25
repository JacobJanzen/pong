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
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define PADDLE_HEIGHT 1.0 / 6.0

typedef struct GAME_STATE {
    double l_paddle_pos;
    double r_paddle_pos;
} game_state_t;

typedef struct GAME_UPDATE {
    int l_paddle_dir;
    int r_paddle_dir;
} game_update_t;

bool init_game();
game_state_t *get_game_state();
void update_state(game_update_t *update);
void cleanup_game();

#endif
