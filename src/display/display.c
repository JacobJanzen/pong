#include "../../include/display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

#define PADDLE_HEIGHT(canvas_height) canvas_height / 6
#define PADDLE_WIDTH(canvas_width) canvas_width / 40

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

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
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

    int xPos = isLeft ? PADDLE_X_POS(width)
                      : width - PADDLE_X_POS(width) - PADDLE_WIDTH(width);
    int yPos = (int)(height * pos) - height / 12;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect lPaddle = {
        xPos,
        yPos,
        PADDLE_WIDTH(width),
        PADDLE_HEIGHT(height),
    };
    SDL_RenderFillRect(renderer, &lPaddle);
}

void main_loop(SDL_Window *window, SDL_Renderer *renderer, int width,
               int height) {
    (void)renderer;
    SDL_Event e;

    SDL_UpdateWindowSurface(window);

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        render_line(renderer, width, height);
        render_paddle(renderer, width, height, true, 0.5);
        render_paddle(renderer, width, height, false, 0.5);

        SDL_RenderPresent(renderer);
    }
}

bool display(int width, int height) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!init(&window, &renderer, width, height)) {
        fprintf(stderr, "initialization failed\n");
        return false;
    }

    main_loop(window, renderer, width, height);

    cleanup(&window);

    return true;
}
