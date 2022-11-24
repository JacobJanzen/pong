#include "../../include/display.h"
#include "../../include/game.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define DISPLAY_PADDLE_HEIGHT(canvas_height) canvas_height *PADDLE_HEIGHT
#define DISPLAY_PADDLE_WIDTH(canvas_width) canvas_width / 40

#define PADDLE_X_POS(canvas_width) canvas_width / 30

#define NUM_DOTS 30
#define DOT_DIAMETER(canvas_height) canvas_height / NUM_DOTS

bool init(SDL_Window **window, SDL_Renderer **renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",
                SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height,
                               SDL_WINDOW_SHOWN);
    if (!*window) {
        fprintf(stderr, "Window could not be created! SDL Error: %s\n",
                SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s\n",
                SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);

    return true;
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

void main_loop(SDL_Window *window, SDL_Renderer *renderer, int width,
               int height) {
    SDL_Event e;

    SDL_UpdateWindowSurface(window);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (!keys) {
        fprintf(stderr, "Could not get keys! SDL_Error: %s\n", SDL_GetError());
    }

    game_update_t update = {0, 0};

    while (true) {
        SDL_PumpEvents();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return;
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                move_paddles(keys, &update);
            }
        }

        update_state(&update);
        game_state_t *game_state = get_game_state();
        if (!game_state) {
            perror("failed to get game state");
            return;
        }

        draw_assets(window, renderer, width, height, game_state);
    }
}

bool display(int width, int height) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!init(&window, &renderer, width, height)) {
        perror("initialization failed");
        return false;
    }

    main_loop(window, renderer, width, height);

    cleanup(&window);

    return true;
}
