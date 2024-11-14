#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "common.h"
#include <SDL2/SDL_render.h>
typedef struct {
    Vector2 pos;
    SDL_Texture *texture;
} Player;

#endif
