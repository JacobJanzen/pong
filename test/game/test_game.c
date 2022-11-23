#include "test_game.h"
#include "../../include/game.h"

#include <assert.h>
#include <stdio.h>

#define MAX_DIFF 0.0001

double abs_double(double x) { return x > 0 ? x : -x; }

bool close_to(double expected, double actual) {
    return abs_double(expected - actual) < MAX_DIFF;
}

void before_each() { init_game(); }

void after_each() { cleanup_game(); }

void test_game_state() {
    before_each();

    game_state_t *game_state = get_game_state();

    assert(game_state);
    assert(close_to(0.5, game_state->l_paddle_pos));

    after_each();
}

void test_move_paddle() {
    before_each();

    game_state_t *game_state = get_game_state();
    assert(game_state);
    double before_move = game_state->l_paddle_pos;

    game_update_t update = {-1};
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);
    double after_move = game_state->l_paddle_pos;
    assert(before_move > after_move);

    update.l_paddle_dir = 1;
    update_state(&update);
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);
    after_move = game_state->l_paddle_pos;
    assert(before_move < after_move);

    after_each();
}

void test_stop_paddle_at_border() {
    before_each();

    game_state_t *game_state = get_game_state();
    assert(game_state);
    game_state->l_paddle_pos = PADDLE_HEIGHT / 2;
    game_update_t update = {-1};
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);

    assert(close_to(PADDLE_HEIGHT / 2, game_state->l_paddle_pos));

    game_state->l_paddle_pos = 1 - PADDLE_HEIGHT / 2;
    update.l_paddle_dir = 1;
    update_state(&update);
    game_state = get_game_state();
    assert(game_state);
    assert(close_to(1 - PADDLE_HEIGHT / 2, game_state->l_paddle_pos));

    after_each();
}

void test_game() {
    test_move_paddle();
    test_stop_paddle_at_border();
    test_game_state();
}
