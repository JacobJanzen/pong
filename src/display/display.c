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
#include "../../include/display.h"
#include "../../include/game.h"
#include "../../include/log.h"
#include "../../include/timer.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define TICKS_PER_FRAME 1000 / 60

#define DISPLAY_PADDLE_HEIGHT(canvas_height) canvas_height *PADDLE_HEIGHT
#define DISPLAY_PADDLE_WIDTH(canvas_width) canvas_width / 40

#define PADDLE_X_POS(canvas_width) canvas_width / 30

#define NUM_DOTS 30
#define DOT_DIAMETER(canvas_height) canvas_height / NUM_DOTS

#define DISPLAY_BALL_RADIUS(canvas_width) canvas_width *BALL_RADIUS

char g_error_string[256];

typedef struct GAME {
    SDL_Window *window;
    SDL_Renderer *renderer;
    app_timer_t *frame_timer;
    game_state_t *game_state;
    int width;
    int height;
} game_t;

static void init(game_t *game) {
    log_message(LOG_INFO, "Initializing video...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sprintf(g_error_string, "SDL could not initialize! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
    }
    log_message(LOG_INFO, "Successfully initialized video");

    log_message(LOG_INFO, "Initializing window...");
    game->window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, game->width,
                                    game->height, SDL_WINDOW_SHOWN);
    if (!game->window) {
        sprintf(g_error_string, "Window could not be created! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
    }
    log_message(LOG_INFO, "Successfully initialized window");

    log_message(LOG_INFO, "Initializing renderer...");
    game->renderer =
        SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        sprintf(g_error_string,
                "Renderer could not be created! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
    }
    log_message(LOG_INFO, "Successfully initialized renderer");

    log_message(LOG_INFO, "Initializing timer...");
    game->frame_timer = timer_init();
    if (!game->frame_timer) {
        log_message(LOG_FATAL, "failed to initialize frame timer");
    }
    log_message(LOG_INFO, "Successfully initialized timer");

    log_message(LOG_INFO, "Initializing game state...");
    game->game_state = init_game();
    if (!game->game_state) {
        log_message(LOG_FATAL, "failed to initialize game state");
    }
    log_message(LOG_INFO, "Successfully initialized game state");

    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xFF);
}

static void cleanup(game_t *game) {
    SDL_DestroyWindow(game->window);
    game->window = NULL;
    cleanup_game();

    SDL_Quit();
}

static void render_line(game_t *game) {
    SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < NUM_DOTS / 2; i++) {
        SDL_Rect dot = {
            game->width / 2 - DOT_DIAMETER(game->height) / 2,
            i * 2 * DOT_DIAMETER(game->height),
            DOT_DIAMETER(game->height),
            DOT_DIAMETER(game->height),
        };
        SDL_RenderFillRect(game->renderer, &dot);
    }
}

static void render_paddle(game_t *game, bool is_left, double pos) {

    int xPos = is_left ? PADDLE_X_POS(game->width)
                       : game->width - PADDLE_X_POS(game->width) -
                             DISPLAY_PADDLE_WIDTH(game->width);
    int yPos = (int)(game->height * pos) - game->height / 12;

    SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect paddle = {
        xPos,
        yPos,
        DISPLAY_PADDLE_WIDTH(game->width),
        DISPLAY_PADDLE_HEIGHT(game->height),
    };
    SDL_RenderFillRect(game->renderer, &paddle);
}

static void render_ball(game_t *game, double x_pos, double y_pos) {
    int x_pos_disp = game->width * x_pos;
    int y_pos_disp = game->height * y_pos;
    SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect ball = {
        x_pos_disp - DISPLAY_BALL_RADIUS(game->width),
        y_pos_disp - DISPLAY_BALL_RADIUS(game->width),
        DISPLAY_BALL_RADIUS(game->width) * 2,
        DISPLAY_BALL_RADIUS(game->width) * 2,
    };
    SDL_RenderFillRect(game->renderer, &ball);
}

static void move_paddles(const Uint8 *keys, game_update_t *update) {
    update->l_paddle_dir = 0;
    update->r_paddle_dir = 0;
    if (keys[SDL_SCANCODE_W]) {
        --update->l_paddle_dir;
    }
    if (keys[SDL_SCANCODE_S]) {
        ++update->l_paddle_dir;
    }
    if (keys[SDL_SCANCODE_UP]) {
        --update->r_paddle_dir;
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        ++update->r_paddle_dir;
    }
}

static void draw_assets(game_t *game) {
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(game->renderer);

    render_line(game);
    render_paddle(game, true, game->game_state->l_paddle_pos);
    render_paddle(game, false, game->game_state->r_paddle_pos);
    render_ball(game, game->game_state->ball_x_pos,
                game->game_state->ball_y_pos);

    SDL_RenderPresent(game->renderer);
    SDL_UpdateWindowSurface(game->window);
}

static bool main_loop(game_t *game) {
    SDL_Event e;
    game_update_t update = {0, 0};

    SDL_UpdateWindowSurface(game->window);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (!keys) {
        sprintf(g_error_string, "Could not get keys! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_ERROR, g_error_string);
        return false;
    }

    log_message(LOG_INFO, "Starting main game loop");
    while (true) {
        timer_start(game->frame_timer);

        SDL_PumpEvents();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return true;
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                move_paddles(keys, &update);
            }
        }

        update_state(&update);

        draw_assets(game);

        timer_stop(game->frame_timer);
        uint32_t frame_ticks = get_ticks(game->frame_timer);
        if (frame_ticks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frame_ticks);
        }
    }

    return true;
}

bool display(int width, int height) {
    game_t game = {
        .height = height,
        .width = width,
    };

    log_message(LOG_INFO, "Initializing game...");
    init(&game);
    log_message(LOG_INFO, "Successfully initialized game");

    if (!main_loop(&game)) {
        return false;
    }

    log_message(LOG_INFO, "Cleaning up game...");
    cleanup(&game);
    log_message(LOG_INFO, "Successfully cleaned up game");

    return true;
}
