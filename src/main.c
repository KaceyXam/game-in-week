#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

struct GameState {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    struct GameState app;
    app.window = SDL_CreateWindow("Game Made in a Week", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, 800, 600,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!app.window) {
        printf("Failed to create window: %s", SDL_GetError());
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Error initializing SDL Image: %s\n", IMG_GetError());
        return -1;
    }

    app.renderer = SDL_CreateRenderer(
        app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!app.renderer) {
        printf("Error Initializing Renderer: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect dest;
    SDL_Texture *image = IMG_LoadTexture(app.renderer, "assets/spaceship.png");
    if (!image) {
        printf("IMAGE NOT LOADING: %s\n", IMG_GetError());
        return -1;
    }
    int w;
    int h;
    SDL_QueryTexture(image, NULL, NULL, &w, &h);
    dest.x = 200;
    dest.y = 200;
    dest.w = w;
    dest.h = h;

    bool quit = false;
    SDL_Event ev;

    while (!quit) {
        while (SDL_PollEvent(&ev) != 0) {
            switch (ev.type) {
            case SDL_QUIT:
                return 0;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
        SDL_RenderClear(app.renderer);

        SDL_RenderCopy(app.renderer, image, NULL, &dest);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();

    return 0;
}
