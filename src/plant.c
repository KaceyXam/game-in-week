#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

typedef enum PlantGrowth {
    GROWTH_SPROUT,
    GROWTH_VEGATATIVE,
    GROWTH_BUDDING,
    GROWTH_FLOWERING,
} PlantGrowth;

typedef struct Plant {
    PlantGrowth growth;
    char water;
    char fertilizer;
    SDL_Texture *texture;
} Plant;
