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
#include "test_game.h"
#include "../../include/game.h"

#include <assert.h>
#include <stdio.h>

#define MAX_DIFF 0.0001

static double abs_double(double x) { return x > 0 ? x : -x; }

static bool close_to(double expected, double actual) {
    return abs_double(expected - actual) < MAX_DIFF;
}

static void before_each() { init_game(); }

static void after_each() { cleanup_game(); }

static void test_game_state() {
    before_each();

    game_state_t *game_state = get_game_state();

    assert(game_state);
    assert(close_to(0.5, game_state->l_paddle_pos));

    after_each();
}

static void test_move_paddle() {
    before_each();

    game_state_t *game_state = get_game_state();
    assert(game_state);
    double before_move = 0.5;

    game_update_t update = {-1, -1};
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);
    double after_move_l = game_state->l_paddle_pos;
    double after_move_r = game_state->r_paddle_pos;
    assert(before_move > after_move_l);
    assert(before_move > after_move_r);

    update.l_paddle_dir = 1;
    update.r_paddle_dir = 1;
    update_state(&update);
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);
    after_move_l = game_state->l_paddle_pos;
    after_move_r = game_state->r_paddle_pos;
    assert(before_move < after_move_l);
    assert(before_move < after_move_r);

    after_each();
}

static void test_stop_paddle_at_border() {
    before_each();

    game_state_t *game_state = get_game_state();
    assert(game_state);
    game_state->l_paddle_pos = PADDLE_HEIGHT / 2;
    game_state->r_paddle_pos = PADDLE_HEIGHT / 2;
    game_update_t update = {-1, -1};
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);

    assert(close_to(PADDLE_HEIGHT / 2, game_state->l_paddle_pos));
    assert(close_to(PADDLE_HEIGHT / 2, game_state->r_paddle_pos));

    game_state->l_paddle_pos = 1 - PADDLE_HEIGHT / 2;
    game_state->r_paddle_pos = 1 - PADDLE_HEIGHT / 2;
    update.l_paddle_dir = 1;
    update.r_paddle_dir = 1;
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);
    assert(close_to(1 - PADDLE_HEIGHT / 2, game_state->l_paddle_pos));
    assert(close_to(1 - PADDLE_HEIGHT / 2, game_state->r_paddle_pos));

    after_each();
}

void test_game() {
    test_move_paddle();
    test_stop_paddle_at_border();
    test_game_state();
}
