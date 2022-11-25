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

char g_error_string[256];

void init(SDL_Window **window, SDL_Renderer **renderer,
          app_timer_t **frame_timer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sprintf(g_error_string, "SDL could not initialize! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
    }

    *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height,
                               SDL_WINDOW_SHOWN);
    if (!*window) {
        sprintf(g_error_string, "Window could not be created! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        sprintf(g_error_string,
                "Renderer could not be created! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
    }

    *frame_timer = timer_init();
    if (!frame_timer) {
        log_message(LOG_FATAL, "failed to initialize frame timer");
    }

    SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);
}

void cleanup(SDL_Window **window) {
    SDL_DestroyWindow(*window);
    *window = NULL;

    SDL_Quit();
}

void render_line(SDL_Renderer *renderer, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < NUM_DOTS / 2; i++) {
        SDL_Rect dot = {
            width / 2 - DOT_DIAMETER(height) / 2,
            i * 2 * DOT_DIAMETER(height),
            DOT_DIAMETER(height),
            DOT_DIAMETER(height),
        };
        SDL_RenderFillRect(renderer, &dot);
    }
}

void render_paddle(SDL_Renderer *renderer, int width, int height, bool isLeft,
                   double pos) {

    int xPos = isLeft
                   ? PADDLE_X_POS(width)
                   : width - PADDLE_X_POS(width) - DISPLAY_PADDLE_WIDTH(width);
    int yPos = (int)(height * pos) - height / 12;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect lPaddle = {
        xPos,
        yPos,
        DISPLAY_PADDLE_WIDTH(width),
        DISPLAY_PADDLE_HEIGHT(height),
    };
    SDL_RenderFillRect(renderer, &lPaddle);
}

void move_paddles(const Uint8 *keys, game_update_t *update) {
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

void draw_assets(SDL_Window *window, SDL_Renderer *renderer, int width,
                 int height, game_state_t *game_state) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    render_line(renderer, width, height);
    render_paddle(renderer, width, height, true, game_state->l_paddle_pos);
    render_paddle(renderer, width, height, false, game_state->r_paddle_pos);

    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}

bool main_loop(SDL_Window *window, SDL_Renderer *renderer,
               app_timer_t *frame_timer, int width, int height) {
    SDL_Event e;
    game_update_t update = {0, 0};

    SDL_UpdateWindowSurface(window);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (!keys) {
        sprintf(g_error_string, "Could not get keys! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_ERROR, g_error_string);
        return false;
    }

    log_message(LOG_INFO, "Starting main game loop");
    while (true) {
        timer_start(frame_timer);

        SDL_PumpEvents();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return true;
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                move_paddles(keys, &update);
            }
        }

        update_state(&update);
        game_state_t *game_state = get_game_state();
        if (!game_state) {
            log_message(LOG_ERROR, "Failed to get game state");
            return false;
        }

        draw_assets(window, renderer, width, height, game_state);

        timer_stop(frame_timer);
        uint32_t frame_ticks = get_ticks(frame_timer);
        if (frame_ticks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frame_ticks);
        }
    }

    return true;
}

bool display(int width, int height) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    app_timer_t *frame_timer = NULL;

    init(&window, &renderer, &frame_timer, width, height);
    log_message(LOG_INFO, "Successfully initialized display");

    if (!main_loop(window, renderer, frame_timer, width, height)) {
        return false;
    }

    log_message(LOG_INFO, "Beginning cleanup");
    cleanup(&window);

    return true;
}
