#ifndef COMMON_HEADER
#define COMMON_HEADER

#include <SDL2/SDL.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
    int x, y;
} Vector2;

typedef enum PlantGrowth {
    GROWTH_SPROUT,
    GROWTH_VEGATATIVE,
    GROWTH_BUDDING,
    GROWTH_FLOWERING,
} PlantGrowth;

typedef struct Plant {
    PlantGrowth growth;
    float growthProgress;
    float water;
    float fertilizer;
    SDL_Texture *texture;
} Plant;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *renderTarget;
    Plant plant;
} GameState;

int initPlant(GameState *app);

void renderPlant(GameState *app);

#endif
