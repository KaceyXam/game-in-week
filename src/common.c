#include "headers/common.h"
#include <SDL2/SDL_image.h>

#define PLANT_WIDTH 667
#define PLANT_HEIGHT 1500

int initPlant(GameState *app) {
    app->plant.water = 1.0;
    app->plant.fertilizer = 1.0;
    app->plant.growthProgress = 0;
    app->plant.growth = 0;

    app->plant.texture = IMG_LoadTexture(app->renderer, "assets/plants.png");
    if (!app->plant.texture) {
        printf("Failed to load plant texture: %s\n", IMG_GetError());
        return -1;
    }

    return 0;
}

void renderPlant(GameState *app) {
    SDL_Rect srcRect = {
        app->plant.growth * PLANT_WIDTH,
        0,
        PLANT_WIDTH,
        1500,
    };

    SDL_Rect destRect = {50, 50, PLANT_WIDTH / 2, PLANT_HEIGHT / 2};

    SDL_RenderCopy(app->renderer, app->plant.texture, &srcRect, &destRect);
}
