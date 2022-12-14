/*
 This file is part of Pong.

    Pong is free software: you can redistribute it and/or modify it under the
 terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or (at your option) any later
 version.

    Pong is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
 Pong. If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>

#include "../include/display.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int width = 640;
    int height = 480;

    if (!display(width, height))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
