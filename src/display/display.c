#include "../../include/display.h"
#include <SDL2/SDL.h>
#include <stdio.h>

bool init(SDL_Window **window, SDL_Surface **screen_surface, int width,
          int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height,
                               SDL_WINDOW_SHOWN);
    if (!*window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
        return false;
    }

    *screen_surface = SDL_GetWindowSurface(*window);

    return true;
}

void cleanup(SDL_Window **window) {
    SDL_DestroyWindow(*window);
    *window = NULL;

    SDL_Quit();
}

void main_loop(SDL_Window *window, SDL_Surface *screen_surface) {
    SDL_Event e;

    SDL_FillRect(screen_surface, NULL,
                 SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return;
        }
    }
}

bool display(int width, int height) {
    SDL_Window *window = NULL;
    SDL_Surface *screen_surface = NULL;
    if (!init(&window, &screen_surface, width, height)) {
        fprintf(stderr, "initialization failed\n");
        return false;
    }

    main_loop(window, screen_surface);

    cleanup(&window);

    return true;
}
