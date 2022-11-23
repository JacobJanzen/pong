#include <stdio.h>
#include <stdlib.h>

#include "../include/display.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int width = 640;
    int height = 480;

    display(width, height);

    return EXIT_SUCCESS;
}
