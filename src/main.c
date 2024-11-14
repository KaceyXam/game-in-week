#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "headers/common.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

GameState app;

void renderTexture(GameState *app, SDL_Texture *texture, Vector2 *pos) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect dest = {.x = pos->x, .y = pos->y, .w = w, .h = h};

    SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}

void initializeSDL(GameState *app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    app->window = SDL_CreateWindow(
        "Game Made in a Week", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!app->window) {
        printf("Failed to create window: %s", SDL_GetError());
        exit(-1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Error initializing SDL Image: %s\n", IMG_GetError());
        exit(-1);
    }

    app->renderer = SDL_CreateRenderer(
        app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!app->renderer) {
        printf("Error Initializing Renderer: %s\n", SDL_GetError());
        exit(-1);
    }

    app->renderTarget = SDL_CreateTexture(
        app->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        WINDOW_WIDTH, WINDOW_HEIGHT);

    if (initPlant(app)) {
        exit(-1);
    }
}

int main() {
    memset(&app, 0, sizeof(app));

    initializeSDL(&app);

    // player.texture = IMG_LoadTexture(app.renderer, "assets/spaceship.png");
    // if (!player.texture) {
    //     printf("IMAGE NOT LOADING: %s\n", IMG_GetError());
    //     return -1;
    // }

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

        SDL_SetRenderTarget(app.renderer, app.renderTarget);

        SDL_SetRenderDrawColor(app.renderer, 131, 185, 242, 255);
        SDL_RenderClear(app.renderer);

        renderPlant(&app);

        SDL_SetRenderTarget(app.renderer, NULL);

        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(app.renderer);

        int windowWidth, windowHeight;
        SDL_GetWindowSize(app.window, &windowWidth, &windowHeight);

        double scale = MIN((double)windowWidth / WINDOW_WIDTH,
                           (double)windowHeight / WINDOW_HEIGHT);

        SDL_Rect destRect = {(windowWidth - (WINDOW_WIDTH * scale)) * 0.5,
                             (windowHeight - (WINDOW_HEIGHT * scale)) * 0.5,
                             WINDOW_WIDTH * scale, WINDOW_HEIGHT * scale};
        SDL_RenderCopy(app.renderer, app.renderTarget, NULL, &destRect);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();

    return 0;
}
