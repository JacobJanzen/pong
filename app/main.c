#include <stdio.h>
#include <stdlib.h>

#include "../include/display.h"
#include "../include/game.h"
#include "../include/log.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int width = 640;
    int height = 480;

    if (!init_game())
        return EXIT_FAILURE;
    log_message(LOG_INFO, "Successfully initialized game");
    if (!display(width, height))
        return EXIT_FAILURE;
    cleanup_game();
    log_message(LOG_INFO, "Finished cleanup");

    return EXIT_SUCCESS;
}
