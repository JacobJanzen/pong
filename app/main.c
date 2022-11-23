#include <stdio.h>
#include <stdlib.h>

#include "../include/display.h"
#include "../include/game.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int width = 640;
    int height = 480;

    if (!init_game())
        return EXIT_FAILURE;
    if (!display(width, height))
        return EXIT_FAILURE;
    cleanup_game();

    return EXIT_SUCCESS;
}
