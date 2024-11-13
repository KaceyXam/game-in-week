#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window =
        SDL_CreateWindow("Game Made in a Week", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to create window: %s", SDL_GetError());
        return -1;
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
