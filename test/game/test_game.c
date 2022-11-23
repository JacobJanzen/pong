#include "test_game.h"
#include "../../include/game.h"

#include <assert.h>
#include <stdio.h>

#define ABS(x) x > 0 ? x : -x

#define MAX_DIFF 0.0001
#define CLOSE_TO(expected, actual) ABS(expected - actual) < MAX_DIFF

void before_each() { init(); }

void after_each() { cleanup(); }

void test_game_state() {
    before_each();

    game_state_t *game_state = get_game_state();

    assert(game_state);
    assert(CLOSE_TO(0.5, game_state->l_paddle_pos));

    after_each();
}

void test_game() { test_game_state(); }
