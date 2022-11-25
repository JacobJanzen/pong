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
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define DISPLAY_PADDLE_HEIGHT(canvas_height) canvas_height *PADDLE_HEIGHT
#define DISPLAY_PADDLE_WIDTH(canvas_width) canvas_width / 40

#define PADDLE_X_POS(canvas_width) canvas_width / 30

#define NUM_DOTS 30
#define DOT_DIAMETER(canvas_height) canvas_height / NUM_DOTS

char g_error_string[256];

void init(SDL_Window **window, SDL_Renderer **renderer, int width, int height) {
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

    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        sprintf(g_error_string,
                "Renderer could not be created! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_FATAL, g_error_string);
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

bool main_loop(SDL_Window *window, SDL_Renderer *renderer, int width,
               int height) {
    SDL_Event e;

    SDL_UpdateWindowSurface(window);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (!keys) {
        sprintf(g_error_string, "Could not get keys! SDL Error: %s\n",
                SDL_GetError());
        log_message(LOG_ERROR, g_error_string);
        return false;
    }

    game_update_t update = {0, 0};

    log_message(LOG_INFO, "Starting main game loop");
    while (true) {
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
    }

    return true;
}

bool display(int width, int height) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    init(&window, &renderer, width, height);
    log_message(LOG_INFO, "Successfully initialized display");

    if (!main_loop(window, renderer, width, height)) {
        return false;
    }

    log_message(LOG_INFO, "Beginning cleanup");
    cleanup(&window);

    return true;
}
